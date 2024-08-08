#include <gtest/gtest.h>
#include <stack>
#include "../containers/s21_stack.h"

TEST (s21_stack_constuct, initializer_list) {
  s21::stack<int> s21_stack({1, 2, 3, 4, 5});
  ASSERT_EQ(s21_stack.top(), 5);
  s21_stack.pop();
  s21_stack.pop();
  s21_stack.pop();
  ASSERT_EQ(s21_stack.top(), 2);
}

TEST (s21_stack_constuct, initializer_list_str) {
  s21::stack<std::string> s21_stack({"1", "2", "3", "4", "5"});
  ASSERT_EQ(s21_stack.top(), "5");
  s21_stack.pop();
  s21_stack.pop();
  s21_stack.pop();
  ASSERT_EQ(s21_stack.top(), "2");
}

TEST (s21_stack_constuct, initializer_list_cstr) {
  s21::stack<const char*> s21_stack({"1", "2", "3", "4", "5"});
  ASSERT_EQ(s21_stack.top(), "5");
  s21_stack.pop();
  s21_stack.pop();
  s21_stack.pop();
  ASSERT_EQ(s21_stack.top(), "2");
}

TEST (s21_stack, top_00) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  int expect = 15;
  std_stack.push(expect);
  s21_stack.push(expect);
  ASSERT_EQ(s21_stack.top(), std_stack.top());
}

TEST(s21_stack, empty) {
  s21::stack<int> s21_stack;
  ASSERT_TRUE(s21_stack.empty());
  s21_stack.push(15);
  ASSERT_FALSE(s21_stack.empty());
}

TEST(s21_stack, size) {
  s21::stack<int> s21_stack;
  ASSERT_EQ(s21_stack.size(), (size_t)0);
  s21_stack.push(15);
  ASSERT_EQ(s21_stack.size(), (size_t)1);
  s21_stack.push(20);
  ASSERT_EQ(s21_stack.size(), (size_t)2);
}

TEST(s21_stack, pop_int) {
  s21::stack<int> s21_stack;
  s21_stack.push(15);
  s21_stack.push(20);
  s21_stack.pop();
  ASSERT_EQ(s21_stack.top(), 15);
}

TEST(s21_stack, pop_str) {
  s21::stack<std::string> s21_stack;
  s21_stack.push("15");
  s21_stack.push("20");
  s21_stack.pop();
  ASSERT_EQ(s21_stack.top(), "15");
}

TEST(s21_stack, swap_00) {
  s21::stack<int> s21_stack1;
  s21_stack1.push(15);
  s21_stack1.push(20);

  s21::stack<int> s21_stack2;
  s21_stack2.push(30);
  s21_stack2.push(40);

  s21_stack1.swap(s21_stack2);

  ASSERT_EQ(s21_stack1.top(), 40);
  ASSERT_EQ(s21_stack2.top(), 20);

  s21_stack1.pop();
  ASSERT_EQ(s21_stack1.top(), 30);

  s21_stack2.pop();
  ASSERT_EQ(s21_stack2.top(), 15);
}
