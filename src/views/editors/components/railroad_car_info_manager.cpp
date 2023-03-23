#include "railroad_car_info_manager.h"

namespace rtm::gui::editors::components
{
railroad_car_info_manager::railroad_car_info_manager (
    const core::railyard &ryard, core::railroad_car &_railroad_car,
    QWidget *parent)
    : railway_vehicle_info_manager (ryard, _railroad_car, parent),
      railroad_car (_railroad_car)
{
}

railroad_car_info_manager::~railroad_car_info_manager () {}
}