#include "railyard.h"

#include <QJsonArray>
#include <algorithm>

namespace rtm::core
{

railyard::~railyard ()
{
  for (auto it = r_vehicles.begin (); it != r_vehicles.end (); it++)
    delete *it;
}

railyard::railyard (const railyard &ry)
{
  // Copy new vector
  for (auto cit = ry.r_vehicles.begin (); cit != ry.r_vehicles.end (); cit++)
    this->add (**cit);
}

void
railyard::add (const railway_vehicle &r_vehicle)
{
  /// FIXME: too heavy for a simple id search?
  if (!search (search_by_id_equal (r_vehicle.get_id ())).is_empty ())
    throw std::invalid_argument ("Railway vheicle whit id: \""
                                 + r_vehicle.get_id () + "\" already exist");

  r_vehicles.push_back (r_vehicle.clone ());
}

void
railyard::erase (const railway_vehicle &r_v)
{
  for (auto it = r_vehicles.begin (); it != r_vehicles.end (); it++)
    if ((*it)->get_id () == (r_v.get_id ()))
      {
        delete *it;
        r_vehicles.erase (it);
        return;
      }
}

bool
railyard::replace (const railway_vehicle &r_v)
{
  const std::string &rv_id = r_v.get_id ();

  for (auto it = r_vehicles.begin (); it != r_vehicles.end (); it++)
    if ((*it)->get_id () == rv_id)
      {
        delete *it;
        *it = r_v.clone ();
        return true;
      }

  return false;
}

railway_vehicle *
railyard::take (const railway_vehicle &r_vehicle)
{
  for (auto it = r_vehicles.begin (); it != r_vehicles.end (); it++)
    if ((*it)->get_id () == (r_vehicle.get_id ()))
      {
        railway_vehicle *v = *it;
        r_vehicles.erase (it);
        return v;
      }

  return nullptr;
}

railyard &
railyard::operator= (const railyard &ry)
{
  if (this != &ry)
    {
      // Clear vector
      for (auto it = r_vehicles.begin (); it != r_vehicles.end (); it++)
        delete *it;
      r_vehicles.clear ();

      // Copy new vector
      for (auto cit = ry.r_vehicles.begin (); cit != ry.r_vehicles.end ();
           cit++)
        this->add (**cit);
    }

  return *this;
}

ctr::vector<const railway_vehicle *>
railyard::search (
    const std::function<bool (const railway_vehicle &)> &fun) const
{
  ctr::vector<const railway_vehicle *> aux;

  for (auto it = r_vehicles.begin (); it != r_vehicles.end (); it++)
    if (fun (**it))
      aux.push_back (*it);

  return aux;
}

QJsonDocument
railyard::to_json_document () const
{
  QJsonDocument doc;
  QJsonArray data;

  for (auto it = r_vehicles.begin (); it != r_vehicles.end (); it++)
    data.push_back (*converter::converter::from_object (**it));

  doc.setArray (data);
  return doc;
}

void
railyard::form_json_document (const QJsonDocument &doc)
{
  if (doc.isEmpty ())
    throw converter::converter::error::INVALID_FORMAT;

  QJsonArray data = doc.array ();

  for (auto it = data.begin (); it != data.end (); it++)
    {
      auto aux = converter::converter::from_json_object (it->toObject ());
      add (*aux);
      delete aux;
    }
}

}