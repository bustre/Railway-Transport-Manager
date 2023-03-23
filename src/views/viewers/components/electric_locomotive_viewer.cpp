#include "electric_locomotive_viewer.h"

namespace rtm::gui::viewers::components
{
electric_locomotive_viewer::electric_locomotive_viewer (
    const core::electric_locomotive &_e_locomotive,
    const std::string &project_path, QWidget *parent)
    : locomotive_viewer (_e_locomotive, project_path, parent),
      e_locomotive (_e_locomotive)
{
  l_engine_efficiency = new QLabel ();

  add_row (new QLabel (tr ("Engine efficiency:")), l_engine_efficiency);
  load_data ();
}

void
electric_locomotive_viewer::load_data () const
{
  l_engine_efficiency->setText (
      QString::number (e_locomotive.get_engine_efficiency ()));
}
}