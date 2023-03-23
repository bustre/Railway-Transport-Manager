#ifndef ELECTRIC_LOCOMOTIVE_VIEWER_H
#define ELECTRIC_LOCOMOTIVE_VIEWER_H

#include "../../../core/electric_locomotive.h"
#include "locomotive_viewer.h"

#include <QLabel>
#include <QWidget>

namespace rtm::gui::viewers::components
{

class electric_locomotive_viewer : public locomotive_viewer
{
  Q_OBJECT

private:
  const core::electric_locomotive &e_locomotive;

  QLabel *l_engine_efficiency;

  void load_data () const;

public:
  electric_locomotive_viewer (const core::electric_locomotive &e_locomotive,
                              const std::string &project_path,
                              QWidget *parent = nullptr);

  ~electric_locomotive_viewer () override = default;
};

}

#endif