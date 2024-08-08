#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
class list {
 private:
  template <typename F>
  class Node {
   public:
    friend class list;
    Node(F data = F(), Node<F> *pNext = nullptr, Node<F> *pPrev = nullptr)
        : data(data), pNext(pNext), pPrev(pPrev){};

   private:
    F data;
    Node<F> *pNext;
    Node<F> *pPrev;
  };

  size_t size_;
  Node<T> *head_;
  Node<T> *tail_;
  Node<T> *circle_;

  void ChangeHeadTeal();
  void CreateCircle();
  void UnitCircle();
  void UnitNull();
  void MergeWithoutSort(list &other);
  void MoveHead();
  void MoveTail();
  void MergeNotEmpty(list &other);
  void ChangeNode(list &other);

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  template <typename T1>
  class ListIterator {
   public:
    friend class list<T1>;
    friend class Node<T1>;

    ListIterator(Node<T1> *node) : m_node(node) {}

    ListIterator &operator++() {
      m_node = m_node->pNext;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListIterator &operator--() {
      m_node = m_node->pPrev;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator temp = *this;
      --(*this);
      return temp;
    }

    T1 &operator*() const { return m_node->data; }

    bool operator==(const ListIterator &other) const {
      return m_node == other.m_node;
    }

    bool operator!=(const ListIterator &other) const {
      return m_node != other.m_node;
    }

   private:
    Node<T1> *m_node;
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const T &operator*() { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

  list() : size_(0U), head_(nullptr), tail_(nullptr) { CreateCircle(); };
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list() { clear(); };
  list<value_type> &operator=(const list<value_type> &l) noexcept;
  list<value_type> &operator=(list<value_type> &&l) noexcept;

  const_reference front() { return head_->data; };
  const_reference back() { return tail_->data; };

  iterator begin() { return iterator(head_ ? head_ : circle_); };
  iterator end() { return iterator(circle_); };

  bool empty() { return head_ == nullptr; };
  size_type size() { return size_; };
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void insert(iterator pos, Node<value_type> *node);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  void OutList();  //
};
}  // namespace s21

#endif  // LIST_H

template <typename value_type>
s21::list<value_type>::list(size_type n)
    : size_(0U), head_(nullptr), tail_(nullptr) {
  CreateCircle();
  if (n >= max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  while (n > 0) {
    push_back(value_type());
    n--;
  }
}

template <typename value_type>
s21::list<value_type>::list(std::initializer_list<value_type> const &items)
    : size_(0U), head_(nullptr), tail_(nullptr) {
  CreateCircle();
  if (items.size() >= max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  for (const auto &iitems : items) {
    push_back(iitems);
  }
}

template <typename value_type>
s21::list<value_type>::list(const list &l)
    : size_(0U), head_(nullptr), tail_(nullptr) {
  CreateCircle();
  Node<value_type> *temp = l.head_;
  if (l.size_) {
    while (temp != l.circle_) {
      push_back(temp->data);
      temp = temp->pNext;
    }
  }
}

template <typename value_type>
inline s21::list<value_type> &s21::list<value_type>::operator=(
    list<value_type> &&l) noexcept {
  if (this != &l) {
    list<value_type> temp(std::move(l));
    *this = temp;
  }
  return *this;
}

template <typename value_type>
inline s21::list<value_type> &s21::list<value_type>::operator=(
    const list<value_type> &l) noexcept {
  if (this != &l) {
    clear();
    Node<value_type> *temp = l.head_;
    if (temp) {
      while (temp != l.circle_) {
        push_back(temp->data);
        temp = temp->pNext;
      }
    }
  }
  return *this;
}

template <typename value_type>
s21::list<value_type>::list(list &&l) noexcept
    : size_(0U), head_(nullptr), tail_(nullptr) {
  CreateCircle();
  Node<value_type> *temp = l.head_;
  if (l.size_) {
    while (temp != nullptr) {
      push_back(temp->data);
      l.pop_front();
      temp = l.head_;
    }
  }
}

template <typename value_type>
size_t s21::list<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node<value_type>) / 2;
}

template <typename value_type>
void s21::list<value_type>::clear() {
  while (size_) pop_front();
  if (circle_) {
    delete circle_;
    circle_ = nullptr;
  }
}

template <typename value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::insert(
    iterator pos, const_reference value) {
  auto res = begin();
  if (pos == begin()) {
    push_front(value);
    res = begin();
  } else if (pos == end()) {
    push_back(value);
  } else {
    Node<value_type> *temp = this->head_;
    while (iterator(temp->pNext) != pos) temp = temp->pNext;
    temp->pNext = new Node<value_type>(value, temp->pNext, temp);
    temp->pNext->pNext->pPrev = temp->pNext;
    res = iterator(temp->pNext);
    ++size_;
  }
  return res;
}

template <typename value_type>
void s21::list<value_type>::insert(iterator pos, Node<value_type> *node) {
  if (pos == begin()) {
    node->pNext = head_;
    node->pPrev = circle_;
    head_ = node;
    circle_->pNext->pPrev = head_;
    UnitCircle();
  } else if (pos == iterator(circle_)) {
    node->pNext = circle_;
    node->pPrev = tail_;
    tail_ = node;
    circle_->pPrev->pNext = tail_;
    UnitCircle();
  } else {
    Node<value_type> *temp = this->head_;
    while (iterator(temp->pNext) != pos) temp = temp->pNext;
    node->pNext = temp->pNext;
    node->pPrev = temp;
    temp->pNext->pPrev = node;
    temp->pNext = node;
  }
  ++size_;
}

template <typename value_type>
void s21::list<value_type>::erase(iterator pos) {
  if (pos == begin())
    pop_front();
  else if (pos == iterator(tail_))
    pop_back();
  else if (pos == iterator(circle_))
    throw std::invalid_argument("pointer being freed was not allocated");
  else {
    Node<value_type> *temp = this->head_;
    while (iterator(temp->pNext) != pos) temp = temp->pNext;
    Node<value_type> *toDelete = temp->pNext;
    temp->pNext = toDelete->pNext;
    temp->pNext->pPrev = temp;
    delete toDelete;
    --size_;
  }
}

template <typename value_type>
void s21::list<value_type>::push_back(const_reference value) {
  if (head_ == nullptr) {
    head_ = new Node<value_type>(value, circle_, circle_);
    tail_ = head_;
  } else {
    Node<value_type> *temp = this->tail_;
    temp->pNext = new Node<value_type>(value, circle_, temp);
    tail_ = temp->pNext;
  }
  UnitCircle();
  ++size_;
}

template <typename value_type>
void s21::list<value_type>::pop_back() {
  if (size_ > 0) {
    Node<value_type> *temp = this->tail_->pPrev;
    delete temp->pNext;
    temp->pNext = circle_;
    tail_ = temp;
    circle_->pPrev = tail_;
    if (size_ == 1)
      UnitNull();
    else
      --size_;
  } else {
    throw std::invalid_argument("pointer being freed was not allocated");
  }
}

template <typename value_type>
void s21::list<value_type>::push_front(const_reference value) {
  if (head_ == nullptr)
    push_back(value);
  else {
    Node<value_type> *temp = this->head_;
    head_ = new Node<value_type>(value, head_, circle_);
    temp->pPrev = head_;
    circle_->pNext = head_;
    ++size_;
  }
}

template <typename value_type>
void s21::list<value_type>::pop_front() {
  if (size_ > 0) {
    Node<value_type> *temp = this->head_;
    head_ = head_->pNext;
    if (size_ != 1) (temp->pNext)->pPrev = circle_;
    circle_->pNext = head_;
    delete temp;
    if (size_ == 1)
      UnitNull();
    else
      --size_;
  } else {
    throw std::invalid_argument("pointer being freed was not allocated");
  }
}

template <typename value_type>
void s21::list<value_type>::swap(list &other) {
  if (head_ != other.head_ && head_ && other.head_) {
    size_t tempSize = size_;
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = circle_->pNext;
    other.tail_ = circle_->pPrev;
    other.size_ = tempSize;
    head_->pPrev = other.circle_;
    tail_->pNext = other.circle_;
    other.head_->pPrev = circle_;
    other.tail_->pNext = circle_;
    circle_ = other.circle_;
    other.circle_ = other.head_->pPrev;
  } else if (!head_ && !other.head_) {
    Node<value_type> *temp = circle_;
    circle_ = other.circle_;
    other.circle_ = temp;
  } else if (!head_) {
    Node<value_type> *temp = circle_;
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
    head_->pPrev = other.circle_;
    tail_->pNext = other.circle_;
    circle_ = other.circle_;
    other.circle_ = temp;
  } else if (!other.head_) {
    size_t tempSize = size_;
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
    other.head_ = circle_->pNext;
    other.tail_ = circle_->pPrev;
    other.size_ = tempSize;
    other.head_->pPrev = circle_;
    other.tail_->pNext = circle_;
    circle_ = other.circle_;
    other.circle_ = other.head_->pPrev;
  }
}

template <typename value_type>
void s21::list<value_type>::merge(list &other) {
  if (head_ != other.head_ && head_ && other.head_) {
    MergeNotEmpty(other);
  } else if (!head_ && other.head_)
    ChangeNode(other);
}

template <typename value_type>
void s21::list<value_type>::splice(const_iterator pos, list &other) {
  if (!empty() && !other.empty()) {
    if (pos == begin()) {
      head_ = other.head_;
      circle_->pNext->pPrev = other.tail_;
      other.head_->pPrev = circle_;
      other.tail_->pNext = circle_->pNext;
      circle_->pNext = head_;
    } else if (pos == iterator(tail_)) {
      MergeWithoutSort(other);
    } else {
      Node<value_type> *temp = this->head_;
      while (iterator(temp) != pos) {
        if (temp->pNext != circle_)
          temp = temp->pNext;
        else
          temp = head_;
      }
      Node<value_type> *tempNext = temp->pNext;
      temp->pNext = other.head_;
      tempNext->pPrev = other.tail_;
      other.head_->pPrev = temp;
      other.tail_->pNext = tempNext;
    }
    size_ += other.size_;
    other.UnitNull();
  } else if (empty() && !other.empty())
    ChangeNode(other);
}

template <typename value_type>
void s21::list<value_type>::reverse() {
  if (size_ > 1) {
    Node<value_type> *tempHead = this->head_;
    Node<value_type> *tempTail = this->tail_;
    Node<value_type> *tempNode = tempHead->pNext;
    auto tempPrev = tempHead->pNext->pPrev;
    auto tempNext = tempHead->pNext->pNext;
    for (size_t i = 1; i < size_ / 2; i++) {
      tempNode = tempHead->pNext;
      tempPrev = tempHead->pNext->pPrev;
      if (tempHead->pNext->pNext != tempTail->pPrev) {
        tempNext = tempHead->pNext->pNext;
        tempHead->pNext->pNext->pPrev = tempTail->pPrev;
        tempHead->pNext->pPrev = tempTail->pPrev->pPrev;
        tempHead->pNext->pNext = tempTail->pPrev->pNext;
        tempTail->pPrev->pPrev->pNext = tempNode;
      } else {
        tempNext = tempHead->pNext;
        tempHead->pNext->pPrev = tempTail->pPrev;
        tempHead->pNext->pNext = tempTail;
      }
      tempHead->pNext = tempTail->pPrev;
      tempTail->pPrev->pPrev = tempPrev;
      tempTail->pPrev->pNext = tempNext;
      tempTail->pPrev = tempNode;
      tempHead = tempHead->pNext;
      tempTail = tempTail->pPrev;
    }
    ChangeHeadTeal();
  }
}

template <typename value_type>
void s21::list<value_type>::unique() {
  if (!empty()) {
    Node<value_type> *temp = this->head_;
    while (temp->pNext != circle_) {
      while (temp->pNext != circle_ && temp->data == (temp->pNext)->data)
        erase(temp->pNext);
      if (temp->pNext != circle_) temp = temp->pNext;
    }
  }
}

template <typename value_type>
void s21::list<value_type>::sort() {
  if (size_ > 1) {
    Node<value_type> *temp = head_;
    auto tempPrev = head_->pPrev;
    auto tempNext = head_->pPrev;
    bool change = 0;
    if (size_ > 2) {
      for (size_t i = size_ - 1; i > 0; i--) {
        temp = head_;
        for (size_t j = i; j > 0; j--) {
          if (temp->data > temp->pNext->data) {
            tempPrev = temp->pNext;
            if (temp->pNext == tail_)
              MoveTail();
            else if (temp == head_)
              MoveHead();
            else {
              tempNext = temp->pNext->pNext;
              temp->pNext->pNext->pPrev = temp;
              temp->pNext->pPrev = temp->pPrev;
              temp->pPrev->pNext = temp->pNext;
              temp->pNext->pNext = temp;
              temp->pNext = tempNext;
            }
            temp->pPrev = tempPrev;
            change = 1;
          }
          temp = temp->pNext;
          if (change && temp) {
            temp = temp->pPrev;
            change = 0;
          }
        }
      }
    } else if (temp->data > temp->pNext->data)
      ChangeHeadTeal();
  }
}

template <typename value_type>
void s21::list<value_type>::ChangeHeadTeal() {
  if (size_ > 1) {
    Node<value_type> *temp = head_;
    auto tempNext = head_->pNext;
    if (size_ > 2) {
      head_->pNext->pPrev = tail_;
      tail_->pPrev->pNext = head_;
    } else
      tempNext = head_;
    head_->pPrev = head_->pNext;
    head_->pNext = circle_;
    tail_->pNext = tempNext;
    tail_->pPrev = circle_;
    head_ = tail_;
    tail_ = temp;
  }
  circle_->pPrev = tail_;
  circle_->pNext = head_;
}

template <typename value_type>
void s21::list<value_type>::CreateCircle() {
  circle_ = new Node<value_type>(value_type(), nullptr, nullptr);
}

template <typename value_type>
void s21::list<value_type>::UnitCircle() {
  if (circle_->pPrev != tail_) circle_->pPrev = tail_;
  if (circle_->pNext != head_) circle_->pNext = head_;
}

template <typename value_type>
void s21::list<value_type>::UnitNull() {
  head_ = nullptr;
  tail_ = nullptr;
  circle_->pNext = nullptr;
  circle_->pPrev = nullptr;
  size_ = 0;
}

template <typename value_type>
void s21::list<value_type>::MergeWithoutSort(list &other) {
  tail_ = other.tail_;
  circle_->pPrev->pNext = other.head_;
  other.head_->pPrev = circle_->pPrev;
  other.tail_->pNext = circle_;
  circle_->pPrev = tail_;
}

template <typename value_type>
void s21::list<value_type>::MergeNotEmpty(list &other) {
  Node<value_type> *temp = head_;
  Node<value_type> *tOther = other.head_;
  while (temp != circle_ && tOther != other.tail_) {
    tOther = other.head_;
    if (temp->data < tOther->data) {
      temp = temp->pNext;
    } else {
      other.head_ = other.head_->pNext;
      if (other.size_ != 1) other.head_->pPrev = other.circle_;
      other.circle_->pNext = other.head_;
      if (size_ == 1) other.UnitNull();
      other.size_--;
      if (temp->data == tOther->data) {
        insert(iterator(temp->pNext), tOther);
        temp = temp->pNext;
      } else
        insert(iterator(temp), tOther);
    }
  }
  if (!other.empty()) splice(iterator(tail_), other);
}

template <typename value_type>
void s21::list<value_type>::MoveHead() {
  auto temp = head_->pNext->pNext;
  head_ = head_->pNext;
  head_->pNext->pPrev = circle_->pNext;
  head_->pPrev = circle_;
  head_->pNext = circle_->pNext;
  head_->pNext->pNext = temp;
  UnitCircle();
}

template <typename value_type>
void s21::list<value_type>::MoveTail() {
  tail_ = tail_->pPrev;
  tail_->pPrev->pNext = circle_->pPrev;
  tail_->pNext = circle_;
  tail_->pPrev = circle_->pPrev;
  tail_->pPrev->pNext = tail_;
  UnitCircle();
}

template <typename value_type>
void s21::list<value_type>::ChangeNode(list &other) {
  swap(other);
  Node<value_type> *temp = circle_;
  head_->pPrev = other.circle_;
  tail_->pNext = other.circle_;
  circle_ = other.circle_;
  UnitCircle();
  other.circle_ = temp;
  other.UnitCircle();
}

template <typename value_type>
void s21::list<value_type>::OutList() {
  size_t index = 1;
  Node<value_type> *temp = this->head_;
  std::cout << "head_ - " << head_ << std::endl;
  if (size_ > 0) {
    while (index < size_) {
      std::cout << "(pPrev - " << temp->pPrev << ") node " << index
                << " data = " << temp << " " << temp->data << " (pNext - "
                << temp->pNext << ")" << std::endl;
      temp = temp->pNext;
      ++index;
    }
    std::cout << "(pPrev - " << temp->pPrev << ") node " << index
              << " data = " << temp << " " << temp->data << " (pNext - "
              << temp->pNext << ")" << std::endl;
  }
  std::cout << "tail_ - " << tail_ << std::endl;
  if (circle_)
    std::cout << "(pPrev - " << circle_->pPrev << ") circle_ - " << circle_
              << " (pNext - " << circle_->pNext << ")" << std::endl;
  else
    std::cout << "circle_ - " << circle_ << std::endl;
}