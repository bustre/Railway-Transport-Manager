#ifndef GOODS_WAGON_H
#define GOODS_WAGON_H

#include "../utils/vector.h"
#include "load_limit_panel.h"
#include "vehicle_types.h"
#include <string>

namespace rtm::core
{
class goods_wagon : public railroad_car
{
private:
  bool covered;
  double floor_space;   // m^2
  double load_capacity; // m^3
  load_limit_panel limit_panel;

public:
  goods_wagon (const std::string &name, const std::string &id,
               const std::string &image_path, double weight,
               unsigned int max_speed, double length, bool is_covered,
               double floor_space, double load_capacity,
               const load_limit_panel &limit_panel = load_limit_panel ());

  ~goods_wagon () override = default;

  goods_wagon *clone () const override;

  bool is_covered () const;
  double get_floor_space () const;
  double get_load_capacity () const;
  load_limit_panel get_load_limit_panel () const;

  void set_covered (bool is_covered);
  void set_floar_space (double f_space);
  void set_load_capacity (double l_capacity);
  void set_load_limit_panel (const load_limit_panel &l_panel);

  void accept (visitor_interface &visitor) override;
  void accept (const_visitor_interface &visitor) const override;
};
}

#endif