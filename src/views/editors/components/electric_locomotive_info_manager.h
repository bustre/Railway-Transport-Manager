#ifndef ELECTRIC_LOCOMOTIVE_INFO_MANAGER_H
#define ELECTRIC_LOCOMOTIVE_INFO_MANAGER_H

#include "../../../core/electric_locomotive.h"

#include "locomotive_info_manager.h"
#include <QDoubleSpinBox>
#include <QWidget>

namespace rtm::gui::editors::components
{

class electric_locomotive_info_manager : public locomotive_info_manager
{
  Q_OBJECT

private:
  core::electric_locomotive &e_locomotive;

  QDoubleSpinBox *input_efficiency;

  void load_data () const;

public:
  electric_locomotive_info_manager (const core::railyard &ryard,
                                    core::electric_locomotive &e_locomotive,
                                    QWidget *parent = nullptr);

  void save_data () override;
};
}

#endif