#ifndef VEHICLE_VIEWER_VISITOR_H
#define VEHICLE_VIEWER_VISITOR_H

#include "../../../core/generic_visitor_interface.h"
#include "../components/railway_vehicle_viewer.h"

#include <QWidget>
namespace rtm::gui::viewers::visitors
{
class vehicle_viewer_visitor : public core::const_visitor_interface
{

private:
  components::railway_vehicle_viewer *widget;
  QWidget *parent;
  const std::string &project_path;

public:
  vehicle_viewer_visitor (const std::string &project_path,
                          QWidget *parent = nullptr);

  components::railway_vehicle_viewer *get_widget ();

  void visit_passenger_coach (const core::passenger_coach &p_coach) override;
  void visit_electric_locomotive (
      const core::electric_locomotive &e_locomotive) override;
  void visit_goods_wagon (const core::goods_wagon &g_wagon) override;
};
}

#endif