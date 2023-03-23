#ifndef PASSENGER_COACH_INFO_MANAGER_H
#define PASSENGER_COACH_INFO_MANAGER_H

#include "../../../core/passenger_coach.h"
#include "../../../core/railyard.h"

#include "railroad_car_info_manager.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>

namespace rtm::gui::editors::components
{

class passenger_coach_info_manager : public railroad_car_info_manager
{
  Q_OBJECT

private:
  core::passenger_coach &passenger_coach;

  QLineEdit *input_class;
  QSpinBox *input_seats;

  void load_data () const;

public:
  passenger_coach_info_manager (const core::railyard &ryard,
                                core::passenger_coach &passenger_coach,
                                QWidget *parent = nullptr);

  ~passenger_coach_info_manager () override = default;

  void save_data () override;
};
}

#endif