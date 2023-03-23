#include "railway_vehicle.h"
#include <stdexcept>

#include "converter/converter.h"

namespace rtm::core
{

/// RAILWAY VEHICLE
const double railway_vehicle::MIN_WEIGHT = 500.0;
const double railway_vehicle::MIN_LENGTH = 1.0;
const unsigned int railway_vehicle::MIN_SPEED = 1.0;

railway_vehicle::railway_vehicle (const std::string &_name,
                                  const std::string &_id,
                                  const std::string &_image_path,
                                  double _weight, unsigned int _max_speed,
                                  double _length)
{
  set_name (_name);
  set_id (_id);
  set_image_path (_image_path);
  set_weight (_weight);
  set_max_speed (_max_speed);
  set_length (_length);
}

railway_vehicle::~railway_vehicle () {}

/// Public Methods
const std::string &
railway_vehicle::get_name () const
{
  return name;
}

const std::string &
railway_vehicle::get_id () const
{
  return id;
}

const std::string &
railway_vehicle::get_image_path () const
{
  return image_path;
}

double
railway_vehicle::get_weight () const
{
  return weight;
}

unsigned int
railway_vehicle::get_max_speed () const
{
  return max_speed;
}

double
railway_vehicle::get_length () const
{
  return length;
}

void
railway_vehicle::set_name (const std::string &new_name)
{
  name = new_name;
}

void
railway_vehicle::set_id (const std::string &new_id)
{
  id = new_id;
}

void
railway_vehicle::set_image_path (const std::string &path)
{
  image_path = path;
}

void
railway_vehicle::set_weight (double new_weight)
{
  if (new_weight < MIN_WEIGHT)
    throw std::invalid_argument (
        "Weight cannot be less than " + std::to_string (MIN_WEIGHT)
        + " Kg. The value I got is: " + std::to_string (new_weight) + " kg.");

  weight = new_weight;
}

void
railway_vehicle::set_max_speed (unsigned int new_max_speed)
{
  if (new_max_speed < MIN_SPEED)
    throw std::invalid_argument ("Max speed cannot be less than "
                                 + std::to_string (MIN_SPEED)
                                 + " Km/h. The value I got is: "
                                 + std::to_string (new_max_speed) + " Km/h.");
  max_speed = new_max_speed;
}

void
railway_vehicle::set_length (double len)
{
  if (len < MIN_LENGTH)
    throw std::invalid_argument (
        "Length cannot be less than " + std::to_string (MIN_LENGTH)
        + " m.The value I got is: " + std::to_string (len) + " m.");

  length = len;
}

}