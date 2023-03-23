#ifndef RAILWAY_VEHICLE_VIEWER_H
#define RAILWAY_VEHICLE_VIEWER_H

#include "../../../core/railway_vehicle.h"

#include <QFormLayout>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace rtm::gui::viewers::components
{

class railway_vehicle_viewer : public QWidget
{
  Q_OBJECT

private:
  const core::railway_vehicle &r_vehicle;
  const std::string &project_path;

  QVBoxLayout *layout_main;
  QFormLayout *layout_info;
  QPushButton *bt_close;
  QLabel *l_image;
  QLabel *l_name;
  QLabel *l_id;
  QLabel *l_weight;
  QLabel *l_max_speed;
  QLabel *l_length;

  void load_data () const;

protected:
  void add_row (QWidget *w_left, QWidget *w_right) const;
  void add_layout (QLayout *l) const;

public:
  railway_vehicle_viewer (const core::railway_vehicle &r_vehicle,
                          const std::string &project_path,
                          QWidget *parent = nullptr);

  ~railway_vehicle_viewer () override = 0;

signals:
  void close ();
};

}

#endif