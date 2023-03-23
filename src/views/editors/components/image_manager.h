#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include "../../../core/railway_vehicle.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

namespace rtm::gui::editors::components
{

class image_manager : public QWidget
{
  Q_OBJECT

private:
  core::railway_vehicle &r_vehicle;
  const std::string &project_path;

  QVBoxLayout *layout_main;
  QLabel *l_image_viewer;
  QLineEdit *le_image_path;
  QPushButton *bt_change_image;
  QPushButton *bt_remove_image;

  void load_data () const;

public:
  image_manager (rtm::core::railway_vehicle &r_vehicle,
                 const std::string &project_path,
                 QWidget *parent = nullptr);

  ~image_manager ();

  void save_data ();

public slots:
  void clean_up_image () const;
  void select_image () const;
  void set_image (const QString &path) const;
};

}

#endif