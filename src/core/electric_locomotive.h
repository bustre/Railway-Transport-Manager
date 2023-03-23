#ifndef ELECTRIC_LOCOMOTIVE_H
#define ELECTRIC_LOCOMOTIVE_H

#include "vehicle_types.h"
#include <string>

namespace rtm::core
{
class electric_locomotive : public locomotive
{
private:
  double engine_efficiency; // In [0,1], usually is 0.82

public:
  electric_locomotive (const std::string &name, const std::string &id,
                       const std::string &image_path, unsigned int power,
                       unsigned int max_speed, double length, double weight,
                       unsigned int max_trailers,
                       double engine_efficiency = 0.82);

  ~electric_locomotive () override = default;

  electric_locomotive *clone () const override;

  double get_tractive_force () const override;
  double get_engine_efficiency () const;

  void set_engine_efficiency (double efficiency);

  void accept (visitor_interface &visitor) override;
  void accept (const_visitor_interface &visitor) const override;
};
}

#endif