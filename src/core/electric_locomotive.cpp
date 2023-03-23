#include "electric_locomotive.h"

#include "converter/converter.h"
#include <stdexcept>

namespace rtm::core
{

/// ELECTRIC LOCOMOTIVE
electric_locomotive::electric_locomotive (
    const std::string &name, const std::string &id,
    const std::string &image_path, unsigned int power, unsigned int max_speed,
    double length, double weight, unsigned int max_trailers, double efficiency)
    : locomotive (name, id, image_path, power, max_speed, length, weight,
                  max_trailers)
{
  set_engine_efficiency (efficiency);
}

electric_locomotive *
electric_locomotive::clone () const
{
  return new electric_locomotive (*this);
}

/// Public Methods
double
electric_locomotive::get_tractive_force () const
{
  return (static_cast<double> (get_power ()) * engine_efficiency)
         / (get_max_speed () / 3.6);

  // [Formula] t = P*E / v (https://en.wikipedia.org/wiki/Tractive_force)
  // t = tractive froce
  // P = Engine Power (Watts)
  // E = Engine efficiency
  // v = Speed (m/s)
}

double
electric_locomotive::get_engine_efficiency () const
{
  return engine_efficiency;
}

void
electric_locomotive::set_engine_efficiency (double efficiency)
{
  if (efficiency < 0 || efficiency > 1)
    throw std::invalid_argument (
        "Engine efficiency must be between 0 and 1. The value I got is: "
        + std::to_string (efficiency) + ".");

  engine_efficiency = efficiency;
}

void
electric_locomotive::accept (visitor_interface &visitor)
{
  visitor.visit_electric_locomotive (*this);
}

void
electric_locomotive::accept (const_visitor_interface &visitor) const
{
  visitor.visit_electric_locomotive (*this);
}
}