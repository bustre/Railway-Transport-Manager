#ifndef GOODS_WAGON_INFO_MANAGER_H
#define GOODS_WAGON_INFO_MANAGER_H

#include "../../../core/goods_wagon.h"
#include "railroad_car_info_manager.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>

namespace rtm::gui::editors::components
{
class goods_wagon_info_manger : public railroad_car_info_manager
{
  Q_OBJECT

private:
  core::goods_wagon &g_wagon;
  core::load_limit_panel l_limit_panel;
  QStringList column_category;

  QCheckBox *input_covered;
  QDoubleSpinBox *input_floor_space;
  QDoubleSpinBox *input_load_capacity;
  QTableWidget *input_load_limit_table;
  QPushButton *bt_new_column;
  QPushButton *bt_remove_column;
  QLabel *lb_satus_table;

  void load_categorys_line (const ctr::vector<std::string> &v_categorys);
  void load_load_limit_data ();
  void gen_load_limit_table ();
  void load_data ();

  bool check_load_limit_table () const;

public:
  goods_wagon_info_manger (const core::railyard &ryard,
                           core::goods_wagon &g_wagon,
                           QWidget *parent = nullptr);

  ~goods_wagon_info_manger () override = default;

  void update_data_status () override;
  void save_data () override;

public slots:
  void add_category ();
  void remove_category ();
};
}

#endif