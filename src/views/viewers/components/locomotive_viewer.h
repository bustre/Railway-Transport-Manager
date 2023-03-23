#ifndef LOCOMOTIVE_VIEWER_H
#define LOCOMOTIVE_VIEWER_H

#include "../../../core/vehicle_types.h"
#include "railway_vehicle_viewer.h"

#include <QLabel>
#include <QWidget>

namespace rtm::gui::viewers::components
{

class locomotive_viewer : public railway_vehicle_viewer
{
  Q_OBJECT

private:
  const core::locomotive &locomotive;

  QLabel *l_power;
  QLabel *l_max_num_trailers;
  QLabel *l_tractive_force;

  void load_data () const;

public:
  explicit locomotive_viewer (const core::locomotive &locomotive,
                              const std::string &project_path,
                              QWidget *parent = nullptr);

  ~locomotive_viewer () override = 0;
};

}

#endif