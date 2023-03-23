#include "passenger_coach.h"

namespace rtm::core
{

/// PASSENGER_COACH
passenger_coach::passenger_coach (const std::string &name,
                                  const std::string &id,
                                  const std::string &image_path, double weight,
                                  unsigned int max_speed, double length,
                                  const std::string &_class_type,
                                  unsigned int _seats)
    : railroad_car (name, id, image_path, weight, max_speed, length),
      class_type (_class_type), seats (_seats)
{
}

passenger_coach *
passenger_coach::clone () const
{
  return new passenger_coach (*this);
}

/// Public Methods
const std::string &
passenger_coach::get_class () const
{
  return class_type;
}

unsigned int
passenger_coach::get_seats () const
{
  return seats;
}

void
passenger_coach::set_class (const std::string new_class)
{
  class_type = new_class;
}

void
passenger_coach::set_seats (unsigned int _seats)
{
  seats = _seats;
}

void
passenger_coach::accept (visitor_interface &visitor) 
{
  visitor.visit_passenger_coach (*this);
}

void
passenger_coach::accept (const_visitor_interface &visitor) const
{
  visitor.visit_passenger_coach (*this);
}
}