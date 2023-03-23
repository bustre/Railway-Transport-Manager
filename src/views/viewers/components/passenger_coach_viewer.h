#ifndef PASSENGER_COACH_VIEWER_H
#define PASSENGER_COACH_VIEWER_H

#include "../../../core/passenger_coach.h"
#include "railroad_car_viewer.h"

#include <QLabel>

namespace rtm::gui::viewers::components
{
class passenger_coach_viewer : public railroad_car_viewer
{
  Q_OBJECT

private:
  const core::passenger_coach &p_coach;

  QLabel *l_seats;
  QLabel *l_class;

  void load_data () const;

public:
  passenger_coach_viewer (const core::passenger_coach &p_coach,
                          const std::string &project_path,
                          QWidget *parent = nullptr);

  ~passenger_coach_viewer () override = default;
};
}

#endif