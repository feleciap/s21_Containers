#ifndef CPP2_S21_CONTAINERS_CONTAINERS_CONTAINER_ADAPTORS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_CONTAINERS_CONTAINER_ADAPTORS_S21_STACK_H_

#include <initializer_list>
#include "../s21_containers.h"

namespace s21{

template<class T, class Container = s21::list<T> >
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  stack() : container_() {}
  stack(std::initializer_list<value_type> const &items);
  stack(const stack& other);
  stack(stack&& other);
  ~stack() = default;
  reference operator=(stack&& other);

  const_reference top();

  bool empty() {
    return container_.empty();
  }

  size_type size() {
    return container_.size();
  }

  void push(const_reference value);
  void pop();
  void swap(stack& other);

 private:
  Container container_;
};

template<class T, class Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}

template<class T, class Container>
stack<T, Container>::stack(const stack& other) {
  container_ = other.container_;
}

template<class T, class Container>
stack<T, Container>::stack(stack&& other) {
  container_ = std::move(other.container_);
}

template<class T, class Container>
T& stack<T, Container>::operator=(stack&& other) {
  container_ = other.container_;
  return *this;
}

template<class T, class Container> 
const T& stack<T, Container>::top() {
  return container_.back();
} 

template<class T, class Container> 
void stack<T, Container>::push(const_reference value) {
  container_.push_back(value);
} 

template<class T, class Container>
void stack<T, Container>::pop() {
  container_.pop_back();
}

template<class T, class Container>
void stack<T, Container>::swap(stack& other) {
  container_.swap(other.container_);
}

}   // namespace s21

#endif //CPP2_S21_CONTAINERS_CONTAINERS_CONTAINER_ADAPTORS_S21_STACK_H_