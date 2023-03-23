#include "vehicle_editor.h"

namespace rtm::gui::editors
{

vehicle_editor::vehicle_editor (const core::railyard &_ryard,
                                core::railway_vehicle *_r_vehicle,
                                const std::string &_project_path,
                                QToolBar *_toolbar, QWidget *parent)
    : QWidget (parent), r_vehicle (_r_vehicle), ryard (_ryard),
      project_path (_project_path), toolbar (_toolbar)
{

  visitors::vehicle_editor_visitor visitor (ryard, toolbar);
  r_vehicle->accept (visitor);

  layout_main = new QHBoxLayout (this);
  img_manager = new components::image_manager (*r_vehicle, project_path, this);
  info_manager = visitor.get_widget ();

  layout_main->addWidget (img_manager);
  layout_main->addWidget (info_manager);

  setup_toolbar ();

  change_button (info_manager->get_data_status ());
}

vehicle_editor::~vehicle_editor () { delete layout_main; }

/// Private Methods
void
vehicle_editor::change_button (bool status) const
{
  bt_save->setEnabled (status);
}

void
vehicle_editor::setup_toolbar ()
{
  bt_save = new QAction (tr ("Save"), toolbar);
  bt_save->setIcon (QIcon (":assets/icons/save.svg"));

  bt_cancel = new QAction (tr ("Cancel"), toolbar);
  bt_cancel->setIcon (QIcon (":assets/icons/delete.svg"));

  change_button (false);

  connect (info_manager,
           &components::railway_vehicle_info_manager::data_status_change, this,
           &vehicle_editor::change_button);

  connect (bt_save, &QAction::triggered, this,
           &vehicle_editor::save_and_close);

  connect (bt_cancel, &QAction::triggered, this,
           &vehicle_editor::cancel_editing);

  toolbar->clear ();
  toolbar->addAction (bt_save);
  toolbar->addAction (bt_cancel);
}

void
vehicle_editor::save_data ()
{
  img_manager->save_data ();
  info_manager->save_data ();

  emit data_has_been_modifed (true);
}

void
vehicle_editor::cancel_editing ()
{
  toolbar->clear ();
  emit close (false);
}

void
vehicle_editor::save_and_close ()
{
  save_data ();
  toolbar->clear ();
  emit close (true);
}

}