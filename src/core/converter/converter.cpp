#include "converter.h"

#include <QJsonArray>
#include <iostream>
#include <string>

namespace rtm::core::converter
{
/// Private methods
electric_locomotive *
converter::read_electric_locomotive (const QJsonObject &j_obj)
{
  return new electric_locomotive (
      j_obj.value ("name").toString ().toStdString (),
      j_obj.value ("id").toString ().toStdString (),
      j_obj.value ("image_path").toString ().toStdString (),
      j_obj.value ("power").toVariant ().toUInt (),
      j_obj.value ("max_speed").toVariant ().toUInt (),
      j_obj.value ("length").toDouble (), j_obj.value ("weight").toDouble (),
      j_obj.value ("max_carts").toVariant ().toUInt (),
      j_obj.value ("engine_efficiency").toDouble ());
}

passenger_coach *
converter::read_passenger_coach (const QJsonObject &j_obj)
{
  return new passenger_coach (
      j_obj.value ("name").toString ().toStdString (),
      j_obj.value ("id").toString ().toStdString (),
      j_obj.value ("image_path").toString ().toStdString (),
      j_obj.value ("weight").toDouble (),
      j_obj.value ("max_speed").toVariant ().toUInt (),
      j_obj.value ("length").toDouble (),
      j_obj.value ("class").toString ().toStdString (),
      j_obj.value ("seats").toVariant ().toUInt ());
}

goods_wagon *
converter::read_goods_wagon (const QJsonObject &j_obj)
{
  load_limit_panel l_limit_panel;
  QJsonArray j_array = j_obj.value ("load_limit_panel").toArray ();

  for (auto it = j_array.begin (); it != j_array.end (); it++)
    {
      auto temp_obj = it->toObject ();
      l_limit_panel.add_limit (
          temp_obj.value ("category").toString ().toStdString (),
          temp_obj.value ("max_load").toDouble ());
    }

  return new goods_wagon (
      j_obj.value ("name").toString ().toStdString (),
      j_obj.value ("id").toString ().toStdString (),
      j_obj.value ("image_path").toString ().toStdString (),
      j_obj.value ("weight").toDouble (),
      j_obj.value ("max_speed").toVariant ().toUInt (),
      j_obj.value ("length").toDouble (), j_obj.value ("covered").toBool (),
      j_obj.value ("floor_space").toDouble (),
      j_obj.value ("load_capacity").toDouble (), l_limit_panel);
}

/// Public methods
QJsonObject *
converter::from_object (const railway_vehicle &r_vehicle)
{
  visitor p_v;
  r_vehicle.accept (p_v);
  return p_v.get_json_object ();
}

railway_vehicle *
converter::from_json_object (const QJsonObject &j_obj)
{

  const std::string &type = j_obj.value ("type").toString ().toStdString ();

  try
    {
      if (type == "e_locomotive")
        return read_electric_locomotive (j_obj);
      else if (type == "p_coach")
        return read_passenger_coach (j_obj);
      else if (type == "g_wagon")
        return read_goods_wagon (j_obj);
      else
        throw std::invalid_argument ("Reading a invalid vehicle type: \""
                                     + type + "\".");
    }
  catch (std::invalid_argument &e)
    {
      std::cerr << e.what () << std::endl; // Console error output
      throw INVALID_DATA;
    }
  catch (...)
    {
      throw GENERIC_ERROR;
    }
}

}