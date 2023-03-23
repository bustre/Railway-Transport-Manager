#ifndef LOAD_LIMIT_PANEL_H
#define LOAD_LIMIT_PANEL_H

/*
 * DOCS: https://it.wikipedia.org/wiki/Peso_per_asse (Italian)
 */

#include "../utils/vector.h"
#include <string>

namespace rtm::core
{
class load_limit_panel
{
private:
  class load_limit // UIC load limit panel
  {
  public:
    std::string line_category;
    double max_load; // Row S

    load_limit () = default;
    load_limit (const std::string &category, double max_load);
  };

  ctr::vector<load_limit> table;

public:
  load_limit_panel () = default;

  void add_limit (const std::string &category, double load);
  void set_limit (const std::string &category, double load);
  void remove_limit (const std::string &category);

  // If category is not in table then "get_limit()"" return -1
  double get_limit (const std::string &category) const;
  ctr::vector<std::string> get_line_categorys () const;
};
}

#endif