#ifndef VEHICLE_EDITOR
#define VEHICLE_EDITOR

#include "../../core/railway_vehicle.h"
#include "../../core/railyard.h"

#include "visitors/vehicle_editor_visitor.h"

#include "components/electric_locomotive_info_manager.h"
#include "components/image_manager.h"
#include "components/locomotive_info_manager.h"
#include "components/railway_vehicle_info_manager.h"
#include <QAction>
#include <QHBoxLayout>
#include <QToolBar>
#include <QWidget>

namespace rtm::gui::editors
{

class vehicle_editor : public QWidget
{
  Q_OBJECT

private:
  core::railway_vehicle *r_vehicle;
  const core::railyard &ryard;
  const std::string project_path;

  QHBoxLayout *layout_main;

  components::image_manager *img_manager;
  components::railway_vehicle_info_manager *info_manager;

  QToolBar *toolbar;
  QAction *bt_save;
  QAction *bt_cancel;

  void setup_toolbar ();
  void change_button (bool status) const;

public:
  vehicle_editor (const core::railyard &ryard,
                  core::railway_vehicle *r_vehicle,
                  const std::string &project_path, QToolBar *toolbar,
                  QWidget *parent = nullptr);

  ~vehicle_editor () override;

  void save_data ();
  void save_and_close ();
  void cancel_editing ();

signals:
  void close (bool); // iif arg is true then the data has been saved
  void data_has_been_modifed (bool);
};
}

#endif