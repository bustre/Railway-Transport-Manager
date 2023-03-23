#include "vehicle_editor_visitor.h"

#include "../../../core/electric_locomotive.h"
#include "../../../core/goods_wagon.h"
#include "../../../core/passenger_coach.h"
#include "../components/electric_locomotive_info_manager.h"
#include "../components/goods_wagon_info_manager.h"
#include "../components/passenger_coach_info_manager.h"

namespace rtm::gui::editors::visitors
{

vehicle_editor_visitor::vehicle_editor_visitor (
    const rtm::core::railyard &_ryard, QToolBar *_toolbar)
    : widget (nullptr), toolbar (_toolbar), ryard (_ryard)
{
}

editors::components::railway_vehicle_info_manager *
vehicle_editor_visitor::get_widget ()
{
  return widget;
}

void
vehicle_editor_visitor::visit_electric_locomotive (
    rtm::core::electric_locomotive &e_locomotive)
{
  widget = new editors::components::electric_locomotive_info_manager (
      ryard, e_locomotive, toolbar);
}

void
vehicle_editor_visitor::visit_passenger_coach (core::passenger_coach &p_coach)
{
  widget = new editors::components::passenger_coach_info_manager (
      ryard, p_coach, toolbar);
}

void
vehicle_editor_visitor::visit_goods_wagon (core::goods_wagon &g_wagon)
{
  widget = new editors::components::goods_wagon_info_manger (ryard, g_wagon,
                                                             toolbar);
}
}