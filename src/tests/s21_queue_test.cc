#include <gtest/gtest.h>
#include <queue>
#include "../containers/s21_queue.h"

TEST (s21_queue_constuct, initializer_list) {
  s21::queue<int> s21_queue({1, 2, 3, 4, 5});
  ASSERT_EQ(s21_queue.back(), 5);
  s21_queue.pop();
  s21_queue.pop();
  s21_queue.pop();
  ASSERT_EQ(s21_queue.front(), 4);
  ASSERT_EQ(s21_queue.back(), 5);
}

TEST (s21_queue_constuct, initializer_list_str) {
  s21::queue<std::string> s21_queue({"1", "2", "3", "4", "5"});
  ASSERT_EQ(s21_queue.back(), "5");
  s21_queue.pop();
  s21_queue.pop();
  s21_queue.pop();
  ASSERT_EQ(s21_queue.front(), "4");
  ASSERT_EQ(s21_queue.back(), "5");
}

TEST (s21_queue_constuct, initializer_list_cstr) {
  s21::queue<const char*> s21_queue({"1", "2", "3", "4", "5"});
  ASSERT_EQ(s21_queue.back(), "5");
  s21_queue.pop();
  s21_queue.pop();
  s21_queue.pop();
  ASSERT_EQ(s21_queue.front(), "4");
  ASSERT_EQ(s21_queue.back(), "5");
}

TEST (s21_queue, back_00) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  int expect = 15;
  std_queue.push(expect);
  s21_queue.push(expect);
  ASSERT_EQ(s21_queue.back(), std_queue.back());
}

TEST(s21_queue, empty) {
  s21::queue<int> s21_queue;
  ASSERT_TRUE(s21_queue.empty());
  s21_queue.push(15);
  ASSERT_FALSE(s21_queue.empty());
}

TEST(s21_queue, size) {
  s21::queue<int> s21_queue;
  ASSERT_EQ(s21_queue.size(), (size_t)0);
  s21_queue.push(15);
  ASSERT_EQ(s21_queue.size(), (size_t)1);
  s21_queue.push(20);
  ASSERT_EQ(s21_queue.size(), (size_t)2);
}

TEST(s21_queue, pop_int) {
  s21::queue<int> s21_queue;
  s21_queue.push(15);
  s21_queue.push(20);
  s21_queue.pop();
  ASSERT_EQ(s21_queue.front(), 20);
}

TEST(s21_queue, pop_str) {
  s21::queue<std::string> s21_queue;
  s21_queue.push("15");
  s21_queue.push("20");
  s21_queue.pop();
  ASSERT_EQ(s21_queue.back(), "20");
}

TEST(s21_queue, swap_00) {
  s21::queue<int> s21_queue1;
  s21_queue1.push(15);
  s21_queue1.push(20);

  s21::queue<int> s21_queue2;
  s21_queue2.push(30);
  s21_queue2.push(40);

  s21_queue1.swap(s21_queue2);

  ASSERT_EQ(s21_queue1.back(), 40);
  ASSERT_EQ(s21_queue2.back(), 20);

  s21_queue1.pop();
  ASSERT_EQ(s21_queue1.back(), 40);

  s21_queue2.pop();
  ASSERT_EQ(s21_queue2.back(), 20);
}
