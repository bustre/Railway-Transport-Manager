#include "passenger_coach_viewer.h"

namespace rtm::gui::viewers::components
{
passenger_coach_viewer::passenger_coach_viewer (
    const core::passenger_coach &_p_coach, const std::string &project_path,
    QWidget *parent)
    : railroad_car_viewer (_p_coach, project_path, parent),
      p_coach (_p_coach)
{
  l_seats = new QLabel;
  l_class = new QLabel;

  add_row (new QLabel (tr ("Number of seats:")), l_seats);
  add_row (new QLabel (tr ("Class:")), l_class);

  load_data ();
}

void
passenger_coach_viewer::load_data () const
{
  l_seats->setText (QString::number (p_coach.get_seats ()));

  if (p_coach.get_class ().empty ())
    l_class->setText (tr ("Does not have a class"));
  else
    l_class->setText (QString::fromStdString (p_coach.get_class ()));
}
}