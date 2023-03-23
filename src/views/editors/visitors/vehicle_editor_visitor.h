#ifndef VEHICLE_EDITOR_VISITOR_H
#define VEHICLE_EDITOR_VISITOR_H

#include "../../../core/generic_visitor_interface.h"
#include "../../../core/railyard.h"

#include <QToolBar>
#include <QWidget>

namespace rtm::gui::editors
{
namespace components
{
class railway_vehicle_info_manager;
}
namespace visitors
{

class vehicle_editor_visitor : public core::visitor_interface
{

private:
  editors::components::railway_vehicle_info_manager *widget;
  QToolBar *toolbar;

  const rtm::core::railyard &ryard;

public:
  explicit vehicle_editor_visitor (const rtm::core::railyard &ryard,
                                   QToolBar *toolbar);

  editors::components::railway_vehicle_info_manager *get_widget ();

  void visit_passenger_coach (core::passenger_coach &p_coach) override;

  void visit_electric_locomotive (
      rtm::core::electric_locomotive &e_locomotive) override;

  void visit_goods_wagon (core::goods_wagon &g_wagon) override;
};
}
}

#endif