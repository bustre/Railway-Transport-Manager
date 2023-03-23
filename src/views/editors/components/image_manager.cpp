#include "image_manager.h"

#include <QDir>
#include <QFileDialog>

namespace rtm::gui::editors::components
{

image_manager::image_manager (rtm::core::railway_vehicle &_r_vehicle,
                              const std::string &_project_path,
                              QWidget *parent)
    : QWidget (parent), r_vehicle (_r_vehicle), project_path (_project_path)
{
  layout_main = new QVBoxLayout (this);
  l_image_viewer = new QLabel ();
  le_image_path = new QLineEdit ();
  bt_change_image = new QPushButton ();
  bt_remove_image = new QPushButton ();

  le_image_path->setEnabled (false);
  l_image_viewer->setScaledContents (true);

  bt_change_image->setText (tr ("Select an image"));
  bt_remove_image->setText (tr ("Remove image"));

  QHBoxLayout *layout_button = new QHBoxLayout ();
  layout_button->addWidget (bt_change_image);
  layout_button->addWidget (bt_remove_image);

  layout_main->addWidget (l_image_viewer);
  layout_main->addStretch ();
  layout_main->addWidget (le_image_path);
  layout_main->addLayout (layout_button, 2);

  connect (bt_change_image, &QPushButton::clicked, this,
           &image_manager::select_image);
  connect (bt_remove_image, &QPushButton::clicked, this,
           &image_manager::clean_up_image);

  load_data ();
}

image_manager::~image_manager () { delete layout_main; }

/// Private Methods
void
image_manager::load_data () const
{
  set_image (QString::fromStdString (project_path + "/"
                                     + r_vehicle.get_image_path ()));
}

/// Public Methods
void
image_manager::save_data ()
{
  QDir dir (QString::fromStdString (project_path));
  const QString &path = le_image_path->text ();

  r_vehicle.set_image_path (dir.relativeFilePath (path).toStdString ());
}

/// Public slots
void
image_manager::clean_up_image () const
{
  set_image ("");
}

void
image_manager::select_image () const
{
  QString path
      = QFileDialog::getOpenFileName (nullptr, tr ("Select an image"), QString::fromStdString(project_path),
                                      "images (*.jpg *.png *.svg *.bmp)");

  if (!path.isEmpty ())
    set_image (path);
}

void
image_manager::set_image (const QString &path) const
{
  QPixmap image = QPixmap (path);

  if (image.isNull ())
    {
      le_image_path->setText ("");
      image = QPixmap (":assets/icons/image-missing.svg");
    }
  else
    le_image_path->setText (path);

  l_image_viewer->setPixmap (
      image.scaled (l_image_viewer->width (), l_image_viewer->height ()));
}
}