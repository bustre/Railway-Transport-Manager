#include "locomotive_info_manager.h"

#include <QFormLayout>
#include <limits>
#include <string>

namespace rtm::gui::editors::components
{

locomotive_info_manager::locomotive_info_manager (
    const core::railyard &ryard, core::locomotive &_locomotive,
    QWidget *parent)
    : railway_vehicle_info_manager (ryard, _locomotive, parent),
      locomotive (_locomotive)
{

  input_power = new QSpinBox ();
  input_max_trailers = new QSpinBox ();
  QWidget *page = new QWidget ();
  QFormLayout *layout_info = new QFormLayout (page);

  input_power->setRange (1, std::numeric_limits<int>::max ());
  input_max_trailers->setRange (0, std::numeric_limits<int>::max ());

  layout_info->addRow (new QLabel (tr ("Engines total power (Watts):")),
                       input_power);
  layout_info->addRow (new QLabel (tr ("Maximum trainable carts (unit):")),
                       input_max_trailers);
  layout_info->addRow (new QLabel (tr (
      "If the maximum number of trailers is set to 0, there is no limit.")));

  add_page (page, tr ("Generic locomotive info"));

  load_data ();
}

locomotive_info_manager::~locomotive_info_manager () {}

/// Private Methods
void
locomotive_info_manager::load_data () const
{
  input_power->setValue (locomotive.get_power ());
  input_max_trailers->setValue (locomotive.get_max_num_trailers ());
}

/// Public Methods
void
locomotive_info_manager::save_data ()
{
  if (!get_data_status ())
    return;

  railway_vehicle_info_manager::save_data ();

  locomotive.set_power (input_power->value ());
  locomotive.set_max_num_trailers (input_max_trailers->value ());
}
}