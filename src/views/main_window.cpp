#include "main_window.h"

#include "../core/converter/converter.h"
#include "editors/vehicle_editor.h"
#include "viewers/vehicle_viewer.h"
#include <QCloseEvent>
#include <QFileInfo>
#include <QMessageBox>
#include <QString>

namespace rtm::gui
{

const QString &main_window::window_title = "Railroad Transport Manager";

main_window::main_window (settings &_settings, QWidget *parent)
    : QMainWindow (parent), r_vehicle_selected (nullptr),
      r_vehicle_status (NO_STATUS), project_file_path (""),
      ryard (core::railyard ()), has_unsaved_changes (false),
      app_settings (_settings), main_view (nullptr), main_toolbar (nullptr)
{
  setMenuBar (create_menu ());
  main_toolbar = new QToolBar ();
  main_toolbar->setEnabled (false); // No project open

  setup_viewer ();
  addToolBar (Qt::LeftToolBarArea, main_toolbar);
  main_toolbar->setMovable (false);
  main_toolbar->toggleViewAction ()->setEnabled (false);
  main_toolbar->toggleViewAction ()->setVisible (false);

  resize (1024, 800);
  setMinimumSize (800, 600);

  setWindowTitle (window_title);
}

main_window::~main_window ()
{
  delete main_view;
  delete main_toolbar;
}

/// Viewer methods
void
main_window::cleanup_view ()
{
  if (main_view)
    {
      delete main_view;
      main_view = nullptr;
    }
}

void
main_window::setup_viewer ()
{
  // cleanup_view(); Already did by default_view()

  QFileInfo file_project (QString::fromStdString (project_file_path));

  main_view = new viewers::vehicle_viewer (
      ryard, file_project.absolutePath ().toStdString (), main_toolbar, this);
  setCentralWidget (main_view);

  connect (static_cast<viewers::vehicle_viewer *> (main_view),
           &viewers::vehicle_viewer::create_vehicle, this,
           &main_window::create_vehicle);

  connect (static_cast<viewers::vehicle_viewer *> (main_view),
           &viewers::vehicle_viewer::edit_vehicle, this,
           &main_window::setup_editing);

  connect (static_cast<viewers::vehicle_viewer *> (main_view),
           &viewers::vehicle_viewer::modified, this,
           &main_window::set_data_changed);
}

void
main_window::gen_recent_projects_list ()
{
  auto &c_recent_projetcs = app_settings.get_recent_files ();
  m_recent_project->clear ();

  // Gen list recent files
  for (auto cit = c_recent_projetcs.begin (); cit != c_recent_projetcs.end ();
       cit++)
    {
      QAction *a_open_project = new QAction ();
      a_open_project->setText (*cit);
      m_recent_project->addAction (a_open_project);

      connect (a_open_project, &QAction::triggered, this,
               [=] { this->load_recent_project (a_open_project->text ()); });
    }

  QAction *close = new QAction (tr ("Clear history"), m_recent_project);

  if (c_recent_projetcs.isEmpty ())
    close->setEnabled (false);

  connect (close, &QAction::triggered, this,
           &main_window::clear_recent_project);

  m_recent_project->addAction (close);
}

QMenuBar *
main_window::create_menu ()
{
  QMenuBar *menu_bar = new QMenuBar (this);

  // Menu -> File
  QMenu *m_file = menu_bar->addMenu (tr ("File"));
  QAction *new_project = new QAction (QIcon (":assets/icons/project.svg"),
                                      tr ("New project"), menu_bar);
  new_project->setShortcut (QKeySequence (Qt::CTRL | Qt::Key_N));

  QAction *save_project = new QAction (QIcon (":assets/icons/save.svg"),
                                       tr ("Save project"), menu_bar);
  save_project->setShortcut (QKeySequence (Qt::CTRL | Qt::Key_S));

  QAction *open_project
      = new QAction (QIcon (":assets/icons/project-folder.svg"),
                     tr ("Open project"), menu_bar);

  open_project->setShortcut (QKeySequence (Qt::CTRL | Qt::Key_O));

  // Menu -> Recent project
  QAction *recent_project = new QAction (tr ("Recent project"), menu_bar);
  recent_project->setIcon (QIcon (":assets/icons/folder-recent.svg"));

  m_recent_project = new QMenu ();
  recent_project->setMenu (m_recent_project);

  gen_recent_projects_list ();

  // Menu -> File
  m_file->addAction (new_project);
  m_file->addAction (save_project);
  m_file->addAction (open_project);
  m_file->addAction (recent_project);

  connect (new_project, &QAction::triggered, this, &main_window::new_project);
  connect (save_project, &QAction::triggered, this,
           &main_window::save_project);
  connect (open_project, &QAction::triggered, this,
           [=] { this->load_project (true); });

  // Menu->Settings
  QMenu *m_settings = menu_bar->addMenu (tr ("Settings"));
  QMenu *m_langs = new QMenu ();

  // All langs
  QAction *set_lang_english = new QAction (tr ("English"));
  QAction *set_lang_italian = new QAction (tr ("Italian"));

  m_langs->addAction (set_lang_english);
  m_langs->addAction (set_lang_italian);

  // Settings actions
  QAction *change_lang = new QAction (tr ("Change language"));
  change_lang->setMenu (m_langs);

  m_settings->addAction (change_lang);

  connect (set_lang_english, &QAction::triggered, this,
           &main_window::change_lang_to_default);
  connect (set_lang_italian, &QAction::triggered, this,
           &main_window::change_lang_to_it);

  // Menu->About
  QMenu *m_about = menu_bar->addMenu (tr ("About"));
  QAction *m_about_pao = new QAction (tr ("About RTM"), m_about);
  QAction *m_about_qt = new QAction (tr ("About Qt"), m_about);
  m_about->addAction (m_about_pao);
  m_about->addAction (m_about_qt);

  connect (m_about_pao, &QAction::triggered, this,
           &main_window::show_pao_project_about);
  connect (m_about_qt, &QAction::triggered, this, &main_window::show_qt_about);

  return menu_bar;
}

/// Create & editing obj
void
main_window::start_editing ()
{
  cleanup_view ();

  QFileInfo file_project (QString::fromStdString (project_file_path));

  main_view = new editors::vehicle_editor (
      ryard, r_vehicle_selected, file_project.absolutePath ().toStdString (),
      main_toolbar, this);

  connect (static_cast<editors::vehicle_editor *> (main_view),
           &editors::vehicle_editor::close, this, &main_window::end_editing);

  connect (static_cast<editors::vehicle_editor *> (main_view),
           &editors::vehicle_editor::data_has_been_modifed, this,
           &main_window::set_data_changed);

  setCentralWidget (main_view);
}

void
main_window::set_data_changed (bool status)
{
  has_unsaved_changes = status;

  if (has_unsaved_changes)
    setWindowTitle ("*" + window_title);
  else
    setWindowTitle (window_title);
}

/// Settings
void
main_window::add_recent_project (const QString &path)
{
  app_settings.add_recent_file (path);
  gen_recent_projects_list ();
}

/// Public Slots

void
main_window::show_pao_project_about () const
{
  QMessageBox::about (nullptr, tr ("About RTM"),
                      tr ("PAO project"
                          "\n    Student: "
                          "Alessandro Bustreo"
                          "\n    Academic year: 2022/2023."));
}

void
main_window::show_qt_about () const
{
  QMessageBox::aboutQt (nullptr, tr ("About Qt"));
}

/// Public Slots -> Create & editing obj
void
main_window::setup_editing (core::railway_vehicle *r_vehicle, bool is_copy)
{
  r_vehicle_selected = r_vehicle;
  r_vehicle_status
      = is_copy ? editing_status::FORM_COPY : editing_status::FROM_EDITING;
  start_editing ();
}

void
main_window::end_editing (bool status)
{

  switch (r_vehicle_status)
    {
    case editing_status::FORM_CREATE:
    case editing_status::FORM_COPY:
      if (status)
        ryard.add (*r_vehicle_selected);
      break;

    case editing_status::FROM_EDITING:
      ryard.add (*r_vehicle_selected);
      break;

    case NO_STATUS:
    default:
      // If this assert is raised, it may be that you have forgotten to
      // update
      // this section after updating editing_status in the vehicle editor.
      assert (0);
      break;
    }

  if (status)
    set_data_changed (true);

  // Clean up
  delete r_vehicle_selected;
  r_vehicle_selected = nullptr;
  r_vehicle_status = editing_status::NO_STATUS;
  default_view (); // Set the viewer
}

void
main_window::create_vehicle (vehicle_t type)
{
  switch (type)
    {
    case vehicle_t::ELECTRIC_LOCOMOTIVE:
      r_vehicle_selected = new core::electric_locomotive (
          "", "", "", 1, core::electric_locomotive::MIN_SPEED,
          core::electric_locomotive::MIN_LENGTH,
          core::electric_locomotive::MIN_WEIGHT, 1, 0.82);
      break;

    case vehicle_t::PASSENGER_COACH:
      r_vehicle_selected = new core::passenger_coach (
          "", "", "", core::passenger_coach::MIN_WEIGHT,
          core::passenger_coach::MIN_SPEED, core::passenger_coach::MIN_LENGTH,
          "", 1);
      break;

    case vehicle_t::GOODS_WAGON:
      r_vehicle_selected
          = new core::goods_wagon ("", "", "", core::goods_wagon::MIN_WEIGHT,
                                   core::goods_wagon::MIN_SPEED,
                                   core::goods_wagon::MIN_LENGTH, true, 1, 1);
      break;

    default:
      // If this assert is raised, it maybe you have forgotten to update
      // this section after updating vehicle_t in the main window.
      assert (0);
      break;
    }

  r_vehicle_status = editing_status::FORM_CREATE;

  if (r_vehicle_selected)
    start_editing ();
}

/// Public Slots -> Settings
void
main_window::clear_recent_project ()
{
  app_settings.clear_recent_files ();
  gen_recent_projects_list ();
}

void
main_window::change_lang_to_default ()
{
  QMessageBox::warning (
      nullptr, tr ("Change language"),
      tr ("You need to restart the application to apply the change."));
  app_settings.set_lang (settings::DEFAULT_EN);
}

void
main_window::change_lang_to_it ()
{
  QMessageBox::warning (
      nullptr, tr ("Change language"),
      tr ("You need to restart the application to apply the change."));
  app_settings.set_lang (settings::ITALIAN);
}

/// Public Slots -> project
void
main_window::new_project ()
{
  ask_about_unsaved_change ();

  project_file_path = QFileDialog::getSaveFileName (
                          this, tr ("New project - railroad transport manage"),
                          "", "Json (*.json)")
                          .toStdString ();

  if (project_file_path.empty ())
    return;

  set_data_changed (false);
  ryard = core::railyard ();

  // A project is open
  main_toolbar->setEnabled (true);
  default_view ();
}

void
main_window::save_project ()
{

  if (project_file_path.empty ())
    project_file_path
        = QFileDialog::getSaveFileName (
              this, tr ("Save data - railroad transport manager"), "",
              "Json (*.json)")
              .toStdString ();

  if (project_file_path.empty ())
    return;

  QJsonDocument doc = ryard.to_json_document ();
  QFile file (project_file_path.c_str ());
  file.open (QIODevice::WriteOnly);

  if (!file.isOpen ())
    {
      QMessageBox::critical (
          nullptr, tr ("Error"),
          tr ("It is impossible to open the selected file."));
      project_file_path = "";
      file.close ();
      return;
    }

  file.write (doc.toJson ());
  file.close ();
  set_data_changed (false);
  add_recent_project (QString::fromStdString (project_file_path));
}

void
main_window::load_project (bool ask_path)
{
  core::railyard aux_railyard;

  if (ask_path)
    project_file_path
        = QFileDialog::getOpenFileName (
              this, tr ("Open progetto - railroad transport manage"), "",
              "Json (*.json)")
              .toStdString ();

  if (project_file_path.empty ())
    return;

  QFile file (project_file_path.c_str ());
  file.open (QIODevice::ReadOnly);
  if (!file.isOpen ())
    {
      QMessageBox::critical (
          nullptr, tr ("Error"),
          tr ("It is impossible to open the selected file."));
      project_file_path = "";
      return;
    }

  QByteArray data = file.readAll ();
  file.close ();
  QJsonDocument doc = QJsonDocument::fromJson (data);

  try
    {
      aux_railyard.form_json_document (doc);
      add_recent_project (QString::fromStdString (project_file_path));

      // Everything is fine
      ask_about_unsaved_change ();
      main_toolbar->setEnabled (true);
      ryard = aux_railyard;
    }
  catch (core::converter::converter::error &e)
    {
      switch (e)
        {
        case core::converter::converter::error::INVALID_DATA:
          QMessageBox::critical (
              nullptr, tr ("Error"),
              tr ("The selected file appears to be damaged. I found invalid "
                  "data. "
                  "Unable to proceed with loading the data."));
          break;

        case core::converter::converter::error::INVALID_FORMAT:
          QMessageBox::critical (
              nullptr, tr ("Error"),
              tr ("The selected file appears to be invalid format. Mabey is "
                  "not a standard JSON file? "
                  "Unable to proceed with loading the data."));
          break;

        case core::converter::converter::error::GENERIC_ERROR:
        default:
          QMessageBox::critical (
              nullptr, tr ("Error"),
              tr ("The selected file appears to be damaged. "
                  "Unable to proceed with loading the data."));
          break;
        }
    }

  default_view ();
}

void
main_window::load_recent_project (const QString &path)
{
  project_file_path = path.toStdString ();
  load_project (false);
}

void
main_window::default_view ()
{
  main_toolbar->clear ();
  cleanup_view ();
  setup_viewer ();
}

void
main_window::ask_about_unsaved_change ()
{
  if (!has_unsaved_changes)
    return;

  QMessageBox::StandardButton qst = QMessageBox::question (
      nullptr, tr ("Save changes?"),
      tr ("Open project contain unsaved change. You want save this change?"));

  if (qst == QMessageBox::Yes)
    save_project ();
}

// Protected

void
main_window::closeEvent (QCloseEvent *event)
{
  ask_about_unsaved_change ();
  event->accept ();
}
}