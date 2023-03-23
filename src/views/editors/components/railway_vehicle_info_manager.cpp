#include "railway_vehicle_info_manager.h"

#include "../../../core/railyard.h"
#include <QFormLayout>
#include <limits>
#include <string>

namespace rtm::gui::editors::components
{

railway_vehicle_info_manager::railway_vehicle_info_manager (
    const core::railyard &_ryard, core::railway_vehicle &_r_vehicle,
    QWidget *parent)
    : QWidget (parent), r_vehicle (_r_vehicle), valid_data (true),
      ryard (_ryard)
{

  layout_main = new QVBoxLayout (this);
  input_name = new QLineEdit ();
  input_id = new QLineEdit ();
  input_weight = new QDoubleSpinBox ();
  input_length = new QDoubleSpinBox ();
  input_speed = new QSpinBox ();

  lb_name = new QLabel (tr ("Name:"));
  lb_id = new QLabel (tr ("ID:"));

  main_tab_widget = new QTabWidget ();
  QWidget *page_1 = new QWidget;
  main_tab_widget->addTab (page_1, tr ("Basic info"));

  input_weight->setRange (500, std::numeric_limits<double>::max ());
  input_length->setRange (1, 100);
  input_speed->setRange (0, 999);
  input_speed->setToolTip (
      tr ("If the maximum speed is cannot be equal to 0."));

  QFormLayout *layout_info = new QFormLayout (page_1);
  layout_info->addRow (lb_name, input_name);
  layout_info->addRow (lb_id, input_id);
  layout_info->addRow (new QLabel (tr ("Weight (kg):")), input_weight);
  layout_info->addRow (new QLabel (tr ("Length (m):")), input_length);
  layout_info->addRow (new QLabel (tr ("Homologation max speed (Km/h):")),
                       input_speed);

  layout_main->addWidget (main_tab_widget);
  add_page (page_1, tr ("Basic info"));

  connect (input_name, &QLineEdit::editingFinished, this,
           &railway_vehicle_info_manager::update_data_status);
  connect (input_id, &QLineEdit::editingFinished, this,
           &railway_vehicle_info_manager::update_data_status);

  load_data ();
  railway_vehicle_info_manager::update_data_status ();
}

railway_vehicle_info_manager::~railway_vehicle_info_manager ()
{
  delete layout_main;
}

/// Private Methods
bool
railway_vehicle_info_manager::check_name () const
{
  if (input_name->text ().isEmpty ())
    {
      lb_name->setText (tr ("Name (error: empty string):"));
      lb_name->setStyleSheet ("QLabel { color: red; }");
      return false;
    }

  lb_name->setText (tr ("Name:"));
  lb_name->setStyleSheet (styleSheet ());
  return true;
}

bool
railway_vehicle_info_manager::check_id () const
{
  const std::string &id = input_id->text ().toStdString ();

  if (id.empty ())
    {
      lb_id->setText (tr ("ID (error: empty string):"));
      lb_id->setStyleSheet ("QLabel { color: red; }");
      return false;
    }

  if (r_vehicle.get_id () != id
      && !ryard.search (core::railyard::search_by_id (id)).is_empty ())
    {
      lb_id->setText (tr ("ID (error: already used):"));
      lb_id->setStyleSheet ("QLabel { color: red; }");
      return false;
    }

  lb_id->setText (tr ("ID:"));
  lb_id->setStyleSheet (styleSheet ());
  return true;
}

void
railway_vehicle_info_manager::load_data () const
{
  input_name->setText (QString::fromStdString (r_vehicle.get_name ()));
  input_id->setText (QString::fromStdString (r_vehicle.get_id ()));

  input_weight->setValue (r_vehicle.get_weight ());
  input_length->setValue (r_vehicle.get_length ());
  input_speed->setValue (r_vehicle.get_max_speed ());
}

/// Proctected Methods
void
railway_vehicle_info_manager::set_data_status (bool status)
{
  valid_data = status;
  emit data_status_change (status);
}

void
railway_vehicle_info_manager::add_page (QWidget *page, const QString &name)
{
  main_tab_widget->addTab (page, name);
}

void
railway_vehicle_info_manager::update_data_status ()
{
  // No lazy (and avoid g++ warning)
  bool status = check_id ();
  status = check_name () && status;

  set_data_status (status);
}

/// Public Methods
void
railway_vehicle_info_manager::save_data ()
{
  if (!valid_data)
    return;

  r_vehicle.set_id (input_id->text ().toStdString ());
  r_vehicle.set_name (input_name->text ().toStdString ());
  r_vehicle.set_weight (input_weight->value ());
  r_vehicle.set_max_speed (input_speed->value ());
  r_vehicle.set_length (input_length->value ());
}

bool
railway_vehicle_info_manager::get_data_status () const
{
  return valid_data;
}

}