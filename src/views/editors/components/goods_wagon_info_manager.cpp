#include "goods_wagon_info_manager.h"
#include <limits>

#include <QFormLayout>
#include <QIcon>
#include <QInputDialog>
#include <QMessageBox>
#include <QTableWidgetItem>

namespace rtm::gui::editors::components
{
goods_wagon_info_manger::goods_wagon_info_manger (const core::railyard &ryard,
                                                  core::goods_wagon &_g_wagon,
                                                  QWidget *parent)
    : railroad_car_info_manager (ryard, _g_wagon, parent), g_wagon (_g_wagon)
{
  input_covered = new QCheckBox;
  input_floor_space = new QDoubleSpinBox;
  input_load_capacity = new QDoubleSpinBox;
  input_load_limit_table = new QTableWidget;
  bt_new_column = new QPushButton;
  bt_remove_column = new QPushButton;
  lb_satus_table = new QLabel;

  QWidget *page = new QWidget;
  QVBoxLayout *layout_main = new QVBoxLayout (page);
  QFormLayout *info_layout = new QFormLayout;

  input_floor_space->setRange (0, std::numeric_limits<double>::max ());
  input_load_capacity->setRange (0, std::numeric_limits<double>::max ());

  input_covered->setText (tr ("The freight car is covered."));

  info_layout->addRow (input_covered);
  info_layout->addRow (new QLabel (tr ("Floor area (m^2):")),
                       input_floor_space);
  info_layout->addRow (new QLabel (tr ("Load capacity (m^3):")),
                       input_load_capacity);

  QVBoxLayout *layout_v_limit_table = new QVBoxLayout ();
  QHBoxLayout *layout_h_limit_table = new QHBoxLayout;

  input_load_limit_table->setColumnCount (0);
  input_load_limit_table->setRowCount (1);
  input_load_limit_table->setVerticalHeaderLabels (QStringList ("S"));
  input_load_limit_table->setHorizontalHeaderLabels (column_category);

  bt_new_column->setText (tr ("New line category"));
  bt_remove_column->setText (tr ("Remove line category"));

  layout_h_limit_table->addWidget (bt_new_column);
  layout_h_limit_table->addWidget (bt_remove_column);

  QLabel *label_panel_title = new QLabel (tr ("\nUIC load limit table."));
  label_panel_title->setWordWrap (true);
  QFont l_panel_limit_font;
  l_panel_limit_font.setBold (true);
  l_panel_limit_font.setPixelSize (16);
  label_panel_title->setFont (l_panel_limit_font);

  QLabel *label_panel_text = new QLabel (tr (
      "Use the button below to add columns to the table. Cells accept only "
      "numbers with commas. To change a value click on the desired cell, the "
      "value entered is in tons.\nExample: line A1 --> maximum weight 30 t."));
  label_panel_text->setWordWrap (true);

  lb_satus_table->setStyleSheet ("QLabel { color: red }");

  layout_v_limit_table->addWidget (label_panel_title);
  layout_v_limit_table->addWidget (label_panel_text);
  layout_v_limit_table->addWidget (input_load_limit_table);
  layout_v_limit_table->addWidget (lb_satus_table);
  layout_v_limit_table->addLayout (layout_h_limit_table);

  connect (bt_new_column, &QPushButton::clicked, this,
           &goods_wagon_info_manger::add_category);
  connect (bt_remove_column, &QPushButton::clicked, this,
           &goods_wagon_info_manger::remove_category);
  connect (input_load_limit_table, &QTableWidget::cellChanged, this,
           &goods_wagon_info_manger::update_data_status);

  layout_main->addLayout (info_layout);
  layout_main->addLayout (layout_v_limit_table);

  add_page (page, tr ("Specific information"));

  load_data ();
  goods_wagon_info_manger::update_data_status ();
}

void
goods_wagon_info_manger::load_categorys_line (
    const ctr::vector<std::string> &v_categorys)
{
  for (auto it = v_categorys.begin (); it != v_categorys.end (); it++)
    column_category.push_back (QString::fromStdString (*it));
}

void
goods_wagon_info_manger::load_load_limit_data ()
{
  int column = 0;

  for (auto it = column_category.begin (); it != column_category.end (); it++)
    {
      double value = l_limit_panel.get_limit ((*it).toStdString ());
      QTableWidgetItem *item = new QTableWidgetItem ();
      item->setText (QString::number (value));
      input_load_limit_table->setColumnCount (column + 1);
      input_load_limit_table->setItem (0, column, item);
      column++;
    }
}

void
goods_wagon_info_manger::load_data ()
{
  input_covered->setChecked (g_wagon.is_covered ());
  input_floor_space->setValue (g_wagon.get_floor_space ());
  input_load_capacity->setValue (g_wagon.get_load_capacity ());

  l_limit_panel = g_wagon.get_load_limit_panel ();

  load_categorys_line (l_limit_panel.get_line_categorys ());
  load_load_limit_data ();

  input_load_limit_table->setHorizontalHeaderLabels (column_category);
}

bool
goods_wagon_info_manger::check_load_limit_table () const
{
  int count = input_load_limit_table->columnCount () - 1;
  while (count >= 0)
    {
      bool is_okey;
      auto item = input_load_limit_table->item (0, count);

      // Item can be null if was created but not setted by the user
      is_okey = item && item->text ().toDouble (&is_okey);

      if (!is_okey)
        {
          lb_satus_table->setText (
              QString (tr ("Error! Invalid data in the column: "))
              + QString::number (count + 1));
          return false;
        }

      count--;
    }

  lb_satus_table->setText ("");
  return true;
}

void
goods_wagon_info_manger::update_data_status ()
{
  railroad_car_info_manager::update_data_status ();
  set_data_status (get_data_status () && check_load_limit_table ());
}

void
goods_wagon_info_manger::gen_load_limit_table ()
{
  l_limit_panel = core::load_limit_panel ();
  int count = input_load_limit_table->columnCount () - 1;

  while (count >= 0)
    {
      auto item = input_load_limit_table->item (0, count);
      l_limit_panel.add_limit (column_category.at (count).toStdString (),
                               item->text ().toDouble ());
      count--;
    }
}

void
goods_wagon_info_manger::save_data ()
{
  if (!get_data_status ())
    return;

  railroad_car_info_manager::save_data ();

  g_wagon.set_covered (input_covered->checkState () == Qt::Checked);
  g_wagon.set_floar_space (input_floor_space->value ());
  g_wagon.set_load_capacity (input_load_capacity->value ());

  gen_load_limit_table ();

  g_wagon.set_load_limit_panel (l_limit_panel);
}

void
goods_wagon_info_manger::add_category ()
{
  bool is_okey;
  const QString &name
      = QInputDialog::getText (this, tr ("New line category"),
                               tr ("Insert the name of new line category:"),
                               QLineEdit::Normal, "", &is_okey);

  if (!is_okey)
    return;

  if (!name.isEmpty () && !column_category.contains (name))
    {
      column_category.push_back (name);
      input_load_limit_table->setColumnCount (
          input_load_limit_table->columnCount () + 1);
      input_load_limit_table->setHorizontalHeaderLabels (column_category);
      update_data_status ();
    }
  else
    {
      QMessageBox msg_box;
      msg_box.setWindowTitle (tr ("Error"));
      msg_box.setIcon (QMessageBox::Icon::Critical);
      msg_box.setText (tr ("The name of the new category cannot be an empty "
                           "string and must not already exist in the table."));
      msg_box.exec ();
    }
}

void
goods_wagon_info_manger::remove_category ()
{
  int column = input_load_limit_table->currentColumn ();

  if (column >= 0)
    {
      input_load_limit_table->removeColumn (column);
      column_category.removeAt (column);
      input_load_limit_table->setHorizontalHeaderLabels (column_category);
      update_data_status ();
    }
  else
    {
      QMessageBox msg_box;
      msg_box.setWindowTitle (tr ("Error"));
      msg_box.setIcon (QMessageBox::Icon::Critical);
      msg_box.setText (
          tr ("No category has been selected. The action has been canceled."));
      msg_box.exec ();
    }
}

}