#ifndef RAILYARD_H
#define RAILYARD_H

#include "../utils/vector.h"
#include "converter/converter.h"
#include "railway_vehicle.h"
#include <QJsonDocument>
#include <functional>
#include <string>

namespace rtm::core
{

class railyard
{
private:
  /*Invariants:
    -ID cannot be empty
    -The ID of each vehicle must be unique.
  */
  ctr::vector<railway_vehicle *> r_vehicles;

public:
  railyard () = default;
  ~railyard ();
  railyard (const railyard &ry);

  void add (const railway_vehicle &r_vehicle);
  void erase (const railway_vehicle &r_vehicle);

  // POST:
  //      If the vehicle to be replaced is not found return false, otherwise
  //      return true.
  bool replace (const railway_vehicle &r_v);

  // POST:
  //      remove the object from r_vehicles without destroying it, and return
  //      a pointer to the object, the ownership is passed to the caller.
  railway_vehicle *take (const railway_vehicle &r_vehicle);

  railyard &operator= (const railyard &ry);

  QJsonDocument to_json_document () const;
  void form_json_document (const QJsonDocument &j_doc);

  // "fun" is a functor or a lambda expression with const
  // railway_vehicle& as argument and return a type boolean.
  ctr::vector<const railway_vehicle *>
  search (const std::function<bool (const railway_vehicle &)> &fun) const;

  /// Search functions
  class search_get_all
  {
  public:
    bool
    operator() (const railway_vehicle &r_vehicle) const
    {
      // FIXME: (find a better solution)
      // I dislike this, but it is the only method to accomplish this without
      // the compiler raising a warning for an unused parameter.
      return !r_vehicle.get_id ().empty ();
      //return true;
    }
  };

  class search_by_id_equal
  {
  private:
    const std::string id;

  public:
    search_by_id_equal (const std::string &_id) : id (_id) {}

    bool
    operator() (const railway_vehicle &r_vehicle) const
    {
      return r_vehicle.get_id () == (id);
    }
  };

  class search_by_name
  {
  private:
    const std::string name;

  public:
    search_by_name (const std::string &_name) : name (_name) {}

    bool
    operator() (const railway_vehicle &r_vehicle) const
    {
      return std::string::npos != r_vehicle.get_name ().find (name);
    }
  };

  class search_by_id
  {
  private:
    const std::string id;

  public:
    search_by_id (const std::string &_id) : id (_id) {}

    bool
    operator() (const railway_vehicle &r_vehicle) const
    {
      return std::string::npos != r_vehicle.get_id ().find (id);
    }
  };

  template <typename Type> class search_by_type
  {
  public:
    bool
    operator() (const railway_vehicle &r_vehicle) const
    {
      return dynamic_cast<const Type *> (&r_vehicle);
    }
  };
};

}

#endif