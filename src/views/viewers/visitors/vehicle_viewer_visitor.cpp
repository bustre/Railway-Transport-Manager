#include "vehicle_viewer_visitor.h"

#include "../../../core/goods_wagon.h"
#include "../../../core/passenger_coach.h"

#include "../components/electric_locomotive_viewer.h"
#include "../components/goods_wagon_viewer.h"
#include "../components/passenger_coach_viewer.h"

namespace rtm::gui::viewers::visitors
{
vehicle_viewer_visitor::vehicle_viewer_visitor (
    const std::string &_project_path, QWidget *_parent)
    : widget (nullptr), parent (_parent), project_path (_project_path)
{
}

components::railway_vehicle_viewer *
vehicle_viewer_visitor::get_widget ()
{
  return widget;
}

void
vehicle_viewer_visitor::visit_passenger_coach (
    const core::passenger_coach &p_coach)
{
  widget
      = new components::passenger_coach_viewer (p_coach, project_path, parent);
}

void
vehicle_viewer_visitor::visit_electric_locomotive (
    const core::electric_locomotive &e_locomotive)
{
  widget = new components::electric_locomotive_viewer (e_locomotive,
                                                       project_path, parent);
}

void
vehicle_viewer_visitor::visit_goods_wagon (const core::goods_wagon &g_wagon)
{
  widget = new components::goods_wagon_viewer (g_wagon, project_path, parent);
}

}