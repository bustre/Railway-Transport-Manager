#include "passenger_coach_info_manager.h"

#include <QFormLayout>
#include <limits>
#include <string>

namespace rtm::gui::editors::components
{

passenger_coach_info_manager::passenger_coach_info_manager (
    const core::railyard &ryard, core::passenger_coach &p_coach,
    QWidget *parent)
    : railroad_car_info_manager (ryard, p_coach, parent),
      passenger_coach (p_coach)
{

  input_class = new QLineEdit ();
  input_seats = new QSpinBox ();

  QWidget *page = new QWidget;
  QFormLayout *info_layout = new QFormLayout (page);

  input_seats->setRange (1, std::numeric_limits<int>::max ());

  info_layout->addRow (new QLabel (tr ("Class:")), input_class);
  info_layout->addRow (new QLabel (tr ("Seats (unit):")), input_seats);

  add_page (page, tr ("Specific information"));
  passenger_coach_info_manager::load_data ();
}

/// Private Methods
void
passenger_coach_info_manager::load_data () const
{
  input_class->setText (QString::fromStdString (passenger_coach.get_class ()));
  input_seats->setValue (passenger_coach.get_seats ());
}

/// Public Methods
void
passenger_coach_info_manager::save_data ()
{
  if (!railway_vehicle_info_manager::get_data_status ())
    return;

  railroad_car_info_manager::save_data ();
  passenger_coach.set_class (input_class->text ().toStdString ());
  passenger_coach.set_seats (input_seats->value ());
}

}