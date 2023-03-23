#ifndef VECTOR_H
#define VECTOR_H

namespace ctr
{

template <typename Type> class vector
{

private:
  static const unsigned int GROWTH_FACTOR = 2; // O(1) amortized

  unsigned int v_size;
  unsigned int v_capacity;
  Type *v_data;

  // Internal methods
  static void clone_data (Type *src, Type *dest, unsigned int size);
  void check_growth ();

public:
  vector ();
  vector (const vector &vt);
  ~vector ();

  /*
   *      ITERATORS:
   *          An iterator reach Past The End (PTE) if and only if
   *          offset >= max_offset. max_offset is equal to size of the vector
   *          at the moment of iterator construction. If vector change size or
   *          base any iterator already delcare became invalid.
   */

  /// ITERATOR
  class iterator
  {
    friend class vector<Type>;

  protected:
    Type *base;
    unsigned int offset;
    unsigned int max_offset; // == size of vector (NOT capacity)

    iterator (Type *base, unsigned int offset, unsigned int max_offset);

  public:
    bool operator== (const iterator &it) const;
    bool operator!= (const iterator &it) const;
    bool operator>= (const iterator &it) const;
    bool operator<= (const iterator &it) const;
    iterator &operator++ ();
    iterator operator++ (int);
    iterator &operator-- ();
    iterator operator-- (int);
    iterator operator+ (unsigned int value);
    iterator operator- (unsigned int value);

    Type &operator* () const;
    Type *operator->() const;
  };

  /// CONST_ITERATOR
  class const_iterator : private iterator
  {
    friend class vector<Type>;

  private:
    const_iterator (Type *base, unsigned int offset, unsigned int max_offset);

  public:
    // Allow conversion from iterator to const_iterator
    const_iterator (const vector<Type>::iterator &it);

    // const_iterator& operator=(const const_iterator& it);
    bool operator!= (const const_iterator &it) const;
    bool operator== (const const_iterator &it) const;
    bool operator>= (const const_iterator &it) const;
    bool operator<= (const const_iterator &it) const;
    const_iterator &operator++ ();
    const_iterator operator++ (int);
    const_iterator &operator-- ();
    const_iterator operator-- (int);
    const_iterator operator+ (unsigned int value);
    const_iterator operator- (unsigned int value);

    const Type &operator* () const;
    const Type *operator->() const;
  };

  /// Vector Iterator Methods
  iterator begin ();
  const_iterator begin () const;

  iterator end ();
  const_iterator end () const;

  // Public Methods
  unsigned int size () const;
  iterator insert (const const_iterator &pos, const Type &obj);
  iterator erase (const const_iterator &pos);
  void clear ();
  void push_back (const Type &obj);
  bool is_empty () const;

  vector<Type> &operator= (const vector<Type> &v);
};

/*
 *
 *  VECTOR
 *
 */
template <typename Type>
vector<Type>::vector () : v_size (0), v_capacity (0), v_data (nullptr)
{
}

template <typename Type>
vector<Type>::vector (const vector<Type> &vt)
    : v_size (vt.v_size), v_capacity (vt.v_capacity), v_data (new Type[v_size])
{
  clone_data (vt.v_data, v_data, v_size);
}

template <typename Type> vector<Type>::~vector ()
{
  if (v_data)
    delete[] v_data;
}

/// Public Methods
template <typename Type>
unsigned int
vector<Type>::size () const
{
  return v_size;
}

template <typename Type>
void
vector<Type>::push_back (const Type &obj)
{
  v_size++;
  check_growth ();
  *(v_data + v_size - 1) = obj;
}

template <typename Type>
bool
vector<Type>::is_empty () const
{
  return v_capacity == v_size && v_size == 0;
}

template <typename Type>
typename vector<Type>::iterator
vector<Type>::insert (const const_iterator &pos, const Type &obj)
{
  unsigned int offset = pos.offset;

  v_size++; // This break every iterator declare before this
            // instruction (like C++ STL vector)
  check_growth ();

  // end() - 1 = last element
  // Make a right shift
  for (auto it = end () - 1; it != (begin () + offset); it--)
    *it = *(it - 1);

  *(begin () + offset) = obj;

  return begin () + offset;
}

template <typename Type>
typename vector<Type>::iterator
vector<Type>::erase (const const_iterator &pos)
{
  unsigned int offset = pos.offset;

  // end() - 2 = second to last vector element
  for (auto it = begin () + offset; it <= end () - 2; it++)
    *it = *(it + 1);

  v_size--; // This break every iterator declare before this instruction

  return begin () + offset;
}

template <typename Type>
void
vector<Type>::clear ()
{
  // Delete everything for safety reason
  delete[] v_data;
  v_data = new Type[v_capacity];

  v_size = 0;
}

template <typename Type>
typename vector<Type>::iterator
vector<Type>::begin ()
{
  return vector<Type>::iterator (v_data, 0, v_size);
}

template <typename Type>
typename vector<Type>::const_iterator
vector<Type>::begin () const
{
  return vector<Type>::const_iterator (v_data, 0, v_size);
}

template <typename Type>
typename vector<Type>::iterator
vector<Type>::end ()
{
  return vector<Type>::iterator (v_data, v_size, v_size); // PTE
}

template <typename Type>
typename vector<Type>::const_iterator
vector<Type>::end () const
{
  return vector<Type>::const_iterator (v_data, v_size, v_size); // PTE
}

/// Private Methods
template <typename Type>
void
vector<Type>::clone_data (Type *src, Type *dest, unsigned int size)
{
  for (unsigned int index = 0; index < size; index++)
    *(dest + index) = *(src + index);
}

template <typename Type>
void
vector<Type>::check_growth ()
{
  Type *original_data = v_data;
  unsigned int original_capacity = v_capacity;

  if (v_size <= v_capacity)
    return;

  v_capacity = v_capacity ? v_capacity * GROWTH_FACTOR : GROWTH_FACTOR;
  v_data = new Type[v_capacity];

  clone_data (original_data, v_data, original_capacity);
  delete[] original_data;
}

/// Operators
template <typename Type>
vector<Type> &
vector<Type>::operator= (const vector<Type> &v)
{
  if (&v != this)
    {
      if (v_data)
        delete[] v_data;

      v_size = v.v_size;
      v_capacity = v.v_capacity;

      v_data = new Type[v_capacity];

      clone_data (v.v_data, v_data, v_size);
    }

  return *this;
}

/*
 *  VECTOR::ITERATOR
 */
template <typename Type>
vector<Type>::iterator::iterator (Type *_base, unsigned int _offset,
                                  unsigned int _max_offset)
    : base (_base), offset (_offset), max_offset (_max_offset)
{
}

template <typename Type>
bool
vector<Type>::iterator::operator== (const iterator &it) const
{
  return it.base == base && it.offset == offset;
}

template <typename Type>
bool
vector<Type>::iterator::operator!= (const iterator &it) const
{
  return it.base != base || it.offset != offset;
}

template <typename Type>
bool
vector<Type>::iterator::operator>= (const iterator &it) const
{
  return it.base == base && it.offset <= offset;
}

template <typename Type>
bool
vector<Type>::iterator::operator<= (const iterator &it) const
{
  return it.base == base && it.offset >= offset;
}

template <typename Type>
typename vector<Type>::iterator &
vector<Type>::iterator::operator++ ()
{
  if (offset < max_offset) // PTE == false
    offset++;

  return *this;
}

template <typename Type>
typename vector<Type>::iterator
vector<Type>::iterator::operator++ (int)
{
  iterator aux = *this;
  this->operator++ ();
  return aux;
}

template <typename Type>
typename vector<Type>::iterator &
vector<Type>::iterator::operator-- ()
{
  if (offset > 0)
    offset--;
  return *this;
}

template <typename Type>
typename vector<Type>::iterator
vector<Type>::iterator::operator-- (int)
{
  iterator aux = *this;
  this->operator-- ();
  return aux;
}

template <typename Type>
typename vector<Type>::iterator
vector<Type>::iterator::operator+ (unsigned int value)
{
  iterator aux = *this;

  if (aux.offset + value >= aux.max_offset)
    aux.offset = aux.max_offset;
  else
    aux.offset += value;

  return aux;
}

template <typename Type>
typename vector<Type>::iterator
vector<Type>::iterator::operator- (unsigned int value)
{
  iterator aux = *this;

  if (aux.offset <= value)
    aux.offset = 0;
  else
    aux.offset -= value;

  return aux;
}

template <typename Type>
Type &
vector<Type>::iterator::operator* () const
{
  if (offset == max_offset)
    return *(base - sizeof (Type) - 1); // PTE --> out of bound
  else
    return *(base + offset);
}

template <typename Type>
Type *
vector<Type>::iterator::operator->() const
{
  if (offset == max_offset)
    return base - sizeof (Type) - 1; // PTE --> out of bound

  return base + offset;
}

/*
 *  VECTOR::CONST_ITERATOR
 */
template <typename Type>
vector<Type>::const_iterator::const_iterator (Type *base, unsigned int offset,
                                              unsigned int max_offset)
    : iterator (base, offset, max_offset)
{
}

template <typename Type>
vector<Type>::const_iterator::const_iterator (
    const typename vector<Type>::iterator &it)
    : iterator (it)
{
}

template <typename Type>
bool
vector<Type>::const_iterator::operator!= (
    const vector<Type>::const_iterator &it) const
{
  return iterator::operator!= (it);
}

template <typename Type>
bool
vector<Type>::const_iterator::operator== (
    const vector<Type>::const_iterator &it) const
{
  return iterator::operator== (it);
}

template <typename Type>
bool
vector<Type>::const_iterator::operator>= (
    const vector<Type>::const_iterator &it) const
{
  return iterator::operator>= (it);
}

template <typename Type>
bool
vector<Type>::const_iterator::operator<= (
    const vector<Type>::const_iterator &it) const
{
  return iterator::operator<= (it);
}

template <typename Type>
typename vector<Type>::const_iterator &
vector<Type>::const_iterator::operator++ ()
{
  return static_cast<vector<Type>::const_iterator &> (iterator::operator++ ());
}

template <typename Type>
typename vector<Type>::const_iterator
vector<Type>::const_iterator::operator++ (int)
{
  return static_cast<vector<Type>::const_iterator> (iterator::operator++ (+1));
}

template <typename Type>
typename vector<Type>::const_iterator &
vector<Type>::const_iterator::operator-- ()
{
  return static_cast<vector<Type>::const_iterator &> (iterator::operator-- ());
}

template <typename Type>
typename vector<Type>::const_iterator
vector<Type>::const_iterator::operator-- (int)
{
  return static_cast<vector<Type>::const_iterator> (iterator::operator-- (-1));
}

template <typename Type>
typename vector<Type>::const_iterator
vector<Type>::const_iterator::operator+ (unsigned int value)
{
  return static_cast<vector<Type>::const_iterator> (
      iterator::operator+ (value));
}

template <typename Type>
typename vector<Type>::const_iterator
vector<Type>::const_iterator::operator- (unsigned int value)
{
  return static_cast<vector<Type>::const_iterator> (
      iterator::operator- (value));
}

template <typename Type>
const Type &
vector<Type>::const_iterator::operator* () const
{
  return iterator::operator* ();
}

template <typename Type>
const Type *
vector<Type>::const_iterator::operator->() const
{
  return iterator::operator->();
}
}

#endif