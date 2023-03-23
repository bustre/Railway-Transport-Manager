#ifndef SEARCH_BAR_H
#define SEARCH_BAR_H

#include "../../../core/railyard.h"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>

namespace rtm::gui::viewers::components
{

class search_bar : public QWidget
{
  Q_OBJECT

private:
  enum vehicle_types
  {
    ALL,
    RAILROAD_CAR,
    LOCOMOTIVE,
    ELECTRIC_LOCOMOTIVE,
    GOODS_WAGON,
    PASSENGER_COACH
  };

  QVBoxLayout *layout_main;
  QLineEdit *le_search_name;
  QLineEdit *le_search_id;
  QComboBox *cb_search_type;
  
  void load_vehicle_types () const;
  void clean_up_search ();

public:
  search_bar (QWidget *parent = nullptr);

  std::function<bool (const core::railway_vehicle &)>
  get_search_function () const;

signals:
  void search_request ();
};

}

#endif