#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "gui_settings.h"
#include <QAction>
#include <QFileDialog>
#include <QIcon>
#include <QKeySequence>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMetaEnum>
#include <QPushButton>
#include <QSize>
#include <QString>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../core/converter/converter.h"
#include "../core/electric_locomotive.h"
#include "../core/goods_wagon.h"
#include "../core/passenger_coach.h"
#include "../core/railyard.h"
#include "../utils/vector.h"

namespace rtm::gui
{

class main_window : public QMainWindow
{
  Q_OBJECT

public:
  enum vehicle_t
  {
    ELECTRIC_LOCOMOTIVE,
    PASSENGER_COACH,
    GOODS_WAGON
  };

private:
  static const QString &window_title;

  // editing vars
  enum editing_status
  {
    NO_STATUS,
    FROM_EDITING,
    FORM_COPY,
    FORM_CREATE
  };
  core::railway_vehicle *r_vehicle_selected;
  editing_status r_vehicle_status;

  // Project & data
  std::string project_file_path;
  core::railyard ryard;
  bool has_unsaved_changes;

  /// Main window
  settings &app_settings;

  QWidget *main_view;
  QToolBar *main_toolbar;
  QMenu *m_recent_project;

  // Views
  void default_view ();
  QMenuBar *create_menu ();
  void setup_viewer ();
  void cleanup_view ();

  void gen_recent_projects_list ();

  /// Create & editing obj
  void start_editing ();
  void set_data_changed (bool status);

  /// Settings
  void add_recent_project (const QString &path);

  /// Project
  void ask_about_unsaved_change ();

protected:
  void closeEvent (QCloseEvent *event) override;

public:
  explicit main_window (settings &_settings, QWidget *parent = nullptr);
  ~main_window ();

private slots:
  void show_pao_project_about () const;
  void show_qt_about () const;

  /// Slots -> Settings
  void clear_recent_project ();
  void change_lang_to_it ();
  void change_lang_to_default ();

  /// Slots -> Project
  void new_project ();
  void save_project ();
  void load_project (bool ask_path = true);
  void load_recent_project (const QString &path);

  /// Slots -> Create & editing obj
  void setup_editing (core::railway_vehicle *r_vehicle, bool is_copy);
  void end_editing (bool status);
  void create_vehicle (vehicle_t type);
};
}

#endif