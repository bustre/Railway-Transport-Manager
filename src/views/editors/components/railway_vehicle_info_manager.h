#ifndef RAILWAY_VHEICLE_INFO_MANAGER_H
#define RAILWAY_VHEICLE_INFO_MANAGER_H

#include "../../../core/railway_vehicle.h"
#include "../../../core/railyard.h"

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

namespace rtm::gui::editors::components
{
class railway_vehicle_info_manager : public QWidget
{
  Q_OBJECT

private:
  core::railway_vehicle &r_vehicle;
  bool valid_data;

  QVBoxLayout *layout_main;
  QLineEdit *input_name;
  QLineEdit *input_id;
  QDoubleSpinBox *input_weight;
  QSpinBox *input_speed;
  QDoubleSpinBox *input_length;
  QLabel *lb_id;
  QLabel *lb_name;

  QTabWidget *main_tab_widget;

  void load_data () const;
  bool check_id () const;
  bool check_name () const;

protected:
  const rtm::core::railyard &ryard;

  void set_data_status (bool status);
  void add_page (QWidget *page, const QString &name);

public:
  railway_vehicle_info_manager (const core::railyard &ryard,
                                core::railway_vehicle &r_vehicle,
                                QWidget *parent = nullptr);

  virtual ~railway_vehicle_info_manager () = 0;

  virtual void update_data_status ();
  bool get_data_status () const;

  // save data iff valid_date == true
  virtual void save_data ();

signals:
  void data_status_change (bool is_valid);
};
}

#endif