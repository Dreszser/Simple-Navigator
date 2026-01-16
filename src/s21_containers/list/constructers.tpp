namespace s21 {

template <typename T>
s21_List<T>::s21_List() : tail(nullptr), head(nullptr), size_(0) {}

template <typename T>
s21_List<T>::s21_List(int x) : tail(nullptr), head(nullptr), size_(0) {
  for (int i = 0; i < x; i++) push_back(T());
  if (x < 0) throw std::invalid_argument("");
}

template <typename T>
s21_List<T>::s21_List(std::initializer_list<T> const& items)
    : tail(nullptr), head(nullptr), size_(0) {
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename T>
s21_List<T>::s21_List(const s21_List<T>& other)
    : tail(nullptr), head(nullptr), size_(0) {
  ListIterator iter(other.head);
  while (size() != other.size()) {
    push_back(*iter);
    iter++;
  }
}

template <typename T>
s21_List<T>::s21_List(s21_List<T>&& other)
    : tail(other.tail), head(other.head), size_(other.size_) {
  other.size_ = 0;
  other.tail = nullptr;
  other.head = nullptr;
}

template <typename T>
s21_List<T>::~s21_List() {
  resize(0);
}
}  // namespace s21
