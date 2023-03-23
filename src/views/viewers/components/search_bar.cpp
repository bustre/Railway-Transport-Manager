#include "search_bar.h"

#include "../../../core/vehicle_types.h"
#include <QPushButton>

namespace rtm::gui::viewers::components
{
search_bar::search_bar (QWidget *parent) : QWidget (parent)
{
  layout_main = new QVBoxLayout (this);
  le_search_id = new QLineEdit;
  le_search_name = new QLineEdit;
  cb_search_type = new QComboBox;

  QPushButton *bt_search = new QPushButton;
  bt_search->setText (tr ("Search"));
  bt_search->setIcon (QIcon (":assets/icons/search.svg"));

  QPushButton *bt_cancel_search = new QPushButton;
  bt_cancel_search->setText (tr ("Cancel"));
  bt_cancel_search->setIcon (QIcon (":assets/icons/delete.svg"));

  QHBoxLayout *layout_search = new QHBoxLayout;
  layout_search->addWidget (new QLabel (tr ("Name:")));
  layout_search->addWidget (le_search_name);
  layout_search->addWidget (new QLabel (tr ("ID:")));
  layout_search->addWidget (le_search_id);

  QHBoxLayout *layout_control = new QHBoxLayout;
  layout_control->setAlignment (Qt::AlignLeft);
  layout_control->addWidget (new QLabel (tr ("Search by type:")));
  layout_control->addWidget (cb_search_type);
  layout_control->addStretch ();
  layout_control->addWidget (bt_search);
  layout_control->addWidget (bt_cancel_search);

  layout_main->addLayout (layout_search);
  layout_main->addLayout (layout_control);
  layout_main->setAlignment (Qt::AlignLeft);

  connect (bt_search, &QPushButton::clicked, this,
           &search_bar::search_request);
  connect (bt_cancel_search, &QPushButton::clicked, this,
           &search_bar::clean_up_search);

  load_vehicle_types ();
}

void
search_bar::load_vehicle_types () const
{
  cb_search_type->addItem (tr ("All"), ALL);
  cb_search_type->addItem (tr ("Railroad car"), RAILROAD_CAR);
  cb_search_type->addItem (tr ("Locomotive"), LOCOMOTIVE);
  cb_search_type->addItem (tr ("Electric Locomotive"), ELECTRIC_LOCOMOTIVE);
  cb_search_type->addItem (tr ("Goods wagon"), GOODS_WAGON);
  cb_search_type->addItem (tr ("Passenger coach"), PASSENGER_COACH);
}

void
search_bar::clean_up_search ()
{
  le_search_name->clear ();
  le_search_id->clear ();
  cb_search_type->setCurrentIndex (ALL);
  emit search_request ();
}

std::function<bool (const core::railway_vehicle &)>
search_bar::get_search_function () const
{
  const QString &name = le_search_name->text ();
  const QString &id = le_search_id->text ();
  vehicle_types v_types = static_cast<vehicle_types> (
      cb_search_type->currentIndex ()); // FIXME: find a better way

  ctr::vector<std::function<bool (const core::railway_vehicle &)> >
      fun_to_exec; // Vector of every function to execute

  // Setting for get all elements is set
  if (name.isEmpty () && id.isEmpty () && v_types == ALL)
    return core::railyard::search_get_all ();

  // Build the vector of functions to execute
  if (!name.isEmpty ())
    {
      core::railyard::search_by_name name_search (name.toStdString ());
      fun_to_exec.push_back (name_search);
    }

  if (!id.isEmpty ())
    {
      core::railyard::search_by_id id_search (id.toStdString ());
      fun_to_exec.push_back (id_search);
    }

  switch (v_types)
    {
    case RAILROAD_CAR:
      core::railyard::search_by_type<core::railroad_car> rc_search;
      fun_to_exec.push_back (rc_search);
      break;

    case LOCOMOTIVE:
      core::railyard::search_by_type<core::locomotive> l_search;
      fun_to_exec.push_back (l_search);
      break;

    case ELECTRIC_LOCOMOTIVE:
      core::railyard::search_by_type<core::electric_locomotive> el_search;
      fun_to_exec.push_back (el_search);
      break;

    case GOODS_WAGON:
      core::railyard::search_by_type<core::goods_wagon> gw_search;
      fun_to_exec.push_back (gw_search);
      break;

    case PASSENGER_COACH:
      core::railyard::search_by_type<core::passenger_coach> pc_search;
      fun_to_exec.push_back (pc_search);
      break;

    case ALL:
    default:
      fun_to_exec.push_back (core::railyard::search_get_all ());
      break;
    }

  // Exec all function in vector (&& AND)
  return [fun_to_exec] (const core::railway_vehicle &vehicle) {
    bool status = true;

    for (auto it = fun_to_exec.begin (); it != fun_to_exec.end (); it++)
      status = status && (*it).operator() (vehicle);

    // If true the vehicle will be added to the return vector of searched
    // vehicles, otherwise the vehicle will not be added
    return status;
  };
}

}