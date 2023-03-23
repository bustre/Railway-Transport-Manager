#ifndef RAILROAD_CAR_VIEWER_H
#define RAILROAD_CAR_VIEWER_H

#include "../../../core/vehicle_types.h"
#include "railway_vehicle_viewer.h"

#include <QWidget>

namespace rtm::gui::viewers::components
{

class railroad_car_viewer : public railway_vehicle_viewer
{
  Q_OBJECT

private:
  const core::railroad_car &r_car;

public:
  railroad_car_viewer (const core::railroad_car &r_car,
                       const std::string &project_path,
                       QWidget *parent = nullptr);

  ~railroad_car_viewer () override = 0;
};

}

#endif