#ifndef CPP2_S21_CONTAINERS_CONTAINERS_CONTAINER_ADAPTORS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_CONTAINER_ADAPTORS_S21_QUEUE_H_

#include <initializer_list>
#include "../s21_containers.h"

namespace s21{

template<class T, class Container = s21::list<T> >
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue() : container_() {}
  queue(std::initializer_list<value_type> const &items);
  queue(const queue& other);
  queue(queue&& other);
  ~queue() = default;
  reference operator=(queue&& other);

  const_reference front();
  const_reference back();

  bool empty() {
    return container_.empty();
  }

  size_type size() {
    return container_.size();
  }

  void push(const_reference value);
  void pop();
  void swap(queue& other);

 private:
  Container container_;
};

template<class T, class Container>
queue<T, Container>::queue(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}

template<class T, class Container>
queue<T, Container>::queue(const queue& other) {
  container_ = other.container_;
}

template<class T, class Container>
queue<T, Container>::queue(queue&& other) {
  container_ = std::move(other.container_);
}

template<class T, class Container>
T& queue<T, Container>::operator=(queue&& other) {
  container_ = other.container_;
  return *this;
}

template<class T, class Container> 
const T& queue<T, Container>::front() {
  return container_.front();
} 

template<class T, class Container> 
const T& queue<T, Container>::back() {
  return container_.back();
} 

template<class T, class Container> 
void queue<T, Container>::push(const_reference value) {
  container_.push_back(value);
} 

template<class T, class Container>
void queue<T, Container>::pop() {
  container_.pop_front();
}

template<class T, class Container>
void queue<T, Container>::swap(queue& other) {
  container_.swap(other.container_);
}

}   // namespace s21

#endif //CPP2_S21_CONTAINERS_CONTAINERS_CONTAINER_ADAPTORS_S21_QUEUE_H_