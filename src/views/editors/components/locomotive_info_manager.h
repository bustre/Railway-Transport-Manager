#ifndef LOCOMOTIVE_INFO_MANAGER_H
#define LOCOMOTIVE_INFO_MANAGER_H

#include "../../../core/vehicle_types.h"

#include "railway_vehicle_info_manager.h"
#include <QLabel>
#include <QSpinBox>
#include <QWidget>

namespace rtm::gui::editors::components
{

class locomotive_info_manager : public railway_vehicle_info_manager
{
  Q_OBJECT

private:
  core::locomotive &locomotive;

  QSpinBox *input_power;
  QSpinBox *input_max_trailers;

  void load_data () const;

public:
  explicit locomotive_info_manager (const core::railyard &ryard,
                                    core::locomotive &locomotive,
                                    QWidget *parent = nullptr);

  ~locomotive_info_manager () override = 0;

  void save_data () override;
};
}

#endif