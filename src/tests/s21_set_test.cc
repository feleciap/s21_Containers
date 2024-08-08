#include <gtest/gtest.h>

#include <set>

#include "../containers/s21_set.h"

// SET

template <typename value_type>
bool compare_sets(s21::set<value_type>& my_set, std::set<value_type> std_set) {
  bool result = true;
  if (my_set.size() == std_set.size()) {
    auto my_it = my_set.begin();
    auto std_it = std_set.begin();
    for (size_t i = 0; i != my_set.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      my_it++;
      std_it++;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(SetTest, DefaultConstructor) {
  s21::set<int> my_set;
  std::set<int> std_set;
  EXPECT_EQ(my_set.size(), (size_t)0);
  EXPECT_TRUE(my_set.empty());

  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitializersetConstructor) {
  s21::set<int> my_set{1, 2, 3, 7, 9};
  std::set<int> std_set{1, 2, 3, 7, 9};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitializersetConstructor_1) {
  s21::set<int> my_set{50, 40, 60, 40};
  std::set<int> std_set{50, 40, 60, 40};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitializersetConstructor_2) {
  std::initializer_list<int> b;
  s21::set<int> my_set{b};
  std::set<int> std_set{b};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> my_set{1, 2, 3};
  s21::set<int> my_set_copy(my_set);
  std::set<int> std_set{1, 2, 3};
  std::set<int> std_set_copy(std_set);
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructor_1) {
  s21::set<int> my_set{2, 1, 3};
  s21::set<int> my_set_copy(my_set);
  std::set<int> std_set{2, 1, 3};
  std::set<int> std_set_copy(std_set);
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructor_2) {
  s21::set<int> my_set{50, 40, 45};
  s21::set<int> my_set_copy(my_set);
  std::set<int> std_set{50, 40, 45};
  std::set<int> std_set_copy(std_set);
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructor_3) {
  s21::set<int> my_set{50, 40, 45, 60, 55};
  s21::set<int> my_set_copy(my_set);
  std::set<int> std_set{50, 40, 45, 60, 55};
  std::set<int> std_set_copy(std_set);
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructorEmpty) {
  s21::set<int> my_set;
  s21::set<int> my_set_copy(my_set);
  std::set<int> std_set;
  std::set<int> std_set_copy(std_set);
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> my_set{1, 2, 3};
  s21::set<int> my_set_copy(my_set);
  s21::set<int> my_set_move(std::move(my_set));
  std::set<int> std_set{1, 2, 3};
  std::set<int> std_set_copy(std_set);
  std::set<int> std_set_move(std::move(std_set));
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, MoveConstructorEmpty) {
  s21::set<int> my_set;
  s21::set<int> my_set_copy(my_set);
  s21::set<int> my_set_move(std::move(my_set));
  std::set<int> std_set;
  std::set<int> std_set_copy(std_set);
  std::set<int> std_set_move(std::move(std_set));
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, MoveAssignmentOperator) {
  s21::set<int> my_set{1, 2, 3};
  s21::set<int> my_set_copy(my_set);
  s21::set<int> my_set_move = std::move(my_set);
  std::set<int> std_set{1, 2, 3};
  std::set<int> std_set_copy(std_set);
  std::set<int> std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(SetTest, MoveAssignmentOperatorEmpty) {
  s21::set<int> my_set;
  s21::set<int> my_set_copy(my_set);
  s21::set<int> my_set_move = std::move(my_set);
  std::set<int> std_set;
  std::set<int> std_set_copy(std_set);
  std::set<int> std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(SetTest, Empty) {
  s21::set<int> my_set;
  std::set<int> std_set;
  EXPECT_EQ(my_set.empty(), std_set.empty());
  my_set.insert(10);
  std_set.insert(10);
  EXPECT_EQ(my_set.empty(), std_set.empty());
}

TEST(SetTest, Size) {
  s21::set<int> my_set{1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> std_set{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, SizeEmpty) {
  s21::set<int> my_set;
  std::set<int> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, MaxSize) {
  s21::set<int> my_set_empty;
  std::set<int> std_set_empty;
  EXPECT_EQ(my_set_empty.max_size(), std_set_empty.max_size());
}

TEST(SetTest, Clear) {
  s21::set<int> my_set{1, 2, 3, 4};
  my_set.clear();
  std::set<int> std_set{1, 2, 3, 4};
  std_set.clear();
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, ClearEmpty) {
  s21::set<int> my_set;
  my_set.clear();
  std::set<int> std_set;
  std_set.clear();
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, Swap) {
  s21::set<int> my_set1{1, 2, 3, 4, 5};
  s21::set<int> my_set2{6, 7, 8, 9, 10, 11};
  my_set1.swap(my_set2);

  std::set<int> std_set1{1, 2, 3, 4, 5};
  std::set<int> std_set2{6, 7, 8, 9, 10, 11};
  std_set1.swap(std_set2);

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
  EXPECT_TRUE(compare_sets(my_set2, std_set2));
}

TEST(SetTest, Swap_2) {
  s21::set<int> my_set1{1, 5, 8, 100};
  s21::set<int> my_set2;
  my_set1.swap(my_set2);

  std::set<int> std_set1{1, 5, 8, 100};
  std::set<int> std_set2;
  std_set1.swap(std_set2);

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
  EXPECT_TRUE(compare_sets(my_set2, std_set2));
}

TEST(SetTest, Swap_3) {
  s21::set<int> my_set1{1, 5, 8, 100};
  s21::set<int> my_set2;
  my_set2.swap(my_set1);

  std::set<int> std_set1{1, 5, 8, 100};
  std::set<int> std_set2;
  std_set2.swap(std_set1);

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
  EXPECT_TRUE(compare_sets(my_set2, std_set2));
}

TEST(SetTest, Swap_4) {
  s21::set<int> my_set1;
  s21::set<int> my_set2;
  my_set2.swap(my_set1);

  std::set<int> std_set1;
  std::set<int> std_set2;
  std_set2.swap(std_set1);

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
  EXPECT_TRUE(compare_sets(my_set2, std_set2));
}

TEST(SetTest, begin_1) {
  s21::set<int> my_set1{500, 15000, 30000};

  std::set<int> std_set2{500, 15000, 30000};
  EXPECT_EQ(*my_set1.begin(), *std_set2.begin());
}

TEST(SetTest, begin_3_throw) {
  s21::set<int> my_set1;

  EXPECT_EQ(*my_set1.begin(), 0);
}

TEST(SetTest, end_1) {
  s21::set<int> my_set1{500, 15000, 30000};

  std::set<int> std_set2{500, 15000, 30000};
  EXPECT_EQ(*my_set1.begin(), *std_set2.begin());
}

TEST(SetTest, end_2) {
  s21::set<int> my_set1;

  std::set<int> std_set2;
  EXPECT_EQ(*my_set1.end(), *std_set2.end());
}

TEST(SetTest, Merge_1) {
  s21::set<int> my_set1{1, 9999, 20000};
  s21::set<int> my_set2{500, 15000, 30000};
  my_set1.merge(my_set2);

  std::set<int> std_set1{1, 9999, 20000};
  std::set<int> std_set2{500, 15000, 30000};
  std_set1.merge(std_set2);
  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Merge_2) {
  s21::set<int> my_set1{1, 9999, 20000};
  s21::set<int> my_set2{15000, 30000};
  my_set1.merge(my_set2);

  std::set<int> std_set1{1, 9999, 20000};
  std::set<int> std_set2{15000, 30000};
  std_set1.merge(std_set2);
  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Merge_3) {
  s21::set<int> my_set1{1, 20000, 666};
  s21::set<int> my_set2{15000, 154, 124, 30000};
  my_set1.merge(my_set2);

  std::set<int> std_set1{1, 20000, 666};
  std::set<int> std_set2{15000, 154, 124, 30000};
  std_set1.merge(std_set2);
  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Merge_4) {
  s21::set<int> my_set1;
  s21::set<int> my_set2{15000, 154, 124, 30000};
  my_set1.merge(my_set2);

  std::set<int> std_set1;
  std::set<int> std_set2{15000, 154, 124, 30000};
  std_set1.merge(std_set2);
  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Merge_5) {
  s21::set<int> my_set1{1, 20000, 666};
  s21::set<int> my_set2;
  my_set1.merge(my_set2);

  std::set<int> std_set1{1, 20000, 666};
  std::set<int> std_set2;
  std_set1.merge(std_set2);
  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Merge_6) {
  s21::set<int> my_set1;
  s21::set<int> my_set2;
  my_set1.merge(my_set2);

  std::set<int> std_set1;
  std::set<int> std_set2;
  std_set1.merge(std_set2);
  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Insert_1) {
  s21::set<int> my_set1{1, 9999, 20000};
  my_set1.insert(5);

  std::set<int> std_set1{1, 9999, 20000};
  std_set1.insert(5);

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Insert_3) {
  s21::set<int> my_set1;
  my_set1.insert(5);

  std::set<int> std_set1;
  std_set1.insert(5);

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
  my_set1.insert(5);
  std_set1.insert(5);
}

TEST(SetTest, Insert_4) {
  s21::set<int> my_set1{50, 40, 30};
  my_set1.insert(40);

  std::set<int> std_set1{50, 40, 30};
  std_set1.insert(40);

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
  my_set1.insert(40);
  std_set1.insert(40);
}

TEST(SetTest, Erase_1) {
  s21::set<int> my_set1{1, 9999, 20000};
  my_set1.erase(my_set1.begin());

  std::set<int> std_set1{1, 9999, 20000};
  std_set1.erase(std_set1.begin());

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Erase_2_throw) {
  s21::set<int> my_set1{1, 9999, 20000};

  EXPECT_THROW(my_set1.erase(my_set1.end()), std::invalid_argument);
}

TEST(SetTest, Erase_3) {
  s21::set<int> my_set1{1, 9999, 20000};
  my_set1.erase(--my_set1.end());

  std::set<int> std_set1{1, 9999, 20000};
  std_set1.erase(std_set1.end().operator--());

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Erase_4) {
  s21::set<int> my_set1{20000, 1, 2};
  my_set1.erase(--my_set1.end());

  std::set<int> std_set1{20000, 1, 2};
  std_set1.erase(std_set1.end().operator--());

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(SetTest, Erase_5) {
  s21::set<int> my_set1{50, 60, 55};
  my_set1.erase(--my_set1.end());

  std::set<int> std_set1{50, 60, 55};
  std_set1.erase(std_set1.end().operator--());

  EXPECT_TRUE(compare_sets(my_set1, std_set1));
}

TEST(setTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(setTest, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(setTest, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(setTest, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(setTest, BeginEnd) {
  s21::set<int> s{3, 5, 1, 4, 2};
  auto it = s.begin();
  ASSERT_EQ(*it, 1);

  it = s.end();
  ASSERT_EQ(*it, 0);

  s.clear();
  it = s.begin();
  ASSERT_EQ(it, nullptr);
}

TEST(setTest, SizeMaxSize) {
  s21::set<int> s{3, 5, 1, 4, 2};
  std::set<int> s1{3, 5, 1, 4, 2};
  ASSERT_EQ(s.size(), 5);
  ASSERT_GE(s.max_size(), s1.max_size());

  s.clear();
  ASSERT_EQ(s.size(), 0);
}

TEST(setTest, Erase) {
  s21::set<int> s{1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));
}

TEST(setTest, Erase_6) {
  s21::set<int> s{50, 40, 60};
  auto it = s.find(50);
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(50));
}

TEST(setTest, Erase_7) {
  s21::set<int> s{50, 40, 45};
  auto it = s.find(45);
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(45));
}

TEST(setTest, Erase_8) {
  s21::set<int> s{50, 40, 30};
  auto it = s.find(40);
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(40));
}

TEST(setTest, Erase_9) {
  s21::set<int> s{50, 40, 30};
  auto it = s.end();
  it++;
  it--;
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(40));
}

TEST(setTest, Erase_10) {
  s21::set<int> s{50, 40, 30};
  auto it = s.find(50);
  it--;
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(40));
}

TEST(setTest, Erase_11) {
  s21::set<int> s{50, 40, 45, 41};
  auto it = s.begin();
  it++;
  s.erase(it);
  EXPECT_EQ(s.size(), 3);
  EXPECT_FALSE(s.contains(41));
}

TEST(setTest, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(setTest, Merge) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_FALSE(s2.contains(3));
}

TEST(setTest, Merge_1) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{50, 40, 45};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 6);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s1.contains(40));
  EXPECT_FALSE(s2.contains(50));
}

TEST(setTest, Find) {
  s21::set<int> s{1, 2, 3};
  auto it1 = s.find(2);
  EXPECT_EQ(*it1, 2);
  auto it2 = s.find(4);
  EXPECT_EQ(it2, s.end());
}

TEST(setTest, Find2) {
  s21::set<int> s;
  auto it = s.find(0);
  EXPECT_EQ(it, s.end());
}

TEST(setTest, RotateCheck) {
  s21::set<int> s1 = {1, 2, 3, 6, 7, 8, 9, 99, -56};
  s1.insert(-1000);
  s1.insert(-10002);
  s1.insert(-100023);
  s1.insert(-100024);
  s1.insert(-100026);
}

TEST(setTest, RotateCheck2) {
  s21::set<int> s1 = {5, 3, 7, 2, 4, 6, 8};
  s1.erase(s1.begin());
}
