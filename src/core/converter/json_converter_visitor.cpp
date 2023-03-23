#include "json_converter_visitor.h"

#include "../electric_locomotive.h"
#include "../goods_wagon.h"
#include "../passenger_coach.h"
#include <QJsonArray>

namespace rtm::core::converter
{
visitor::visitor () : j_obj (nullptr) {}

void
visitor::visit_electric_locomotive (const electric_locomotive &e_locomotive)
{
  j_obj = new QJsonObject ();

  j_obj->insert ("type", "e_locomotive");
  j_obj->insert ("name", QJsonValue::fromVariant (QString::fromStdString (
                             e_locomotive.get_name ())));
  j_obj->insert ("id", QJsonValue::fromVariant (
                           QString::fromStdString (e_locomotive.get_id ())));
  j_obj->insert ("image_path",
                 QJsonValue::fromVariant (
                     QString::fromStdString (e_locomotive.get_image_path ())));
  j_obj->insert ("power", QJsonValue::fromVariant (e_locomotive.get_power ()));
  j_obj->insert ("max_speed",
                 QJsonValue::fromVariant (e_locomotive.get_max_speed ()));
  j_obj->insert ("length",
                 QJsonValue::fromVariant (e_locomotive.get_length ()));
  j_obj->insert ("weight",
                 QJsonValue::fromVariant (e_locomotive.get_weight ()));
  j_obj->insert ("max_carts", QJsonValue::fromVariant (
                                  e_locomotive.get_max_num_trailers ()));
  j_obj->insert (
      "engine_efficiency",
      QJsonValue::fromVariant (e_locomotive.get_engine_efficiency ()));
}

void
visitor::visit_passenger_coach (const passenger_coach &p_coach)
{
  j_obj = new QJsonObject ();

  j_obj->insert ("type", "p_coach");
  j_obj->insert ("name", QJsonValue::fromVariant (
                             QString::fromStdString (p_coach.get_name ())));
  j_obj->insert ("id", QJsonValue::fromVariant (
                           QString::fromStdString (p_coach.get_id ())));
  j_obj->insert ("image_path",
                 QJsonValue::fromVariant (
                     QString::fromStdString (p_coach.get_image_path ())));
  j_obj->insert ("weight", QJsonValue::fromVariant (p_coach.get_weight ()));
  j_obj->insert ("length", QJsonValue::fromVariant (p_coach.get_length ()));
  j_obj->insert ("max_speed",
                 QJsonValue::fromVariant (p_coach.get_max_speed ()));
  j_obj->insert ("class", QJsonValue::fromVariant (
                              QString::fromStdString (p_coach.get_class ())));
  j_obj->insert ("seats", QJsonValue::fromVariant (p_coach.get_seats ()));
}

void
visitor::visit_goods_wagon (const goods_wagon &g_wagon)
{
  j_obj = new QJsonObject ();
  QJsonArray j_limit_panel;
  auto limit_panel = g_wagon.get_load_limit_panel ();
  auto category = limit_panel.get_line_categorys ();

  j_obj->insert ("type", "g_wagon");
  j_obj->insert ("name", QJsonValue::fromVariant (
                             QString::fromStdString (g_wagon.get_name ())));
  j_obj->insert ("id", QJsonValue::fromVariant (
                           QString::fromStdString (g_wagon.get_id ())));
  j_obj->insert ("image_path",
                 QJsonValue::fromVariant (
                     QString::fromStdString (g_wagon.get_image_path ())));
  j_obj->insert ("weight", QJsonValue::fromVariant (g_wagon.get_weight ()));
  j_obj->insert ("length", QJsonValue::fromVariant (g_wagon.get_length ()));
  j_obj->insert ("max_speed",
                 QJsonValue::fromVariant (g_wagon.get_max_speed ()));
  j_obj->insert ("covered", QJsonValue::fromVariant (g_wagon.is_covered ()));
  j_obj->insert ("floor_space",
                 QJsonValue::fromVariant (g_wagon.get_floor_space ()));
  j_obj->insert ("load_capacity",
                 QJsonValue::fromVariant (g_wagon.get_load_capacity ()));

  for (auto it = category.begin (); it != category.end (); it++)
    {
      QJsonObject j_limit_object;
      j_limit_object.insert ("category", QJsonValue::fromVariant (
                                             QString::fromStdString ((*it))));
      j_limit_object.insert (
          "max_load", QJsonValue::fromVariant (limit_panel.get_limit (*it)));
      j_limit_panel.push_back (j_limit_object);
    }

  j_obj->insert ("load_limit_panel", j_limit_panel);
}

QJsonObject *
visitor::get_json_object ()
{
  return j_obj;
}
}