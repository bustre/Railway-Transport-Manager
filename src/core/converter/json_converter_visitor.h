#ifndef JSON_CONVERTER_VISITOR_H
#define JSON_CONVERTER_VISITOR_H

#include "../generic_visitor_interface.h"
#include <QJsonObject>

namespace rtm::core::converter
{
class visitor : public const_visitor_interface
{
private:
  QJsonObject *j_obj;

public:
  visitor ();

  QJsonObject *get_json_object ();

  void visit_electric_locomotive (const electric_locomotive &e_locomotive) override;
  void visit_passenger_coach (const passenger_coach &p_coach) override;
  void visit_goods_wagon (const goods_wagon &g_wagon) override;
};
}

#endif