#ifndef RAILROAD_CAR_INFO_MANAGER_H
#define RAILROAD_CAR_INFO_MANAGER_H

#include "../../../core/vehicle_types.h"

#include "railway_vehicle_info_manager.h"
#include <QWidget>

namespace rtm::gui::editors::components
{

class railroad_car_info_manager : public railway_vehicle_info_manager
{
  Q_OBJECT

private:
  core::railroad_car &railroad_car;

public:
  railroad_car_info_manager (const core::railyard &ryard,
                             core::railroad_car &railroad_car,
                             QWidget *parent = nullptr);

  ~railroad_car_info_manager () override = 0;
};
}

#endif