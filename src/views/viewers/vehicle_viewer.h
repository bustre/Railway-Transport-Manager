#ifndef VIEWER_H
#define VIEWER_H

#include "../../core/railway_vehicle.h"
#include "../../core/railyard.h"

#include "../main_window.h"
#include "components/railway_vehicle_viewer.h"
#include "components/search_bar.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QPixmap>
#include <QSize>
#include <QToolBar>
#include <QWidget>

namespace rtm::gui::viewers
{

class vehicle_viewer : public QWidget
{
  Q_OBJECT

private:
  core::railyard &ryard;
  const std::string project_path;

  QHBoxLayout *layout_main;
  QVBoxLayout *layout_left;
  QListWidget *list_item;
  QToolBar *toolbar;
  components::search_bar *s_bar;
  components::railway_vehicle_viewer *view_details;

  // Init the viewer
  void setup_toolbar () const;
  void generate_list () const;

  // Viewer behaviors
  void show_info_viewer ();
  void close_info_viewer ();
  void setup_for_edit ();
  void setup_for_copy ();
  void setup_for_create ();
  void delete_selected_vehicle ();

public:
  vehicle_viewer (core::railyard &ryard, const std::string &project_path,
                  QToolBar *toolbar, QWidget *parent = nullptr);

  ~vehicle_viewer ();

signals:
  void create_vehicle (main_window::vehicle_t t);
  void edit_vehicle (core::railway_vehicle *r_vehicle, bool is_copy);
  void modified (bool);
};
}

#endif