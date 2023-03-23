#ifndef GOODS_WAGON_VIEWER_H
#define GOODS_WAGON_VIEWER_H

#include "../../../core/goods_wagon.h"
#include "../../../utils/vector.h"
#include "railroad_car_viewer.h"

#include <QLabel>
#include <QStringList>
#include <QTableWidget>
#include <QWidget>

namespace rtm::gui::viewers::components
{

class goods_wagon_viewer : public railroad_car_viewer
{
  Q_OBJECT

private:
  const core::goods_wagon &g_wagon;

  QLabel *l_roof;
  QLabel *l_floor_space;
  QLabel *l_load_capacity;
  QTableWidget *table_load_limit;

  void load_data () const;
  void gen_table_header (QStringList &header,
                         const ctr::vector<std::string> &category) const;

public:
  goods_wagon_viewer (const core::goods_wagon &g_wagon,
                      const std::string &project_path,
                      QWidget *parent = nullptr);

  ~goods_wagon_viewer () override = default;
};

}

#endif