#include "goods_wagon.h"

namespace rtm::core
{

/// GOODS WAGON
goods_wagon::goods_wagon (const std::string &name, const std::string &id,
                          const std::string &image_path, double weight,
                          unsigned int max_speed, double length,
                          bool is_covered, double _floor_space,
                          double _load_capacity,
                          const load_limit_panel &_limit_panel)
    : railroad_car (name, id, image_path, weight, max_speed, length),
      covered (is_covered), floor_space (_floor_space),
      load_capacity (_load_capacity),
      limit_panel (load_limit_panel (_limit_panel))
{
}

goods_wagon *
goods_wagon::clone () const
{
  return new goods_wagon (*this);
}

bool
goods_wagon::is_covered () const
{
  return covered;
}

double
goods_wagon::get_floor_space () const
{
  return floor_space;
}

double
goods_wagon::get_load_capacity () const
{
  return load_capacity;
}

load_limit_panel
goods_wagon::get_load_limit_panel () const
{
  return limit_panel;
}

void
goods_wagon::set_covered (bool is_covered)
{
  covered = is_covered;
}

void
goods_wagon::set_floar_space (double f_space)
{
  floor_space = f_space;
}

void
goods_wagon::set_load_capacity (double l_capacity)
{
  load_capacity = l_capacity;
}

void
goods_wagon::set_load_limit_panel (const load_limit_panel &l_panel)
{
  limit_panel = l_panel;
}

void
goods_wagon::accept (visitor_interface &visitor) 
{
  visitor.visit_goods_wagon (*this);
}

void
goods_wagon::accept (const_visitor_interface &visitor) const
{
  visitor.visit_goods_wagon (*this);
}

}