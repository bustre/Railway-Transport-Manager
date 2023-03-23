#include "goods_wagon_viewer.h"

#include <QTableWidgetItem>
#include <QVBoxLayout>

namespace rtm::gui::viewers::components
{
goods_wagon_viewer::goods_wagon_viewer (const core::goods_wagon &_g_wagon,
                                        const std::string &project_path,
                                        QWidget *parent)
    : railroad_car_viewer (_g_wagon, project_path, parent), g_wagon (_g_wagon)
{
  l_roof = new QLabel ();
  l_floor_space = new QLabel ();
  l_load_capacity = new QLabel ();
  table_load_limit = new QTableWidget ();

  add_row (new QLabel (tr ("Roof?")), l_roof);
  add_row (new QLabel (tr ("Floor area (m^2):")), l_floor_space);
  add_row (new QLabel (tr ("Load capacity (m^3):")), l_load_capacity);

  QVBoxLayout *layout_table = new QVBoxLayout;
  layout_table->addWidget (new QLabel (tr ("UIC Load Limits Panel")));
  layout_table->addWidget (table_load_limit);

  table_load_limit->setColumnCount (0);
  table_load_limit->setRowCount (1);
  table_load_limit->setVerticalHeaderLabels (QStringList ("S"));
  table_load_limit->setEditTriggers (QAbstractItemView::NoEditTriggers);

  add_layout (layout_table);
  load_data ();
}

void
goods_wagon_viewer::gen_table_header (
    QStringList &header, const ctr::vector<std::string> &category) const
{
  for (auto it = category.begin (); it != category.end (); it++)
    header.push_back (QString::fromStdString (*it));
}

void
goods_wagon_viewer::load_data () const
{
  if (g_wagon.is_covered ())
    l_roof->setText (tr ("Yes"));
  else
    l_roof->setText (tr ("No"));

  l_floor_space->setText (QString::number (g_wagon.get_floor_space ()));
  l_load_capacity->setText (QString::number (g_wagon.get_load_capacity ()));

  // Table
  auto l_limit_panel = g_wagon.get_load_limit_panel ();
  QStringList table_header;
  gen_table_header (table_header, l_limit_panel.get_line_categorys ());

  int column = 0;

  for (auto it = table_header.begin (); it != table_header.end (); it++)
    {
      double value = l_limit_panel.get_limit ((*it).toStdString ());
      QTableWidgetItem *item = new QTableWidgetItem ();
      item->setText (QString::number (value));
      table_load_limit->setColumnCount (column + 1);
      table_load_limit->setItem (0, column, item);
      column++;
    }

  table_load_limit->setHorizontalHeaderLabels (table_header);
}

}