#ifndef PASSENGER_COACH_H
#define PASSENGER_COACH_H

#include "vehicle_types.h"
#include <string>

namespace rtm::core
{
class passenger_coach : public railroad_car
{
private:
  std::string class_type;
  unsigned int seats;

public:
  passenger_coach (const std::string &name, const std::string &id,
                   const std::string &image_path, double weight,
                   unsigned int max_speed, double length,
                   const std::string &class_type, unsigned int seats);

  ~passenger_coach () override = default;

  passenger_coach *clone () const override;

  const std::string &get_class () const;
  unsigned int get_seats () const;

  void set_class (const std::string new_class);
  void set_seats (unsigned int seats);

  void accept (visitor_interface &visitor) override;
  void accept (const_visitor_interface &visitor) const override;
};
}

#endif