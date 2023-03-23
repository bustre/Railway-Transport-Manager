#include "railroad_car_viewer.h"

namespace rtm::gui::viewers::components
{
railroad_car_viewer::railroad_car_viewer (const core::railroad_car &_r_car,
                                          const std::string &project_path,
                                          QWidget *parent)
    : railway_vehicle_viewer (_r_car, project_path, parent), r_car (_r_car)
{
}

railroad_car_viewer::~railroad_car_viewer () {}
}