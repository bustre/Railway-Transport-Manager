#include "railway_vehicle_viewer.h"

#include <QPixmap>
#include <QPushButton>
#include <QString>

#include "../components/railway_vehicle_viewer.h"

namespace rtm::gui::viewers::components
{

railway_vehicle_viewer::railway_vehicle_viewer (
    const core::railway_vehicle &_r_vehicle, const std::string &_project_path,
    QWidget *parent)
    : QWidget (parent), r_vehicle (_r_vehicle), project_path (_project_path)
{
  layout_main = new QVBoxLayout (this);
  layout_info = new QFormLayout;
  l_image = new QLabel;
  bt_close = new QPushButton ();

  l_name = new QLabel ();
  l_id = new QLabel ();
  l_weight = new QLabel ();
  l_max_speed = new QLabel ();
  l_length = new QLabel ();

  l_image->setScaledContents (true);
  l_image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

  bt_close->setIcon (QIcon (":assets/icons/close.svg"));
  bt_close->setIconSize (QSize (24, 24));
  bt_close->setFixedSize (24, 24);
  bt_close->setFlat (true);

  layout_info->setLabelAlignment (Qt::AlignLeft | Qt::AlignTop);
  layout_info->addRow (new QLabel (tr ("Name:")), l_name);
  layout_info->addRow (new QLabel (tr ("Id:")), l_id);
  layout_info->addRow (new QLabel (tr ("Weight (Kg):")), l_weight);
  layout_info->addRow (new QLabel (tr ("Max speed (Km/h):")), l_max_speed);
  layout_info->addRow (new QLabel (tr ("Length (m):")), l_length);
  l_image->setAlignment (Qt::AlignCenter);

  layout_main->addWidget (bt_close, 0, Qt::AlignRight | Qt::AlignTop);
  layout_main->addWidget (l_image, 1, Qt::AlignCenter);
  layout_main->addLayout (layout_info, 1);

  connect (bt_close, &QPushButton::clicked, this,
           &railway_vehicle_viewer::close);

  load_data ();
}

railway_vehicle_viewer::~railway_vehicle_viewer () { delete layout_main; }

void
railway_vehicle_viewer::load_data () const
{
  QPixmap p_map;
  p_map.load (QString::fromStdString (project_path + "/"
                                      + r_vehicle.get_image_path ()));

  if (p_map.isNull ())
    {
      l_image->setPixmap (QPixmap (":assets/icons/image-missing.svg"));
      l_image->setScaledContents (false); //Avoid stretch the image
    }
  else
    l_image->setPixmap (p_map);

  l_name->setText (QString::fromStdString (r_vehicle.get_name ()));
  l_id->setText (QString::fromStdString (r_vehicle.get_id ()));
  l_weight->setText (QString::number (r_vehicle.get_weight ()));
  l_max_speed->setText (QString::number (r_vehicle.get_max_speed ()));
  l_length->setText (QString::number (r_vehicle.get_length ()));
}

void
railway_vehicle_viewer::add_row (QWidget *w_left, QWidget *w_right) const
{
  layout_info->addRow (w_left, w_right);
}

void
railway_vehicle_viewer::add_layout (QLayout *l) const
{
  layout_main->addLayout (l);
}
}