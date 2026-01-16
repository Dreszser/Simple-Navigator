#ifndef S21_SET_H_
#define S21_SET_H_

#include "../tree/S21Tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using tree = Tree<value_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;
  using size_type = size_t;

  tree *tree_;

  /* Constructors */

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s) noexcept;
  ~set();

  /* Operators overloads */

  set &operator=(set &&s);
  set &operator=(const set &s);

  /* Set Iterators */

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  /* Set Capacity */

  bool empty();
  size_type size();
  size_type max_size();

  /* Set Modifiers */

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  /* Set Lookup */

  iterator find(const Key &key);
  bool contains(const Key &key);

  /* Print for debugging */

  void print();

  /* insert many */
  template <class... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#include "s21_set.tpp"

#endif  // S21_SET_H_