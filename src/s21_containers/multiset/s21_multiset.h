#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include "../tree/S21Tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <typename Key>
class multiset : public set<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using tree = typename set<Key>::tree;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;
  using size_type = size_t;

  /* Constructors */

  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms) noexcept;

  multiset &operator=(multiset &&ms);
  multiset &operator=(const multiset &ms);

  std::pair<iterator, bool> insert(const value_type &value);
  void merge(multiset &other);

  size_type count(const Key &key);

  std::pair<iterator, iterator> equal_range(const Key &key);

  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  /* Insert many */
  template <class... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};
}  // namespace s21

#include "s21_multiset.tpp"

#endif  // S21_MULTISET_H_