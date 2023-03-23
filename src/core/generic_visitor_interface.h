#ifndef GENERIC_VISTOR_INTERFACE_H
#define GENERIC_VISTOR_INTERFACE_H

namespace rtm::core
{
/// Prototype
class railway_vehicle;
class electric_locomotive;
class passenger_coach;
class goods_wagon;

class const_visitor_interface
{
public:
  virtual void
  visit_electric_locomotive (const electric_locomotive &e_locomotive)
      = 0;
  virtual void visit_passenger_coach (const passenger_coach &p_coach) = 0;
  virtual void visit_goods_wagon (const goods_wagon &g_wagon) = 0;
};

class visitor_interface
{
public:
  virtual void visit_electric_locomotive (electric_locomotive &e_locomotive)
      = 0;
  virtual void visit_passenger_coach (passenger_coach &p_coach) = 0;
  virtual void visit_goods_wagon (goods_wagon &g_wagon) = 0;
};
}

#endif