#ifndef SET_H
#define SET_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
class set {
 private:
  template <typename F>
  class Node {
   public:
    friend class set;
    Node(F data = F(), Node<F> *parent_ = nullptr, Node<F> *right_ = nullptr,
         Node<F> *left_ = nullptr)
        : data(data), parent_(parent_), right_(right_), left_(left_){};

   private:
    F data;
    Node<F> *parent_;
    Node<F> *right_;
    Node<F> *left_;
  };

  size_t size_;
  Node<T> *root_;
  Node<T> *begin_;
  Node<T> *end_;

  void CreateEnd();
  Node<T> *NextNode(Node<T> *tNode);
  Node<T> *PrevNode(Node<T> *tNode);
  void EraseBegin();
  void EraseRBegin();
  void TransferBegin();
  void UnitNull();
  void CopySet(const set &s);
  void OutSet();

 public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  template <typename T1>
  class SetIterator {
   public:
    friend class set<T1>;
    friend class Node<T1>;

    SetIterator(Node<T1> *node) : m_node(node) {}

    SetIterator &operator++() {
      m_node = m_set->NextNode(m_node);
      return *this;
    }

    SetIterator operator++(int) {
      SetIterator temp = *this;
      ++(*this);
      return temp;
    }

    SetIterator &operator--() {
      m_node = m_set->PrevNode(m_node);
      return *this;
    }

    SetIterator operator--(int) {
      SetIterator temp = *this;
      --(*this);
      return temp;
    }

    T1 &operator*() const { return m_node->data; }

    bool operator==(const SetIterator &other) const {
      return m_node == other.m_node;
    }

    bool operator!=(const SetIterator &other) const {
      return m_node != other.m_node;
    }

   private:
    Node<T1> *m_node;
    set<T1> *m_set;
  };

  template <typename value_type>
  class SetConstIterator : public SetIterator<T> {
   public:
    SetConstIterator(SetIterator<T> other) : SetIterator<T>(other) {}
    const T &operator*() { return SetIterator<T>::operator*(); }
  };

  using iterator = SetIterator<value_type>;
  using const_iterator = SetConstIterator<value_type>;

  set() : size_(0U), root_(nullptr), begin_(nullptr) { CreateEnd(); };
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set() { clear(); };
  set<value_type> &operator=(const set<value_type> &s) noexcept;
  set<value_type> &operator=(set<value_type> &&s) noexcept;

  iterator begin() { return iterator(root_ ? begin_ : end_); };
  iterator end() { return iterator(end_); };

  bool empty() { return root_ == nullptr; };
  size_type size() { return size_; };
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const key_type &key);
  bool contains(const key_type &key);

 private:
  void EraseNormal(iterator pos);
};
}  // namespace s21

#endif  // SET_H

template <typename value_type>
s21::set<value_type>::set(std::initializer_list<value_type> const &items)
    : size_(0U), root_(nullptr), begin_(nullptr) {
  CreateEnd();
  if (items.size() >= max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  for (const auto &iitems : items) {
    insert(iitems);
  }
}

template <typename value_type>
s21::set<value_type>::set(const set &s)
    : size_(0U), root_(nullptr), begin_(nullptr) {
  *this = s;
}

template <typename value_type>
s21::set<value_type>::set(set &&s)
    : size_(0U), root_(nullptr), begin_(nullptr) {
  CreateEnd();
  if (s.root_) {
    set<value_type> temp(s);
    *this = temp;
    s.clear();
  }
}

template <typename value_type>
inline s21::set<value_type> &s21::set<value_type>::operator=(
    set<value_type> &&s) noexcept {
  if (this != &s) {
    set<value_type> temp(std::move(s));
    *this = temp;
  }
  return *this;
}

template <typename value_type>
inline s21::set<value_type> &s21::set<value_type>::operator=(
    const set<value_type> &s) noexcept {
  if (this != &s) {
    if (root_) clear();
    size_ = 0U, root_ = nullptr, begin_ = nullptr;
    CreateEnd();
    if (s.root_) {
      CopySet(s);
    }
  }
  return *this;
}

template <typename value_type>
size_t s21::set<value_type>::max_size() {
  return SIZE_MAX / sizeof(value_type) / 20;
}

template <typename value_type>
void s21::set<value_type>::clear() {
  Node<value_type> *temp = begin_;
  while (size_) {
    erase(iterator(temp));
    temp = begin_;
  }
  if (end_) {
    delete end_;
    end_ = nullptr;
  }
}

template <typename value_type>
std::pair<typename s21::set<value_type>::iterator, bool>
s21::set<value_type>::insert(const value_type &value) {
  std::pair<typename s21::set<value_type>::iterator, bool> res(end_, 1);
  if (empty()) {
    root_ = new Node<value_type>(value, nullptr, end_, nullptr);
    begin_ = root_;
    begin_->left_ = end_;
    res.first = iterator(root_);
    res.second = 1;
    end_->parent_ = root_;
    end_->right_ = end_->parent_;
  } else {
    Node<value_type> *temp = root_;
    while (res.second && ((temp->data < value && temp->right_ &&
                           temp->data < value && temp->right_ != end_) ||
                          (temp->data > value && temp->left_ &&
                           temp->data > value && temp->left_ != end_))) {
      if (value == temp->data) {
        res.first = temp;
        res.second = 0;
      } else if (value < temp->data)
        temp = temp->left_;
      else
        temp = temp->right_;
    }
    if (value == temp->data) {
      res.first = temp;
      res.second = 0;
    } else if (value < temp->data) {
      temp->left_ = new Node<value_type>(value, temp, nullptr, nullptr);
      if (temp == begin_) {
        begin_ = temp->left_;
        begin_->left_ = end_;
      }
      res.first = temp->left_;
    } else {
      if (temp->right_ == end_) {
        temp->right_ = new Node<value_type>(value, temp, nullptr, nullptr);
        temp->right_->right_ = end_;
        end_->parent_ = temp->right_;
        end_->right_ = end_->parent_;
      } else
        temp->right_ = new Node<value_type>(value, temp, nullptr, nullptr);
      res.first = temp->right_;
    }
  }
  if (res.second) size_++;
  return res;
}

template <typename value_type>
void s21::set<value_type>::erase(iterator pos) {
  if (pos == begin())
    EraseBegin();
  else if (pos == iterator(end_->parent_))
    EraseRBegin();
  else if (pos == iterator(end_))
    throw std::invalid_argument("pointer being freed was not allocated");
  else {
    EraseNormal(pos);
  }
}

template <typename value_type>
void s21::set<value_type>::swap(set &other) {
  if (root_ != other.root_ && root_ && other.root_) {
    size_t tempSize = size_;
    Node<value_type> *tempRoot = root_;
    Node<value_type> *tempBegin = begin_;
    Node<value_type> *tempEnd = end_;
    root_ = other.root_;
    begin_ = other.begin_;
    end_ = other.end_;
    size_ = other.size_;
    other.root_ = tempRoot;
    other.begin_ = tempBegin;
    other.end_ = tempEnd;
    other.size_ = tempSize;
  } else if (!root_ && !other.root_) {
    Node<value_type> *temp = end_;
    end_ = other.end_;
    other.end_ = temp;
  } else if (!root_) {
    Node<value_type> *temp = end_;
    root_ = other.root_;
    begin_ = other.begin_;
    size_ = other.size_;
    other.UnitNull();
    end_ = other.end_;
    other.end_ = temp;
  } else if (!other.root_) {
    Node<value_type> *temp = other.end_;
    other.size_ = size_;
    other.root_ = root_;
    other.begin_ = begin_;
    other.end_ = end_;
    UnitNull();
    end_ = temp;
  }
}

template <typename value_type>
void s21::set<value_type>::merge(set &other) {
  if (root_ != other.root_ && root_ && other.root_) {
    Node<value_type> *tempOther = other.begin_;
    while (tempOther) {
      if (!contains(tempOther->data)) {
        other.TransferBegin();
        Node<value_type> *tempThis = root_;
        while ((tempThis->data < tempOther->data && tempThis->right_ &&
                tempThis->data < tempOther->data && tempThis->right_ != end_) ||
               (tempThis->data > tempOther->data && tempThis->left_ &&
                tempThis->data > tempOther->data && tempThis->left_ != end_)) {
          if (tempOther->data < tempThis->data)
            tempThis = tempThis->left_;
          else
            tempThis = tempThis->right_;
        }
        if (tempOther->data < tempThis->data) {
          tempThis->left_ = tempOther;
          tempOther->parent_ = tempThis;
          tempOther->right_ = nullptr;
          tempOther->left_ = nullptr;
          if (tempThis == begin_) {
            begin_ = tempThis->left_;
            begin_->left_ = end_;
          }
        } else {
          if (tempThis->right_ == end_) {
            tempThis->right_ = tempOther;
            tempOther->parent_ = tempThis;
            tempOther->left_ = nullptr;
            tempThis->right_->right_ = end_;
            end_->parent_ = tempThis->right_;
            end_->right_ = end_->parent_;
          } else {
            tempThis->right_ = tempOther;
            tempOther->parent_ = tempThis;
            tempOther->left_ = nullptr;
            tempOther->right_ = nullptr;
          }
        }
        size_++;
      } else
        other.erase(other.begin_);
      tempOther = other.begin_;
    }
  } else if (!root_ && other.root_)
    swap(other);
}

template <typename value_type>
typename s21::set<value_type>::iterator s21::set<value_type>::find(
    const key_type &key) {
  s21::set<value_type>::iterator res = end_;
  if (size_) {
    Node<value_type> *temp = begin_;
    while (temp != end_ && temp->data != key) temp = NextNode(temp);
    res = iterator(temp);
  }
  return res;
}

template <typename value_type>
bool s21::set<value_type>::contains(const key_type &key) {
  bool res = 0;
  if (size_) {
    Node<value_type> *temp = begin_;
    while (temp != end_ && !res) {
      if (temp->data == key) res = 1;
      temp = NextNode(temp);
    }
  }
  return res;
}

template <typename value_type>
void s21::set<value_type>::CreateEnd() {
  end_ = new Node<value_type>(value_type(), nullptr, nullptr, nullptr);
}

template <typename value_type>
typename s21::set<value_type>::template Node<value_type>
    *s21::set<value_type>::NextNode(Node<value_type> *tNode) {
  Node<value_type> *temp = tNode;
  if (temp->right_ != temp->parent_) {  // != end_
    if (temp->right_) {
      temp = temp->right_;
      while (temp->left_) {
        temp = temp->left_;
      }
    } else {
      if (temp == temp->parent_->right_)
        while (temp != temp->parent_->left_) temp = temp->parent_;
      temp = temp->parent_;
    }
  } else
    temp = temp->parent_;
  return temp;
}

template <typename value_type>
typename s21::set<value_type>::template Node<value_type>
    *s21::set<value_type>::PrevNode(Node<value_type> *tNode) {
  Node<value_type> *temp = tNode;
  if (temp->left_) {
    temp = temp->left_;
    while (temp->right_ && temp->right_ != temp->parent_) temp = temp->right_;
  } else {
    if (temp == temp->parent_->left_)
      while (temp != temp->parent_->right_) temp = temp->parent_;
    temp = temp->parent_;
  }
  return temp;
}

template <typename value_type>
void s21::set<value_type>::UnitNull() {
  root_ = nullptr;
  begin_ = nullptr;
  end_->parent_ = nullptr;
  end_->right_ = nullptr;
  size_ = 0;
}

template <typename value_type>
void s21::set<value_type>::EraseBegin() {
  if (begin_ == root_) {
    delete root_;
    if (size_ > 1) {
      root_ = root_->right_;
      root_->parent_ = nullptr;
      Node<value_type> *temp = root_;
      while (temp->left_) temp = temp->left_;
      begin_ = temp;
      temp->left_ = end_;
    } else {
      root_ = nullptr;
      begin_ = nullptr;
      end_->parent_ = nullptr;
      end_->right_ = nullptr;
    }
  } else if (begin_->right_) {
    begin_->parent_->left_ = begin_->right_;
    begin_->right_->parent_ = begin_->parent_;
    Node<value_type> *temp = begin_->right_;
    while (temp->left_) temp = temp->left_;
    Node<value_type> *tempDel = begin_;
    begin_ = temp;
    begin_->left_ = end_;
    delete tempDel;
  } else {
    Node<value_type> *temp = begin_;
    begin_ = begin_->parent_;
    begin_->left_ = end_;
    delete temp;
  }
  --size_;
}

template <typename value_type>
void s21::set<value_type>::EraseRBegin() {
  if (end_->parent_ == root_) {
    root_ = root_->left_;
    delete end_->parent_;
    root_->parent_ = nullptr;
    Node<value_type> *temp = root_;
    while (temp->right_) temp = temp->right_;
    temp->right_ = end_;
    end_->parent_ = temp;
    end_->right_ = temp;
  } else if (end_->parent_->left_) {
    Node<value_type> *temp = end_->parent_->left_;
    end_->parent_->parent_->right_ = temp;
    while (temp->right_) temp = temp->right_;
    delete end_->parent_;
    temp->right_ = end_;
    end_->parent_ = temp;
    end_->right_ = temp;
  } else {
    Node<value_type> *temp = end_->parent_;
    end_->parent_->parent_->right_ = end_;
    end_->parent_ = end_->parent_->parent_;
    end_->right_ = end_->parent_;
    delete temp;
  }
  --size_;
}

template <typename value_type>
void s21::set<value_type>::EraseNormal(iterator pos) {
  Node<value_type> *tempDel = begin_;
  while (iterator(tempDel) != pos) tempDel = NextNode(tempDel);
  if (tempDel->left_ && tempDel->right_) {
    Node<value_type> *tempChange = tempDel->right_;
    while (tempChange->left_) tempChange = tempChange->left_;
    if (tempChange->parent_ != tempDel) {
      tempChange->parent_->left_ = tempChange->right_;
      if (tempChange->right_) tempChange->right_->parent_ = tempChange->parent_;
    }
    if (tempDel->parent_) {
      tempDel == tempDel->parent_->right_
          ? tempDel->parent_->right_ = tempChange
          : tempDel->parent_->left_ = tempChange;
    } else {
      root_ = tempChange;
      root_->parent_ = nullptr;
      root_->left_ = tempDel->left_;
      root_->right_ = tempDel->right_;
    }
    if (tempDel->left_) tempDel->left_->parent_ = tempChange;
    if (tempDel->right_) tempDel->right_->parent_ = tempChange;
    tempChange->parent_ = tempDel->parent_;
  } else if (tempDel->right_) {
    tempDel->right_->parent_ = tempDel->parent_;
    tempDel == tempDel->parent_->left_
        ? tempDel->parent_->left_ = tempDel->right_
        : tempDel->parent_->right_ = tempDel->right_;
  } else if (tempDel->left_) {
    tempDel->left_->parent_ = tempDel->parent_;
    tempDel == tempDel->parent_->left_
        ? tempDel->parent_->left_ = tempDel->left_
        : tempDel->parent_->right_ = tempDel->left_;
  } else {
    tempDel == tempDel->parent_->right_ ? tempDel->parent_->right_ = nullptr
                                        : tempDel->parent_->left_ = nullptr;
  }
  delete tempDel;
  --size_;
}

template <typename value_type>
void s21::set<value_type>::TransferBegin() {
  if (!begin_->parent_ && begin_->right_ == end_) {
    UnitNull();
  } else if (!begin_->parent_ && begin_->right_ != end_) {
    root_ = begin_->right_;
    root_->parent_ = nullptr;
    Node<value_type> *temp = begin_->right_;
    while (temp->left_) temp = temp->left_;
    begin_ = temp;
    begin_->left_ = end_;
    --size_;
  } else if (!begin_->right_) {
    begin_ = begin_->parent_;
    begin_->left_ = end_;
    --size_;
  } else {
    begin_->parent_->left_ = begin_->right_;
    begin_->right_->parent_ = begin_->parent_;
    Node<value_type> *temp = begin_->right_;
    while (temp->left_) temp = temp->left_;
    begin_ = temp;
    begin_->left_ = end_;
    --size_;
  }
}

template <typename value_type>
void s21::set<value_type>::CopySet(const set &s) {
  Node<value_type> *temp = s.root_;
  insert(temp->data);
  while (size_ < s.size_) {
    while (temp->left_ && temp->left_ != s.end_) {
      temp = temp->left_;
      insert(temp->data);
    }
    if (temp->right_ && temp->right_ != s.end_) {
      temp = temp->right_;
      insert(temp->data);
    } else {
      if (temp == temp->parent_->left_ && temp->parent_->right_ &&
          temp->parent_->right_ != s.end_) {
        temp = temp->parent_->right_;
        insert(temp->data);
      } else if (temp == temp->parent_->right_) {
        while (temp == temp->parent_->right_) temp = temp->parent_;
        temp = temp->parent_;
        while (!temp->right_ && temp->right_ != s.end_) temp = temp->parent_;
        temp = temp->right_;
        insert(temp->data);
      } else {
        while (!temp->right_) temp = temp->parent_;
        temp = temp->right_;
        if (temp != s.end_) insert(temp->data);
      }
    }
  }
}

template <typename value_type>
void s21::set<value_type>::OutSet() {
  std::cout << "size_ - " << size_ << std::endl;
  std::cout << "root_ - " << root_ << std::endl;
  std::cout << "begin_ - " << begin_ << std::endl;
  if (size_ > 0) {
    Node<value_type> *temp = begin_;
    size_t index = 1;
    while (index <= size_) {
      std::cout << "(p - " << temp->parent_ << ") node " << index << " - "
                << temp->data << " (" << temp << ") (r - " << temp->right_
                << ", l - " << temp->left_ << ")" << std::endl;
      index++;
      temp = NextNode(temp);
    }
  }
  std::cout << "(p - " << end_->parent_ << ") end_ (" << end_ << ") (r - "
            << end_->right_ << ", l - " << end_->left_ << ")" << std::endl;
  std::cout << std::endl;
}