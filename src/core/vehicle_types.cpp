#include "vehicle_types.h"

namespace rtm::core
{
/// LOCOMOTIVE TYPE
locomotive::locomotive (const std::string &name, const std::string &id,
                        const std::string &image_path, unsigned int _power,
                        unsigned int max_speed, double length, double weight,
                        unsigned int max_trailers)
    : railway_vehicle (name, id, image_path, weight, max_speed, length),
      power (_power), max_num_trailers (max_trailers)
{
}

locomotive::~locomotive () {}

// Public methods
unsigned int
locomotive::get_power () const
{
  return power;
}

unsigned int
locomotive::get_max_num_trailers () const
{
  return max_num_trailers;
}

void
locomotive::set_power (unsigned int pwr)
{
  power = pwr;
}

void
locomotive::set_max_num_trailers (unsigned int max_carts)
{
  max_num_trailers = max_carts;
}

/// RAILROAD_CAR TYPE
railroad_car::railroad_car (const std::string &name, const std::string &id,
                            const std::string &image_path, double weight,
                            unsigned max_speed, double length)
    : railway_vehicle (name, id, image_path, weight, max_speed, length)
{
}

railroad_car::~railroad_car () {}
}