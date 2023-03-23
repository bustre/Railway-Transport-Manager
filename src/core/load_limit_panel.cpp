#include "load_limit_panel.h"
#include <stdexcept>

namespace rtm::core
{

/// LOAD LIMIT PANEL
load_limit_panel::load_limit::load_limit (const std::string &category,
                                          double _max_load)
{
  if (_max_load < 0)
    throw std::invalid_argument (
        "Load limit cannot be less than 0 Kg. The value I got is: "
        + std::to_string (max_load) + " kg.");
  line_category = category;
  max_load = _max_load;
}

void
load_limit_panel::add_limit (const std::string &category, double load)
{
  load_limit l_limit (category, load);

  // Keep lex-order
  for (auto it = table.begin (); it != table.end (); it++)
    if ((*it).line_category > category)
      {
        table.insert (it, l_limit);
        return;
      }

  table.push_back (l_limit);
}

void
load_limit_panel::set_limit (const std::string &category, double load)
{
  for (auto it = table.begin (); it != table.end (); it++)
    if ((*it).line_category == category)
      {
        (*it).max_load = load;
        return;
      }
}

void
load_limit_panel::remove_limit (const std::string &category)
{
  for (auto it = table.begin (); it != table.end (); it++)
    if ((*it).line_category == category)
      {
        table.erase (it);
        return;
      }
}

double
load_limit_panel::get_limit (const std::string &category) const
{
  for (auto it = table.begin (); it != table.end (); it++)
    if ((*it).line_category == category)
      {
        return (*it).max_load;
      }

  return -1;
}

ctr::vector<std::string>
load_limit_panel::get_line_categorys () const
{
  ctr::vector<std::string> categorys;

  for (auto it = table.begin (); it != table.end (); it++)
    categorys.push_back ((*it).line_category);

  return categorys;
}
}