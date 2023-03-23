#include "vehicle_viewer.h"

#include "../../core/railyard.h"
#include <QComboBox>
#include <QInputDialog>
#include <QMetaEnum>
#include <QVariant>

#include "components/railroad_car_viewer.h"
#include "visitors/vehicle_viewer_visitor.h"

// In this way I can use properly railway_vehicle with Qt
Q_DECLARE_METATYPE (const rtm::core::railway_vehicle *)

namespace rtm::gui::viewers
{

vehicle_viewer::vehicle_viewer (core::railyard &_ryard,
                                const std::string &_project_path,
                                QToolBar *_toolbar, QWidget *parent)
    : QWidget (parent), ryard (_ryard), project_path (_project_path),
      toolbar (_toolbar), view_details (nullptr)
{
  layout_main = new QHBoxLayout (this);
  layout_left = new QVBoxLayout;
  list_item = new QListWidget;
  s_bar = new components::search_bar;
  view_details = nullptr;

  list_item->setIconSize (QSize (192, 192));
  setup_toolbar ();

  layout_left->addWidget (s_bar);
  layout_left->addWidget (list_item);
  layout_main->addLayout (layout_left, 1);
  generate_list ();

  connect (s_bar, &components::search_bar::search_request, this,
           &vehicle_viewer::generate_list);
}

vehicle_viewer::~vehicle_viewer ()
{
  list_item->clear ();
  delete list_item;
  delete layout_main;
  toolbar->clear ();
}

/// Init the viewer
void
vehicle_viewer::setup_toolbar () const
{
  toolbar->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);
  toolbar->setIconSize (QSize (32, 32));

  QAction *new_obj = new QAction (tr ("Add"), toolbar);
  new_obj->setIcon (QIcon (":assets/icons/add.svg"));

  QAction *details_obj = new QAction (tr ("Info"), toolbar);
  details_obj->setIcon (QIcon (":assets/icons/question.svg"));

  QAction *modify_obj = new QAction (tr ("Edit"), toolbar);
  modify_obj->setIcon (QIcon (":assets/icons/edit.svg"));

  QAction *copy_obj = new QAction (tr ("Copy"), toolbar);
  copy_obj->setIcon (QIcon (":assets/icons/copy.svg"));

  QAction *remove_obj = new QAction (tr ("Remove"), toolbar);
  remove_obj->setIcon (QIcon (":assets/icons/delete.svg"));

  connect (new_obj, &QAction::triggered, this,
           &vehicle_viewer::setup_for_create);
  connect (modify_obj, &QAction::triggered, this,
           &vehicle_viewer::setup_for_edit);
  connect (copy_obj, &QAction::triggered, this,
           &vehicle_viewer::setup_for_copy);
  connect (remove_obj, &QAction::triggered, this,
           &vehicle_viewer::delete_selected_vehicle);
  connect (details_obj, &QAction::triggered, this,
           &vehicle_viewer::show_info_viewer);

  toolbar->addAction (new_obj);
  toolbar->addSeparator ();
  toolbar->addAction (remove_obj);
  toolbar->addSeparator ();
  toolbar->addAction (details_obj);
  toolbar->addSeparator ();
  toolbar->addAction (modify_obj);
  toolbar->addSeparator ();
  toolbar->addAction (copy_obj);
  toolbar->addSeparator ();
}

void
vehicle_viewer::generate_list () const
{
  list_item->clear ();

  auto r_vehicle = ryard.search (s_bar->get_search_function ());

  for (auto it = r_vehicle.begin (); it != r_vehicle.end (); it++)
    {
      std::string image_relative_path;
      QListWidgetItem *item = new QListWidgetItem ();

      QVariant data;
      data.setValue (*it);
      item->setData (Qt::UserRole,
                     data); // UserRole, the pointer pointed by it

      image_relative_path = (*it)->get_image_path ();
      QIcon icon = QIcon (
          QString::fromStdString (project_path + "/" + image_relative_path));

      // Text format and properties
      item->setText (QString::fromStdString ((*it)->get_name () + "\n"
                                             + "ID: " + (*it)->get_id ()));
      QFont font = item->font ();
      font.setPixelSize (18);
      item->setFont (font);

      // Icon
      if (icon.pixmap (1).isNull ())
        icon = QIcon (":assets/icons/image-missing.svg");

      item->setIcon (icon);

      item->setSizeHint (QSize (64, 64));
      list_item->addItem (item);
    }
}

/// Viewer behaviors
void
vehicle_viewer::show_info_viewer ()
{
  if (!list_item->currentItem ())
    return;

  auto r_vehicle = list_item->currentItem ()
                       ->data (Qt::UserRole)
                       .value<const core::railway_vehicle *> ();

  visitors::vehicle_viewer_visitor visitor (project_path, this);
  r_vehicle->accept (visitor);

  if (view_details)
    {
      layout_main->removeWidget (view_details);
      delete view_details;
    }
  view_details = visitor.get_widget ();

  connect (view_details, &components::railway_vehicle_viewer::close, this,
           &vehicle_viewer::close_info_viewer);

  layout_main->addWidget (view_details, 1);
}

void
vehicle_viewer::close_info_viewer ()
{
  if (view_details)
    {
      layout_main->removeWidget (view_details);
      delete view_details;
      view_details = nullptr;
    }
}

void
vehicle_viewer::delete_selected_vehicle ()
{
  auto item = list_item->takeItem (list_item->currentRow ());

  if (!item)
    return;

  auto r_vehicle
      = item->data (Qt::UserRole).value<const core::railway_vehicle *> ();
  list_item->removeItemWidget (item);
  ryard.erase (*r_vehicle);

  emit modified (true);
}

void
vehicle_viewer::setup_for_edit ()
{
  if (!list_item->currentItem ())
    return;

  auto r_vehicle = list_item->currentItem ()
                       ->data (Qt::UserRole)
                       .value<const core::railway_vehicle *> ();

  emit edit_vehicle (ryard.take (*r_vehicle), false);
}

void
vehicle_viewer::setup_for_copy ()
{
  if (!list_item->currentItem ())
    return;

  auto r_vheicle = list_item->currentItem ()
                       ->data (Qt::UserRole)
                       .value<const core::railway_vehicle *> ();

  if (!r_vheicle)
    return;

  auto editable_r_vehicle = r_vheicle->clone ();
  editable_r_vehicle->set_id ("");
  emit edit_vehicle (editable_r_vehicle, true);
}

void
vehicle_viewer::setup_for_create ()
{
  QStringList options;
  bool is_okey;

  options << tr ("Electric locomotive") << tr ("Passenger coach")
          << tr ("Goods wagon");

  auto item = QInputDialog::getItem (nullptr, tr ("New railway vehicle"),
                                     tr ("Select the new type of vehicle"),
                                     options, 0, false, &is_okey);

  if (!is_okey)
    return;

  if (item == tr ("Electric locomotive"))
    emit create_vehicle (main_window::vehicle_t::ELECTRIC_LOCOMOTIVE);
  if (item == tr ("Passenger coach"))
    emit create_vehicle (main_window::vehicle_t::PASSENGER_COACH);
  if (item == tr ("Goods wagon"))
    emit create_vehicle (main_window::vehicle_t::GOODS_WAGON);
}

}