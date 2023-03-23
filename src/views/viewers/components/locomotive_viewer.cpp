#include "locomotive_viewer.h"

#include <QString>

namespace rtm::gui::viewers::components
{
locomotive_viewer::locomotive_viewer (const core::locomotive &_locomotive,
                                      const std::string &project_path,
                                      QWidget *parent)
    : railway_vehicle_viewer (_locomotive, project_path, parent),
      locomotive (_locomotive)
{
  l_power = new QLabel;
  l_max_num_trailers = new QLabel;
  l_tractive_force = new QLabel;

  add_row (new QLabel (tr ("Engines total output power (watts):")), l_power);
  add_row (new QLabel (tr ("Max numbers trailers (unit):")),
           l_max_num_trailers);
  add_row (new QLabel (tr ("Tractive force (newton):")), l_tractive_force);

  load_data ();
}

locomotive_viewer::~locomotive_viewer () {}

void
locomotive_viewer::load_data () const
{
  l_power->setText (QString::number (locomotive.get_power ()));

  if (locomotive.get_max_num_trailers ())
    l_max_num_trailers->setText (
        QString::number (locomotive.get_max_num_trailers ()));
  else
    l_max_num_trailers->setText (tr ("No limit"));

  l_tractive_force->setText (
      QString::number (locomotive.get_tractive_force ()));
}

}