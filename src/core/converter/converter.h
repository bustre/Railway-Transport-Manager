#ifndef CONVERTER_H
#define CONVERTER_H

#include "../electric_locomotive.h"
#include "../goods_wagon.h"
#include "../passenger_coach.h"
#include "../railway_vehicle.h"

#include "json_converter_visitor.h"
#include <QJsonObject>

namespace rtm::core::converter
{
class converter
{
private:
  static electric_locomotive *read_electric_locomotive (const QJsonObject &j_obj);
  static passenger_coach *read_passenger_coach (const QJsonObject &j_obj);
  static goods_wagon *read_goods_wagon (const QJsonObject &j_obj);

public:
  enum error
  {
    GENERIC_ERROR,
    INVALID_DATA,
    INVALID_FORMAT
  };

  static QJsonObject *from_object (const railway_vehicle &r_vehicle);
  static railway_vehicle *from_json_object (const QJsonObject &j_obj);
};
}

#endif