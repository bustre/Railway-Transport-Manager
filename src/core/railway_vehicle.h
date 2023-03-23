#ifndef RAILWAY_VEHICLE_H
#define RAILWAY_VEHICLE_H

#include "generic_visitor_interface.h"
#include <string>

namespace rtm::core{

// railway vehicle
class railway_vehicle
{

private:
  std::string name, id, image_path;

  double weight;          // Kg
  unsigned int max_speed; // Km/h
  double length;          // m

public:
  static const double MIN_WEIGHT;
  static const double MIN_LENGTH;
  static const unsigned int MIN_SPEED;

  railway_vehicle (const std::string &name, const std::string &id,
                   const std::string &image_path, double weight,
                   unsigned int max_speed, double length);

  virtual ~railway_vehicle () = 0;

  virtual railway_vehicle *clone () const = 0;

  const std::string &get_name () const;
  const std::string &get_id () const;
  const std::string &get_image_path () const;
  double get_weight () const;
  unsigned int get_max_speed () const;
  double get_length () const;

  void set_name (const std::string &name);
  void set_id (const std::string &id);
  void set_image_path (const std::string &path);

  // PRE: max_speed must be more than MIN_SPEED Km/h
  void set_max_speed (unsigned int max_speed);

  // PRE: weight must be more than MIN_WEIGHT Kg
  void set_weight (double weight);

  // PRE: length must be more than MIN_LENGTH m
  void set_length (double length);

  virtual void accept (visitor_interface &visitor) = 0;
  virtual void accept (const_visitor_interface &visitor) const = 0;
};
}

#endif