#include "electric_locomotive_info_manager.h"

#include <QFormLayout>
#include <QLabel>
#include <string>

namespace rtm::gui::editors::components
{

electric_locomotive_info_manager::electric_locomotive_info_manager (
    const core::railyard &ryard, core::electric_locomotive &_e_locomotive,
    QWidget *parent)
    : locomotive_info_manager (ryard, _e_locomotive, parent),
      e_locomotive (_e_locomotive)
{

  input_efficiency = new QDoubleSpinBox ();
  QWidget *page = new QWidget ();
  QFormLayout *layout_info = new QFormLayout (page);

  input_efficiency->setRange (0, 1);
  input_efficiency->setSingleStep (0.01);

  layout_info->addRow (new QLabel (tr ("Motors efficiency:")),
                       input_efficiency);

  add_page (page, tr ("Specific information"));

  load_data ();
}

/// Private Methods
void
electric_locomotive_info_manager::load_data () const
{
  input_efficiency->setValue (e_locomotive.get_engine_efficiency ());
}

/// Public Methods
void
electric_locomotive_info_manager::save_data ()
{
  if (!get_data_status ())
    return;

  locomotive_info_manager::save_data ();

  e_locomotive.set_engine_efficiency (input_efficiency->value ());
}
}