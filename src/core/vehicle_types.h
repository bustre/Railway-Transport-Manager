#ifndef VEHICLE_TYPES_H
#define VEHICLE_TYPES_H

#include "railway_vehicle.h"
#include <string>

namespace rtm::core
{
class locomotive : public railway_vehicle
{
private:
  unsigned int power;            // Watts
  unsigned int max_num_trailers; // if == 0 --> no limit

public:
  locomotive (const std::string &name, const std::string &id,
              const std::string &image_path, unsigned int power,
              unsigned int max_speed, double length, double weight,
              unsigned int max_num_trailers);

  ~locomotive () override = 0;

  virtual double get_tractive_force () const = 0;
  unsigned int get_power () const;
  unsigned int get_max_num_trailers () const;

  void set_power (unsigned int power);
  void set_max_num_trailers (unsigned int max_carts);
};

class railroad_car : public railway_vehicle
{
private:
public:
  railroad_car (const std::string &name, const std::string &id,
                const std::string &image_path, double weight,
                unsigned max_speed, double length);

  ~railroad_car () override = 0;
};
}

#endif