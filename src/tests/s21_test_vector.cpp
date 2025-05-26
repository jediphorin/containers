#include <gtest/gtest.h>
#include "../funcs/s21_vector.hpp"
#include <vector>
#include "../s21_containers.h"
#include <random>

TEST(VectorDataFull, success) {
  std::vector<int> orig = {10, 221, 3332};
  s21::Vector<int> cstm = {10, 221, 3332};
  ASSERT_EQ(*orig.data(), *cstm.data());
  ASSERT_NE(orig.data(), cstm.data());
}

TEST(VectorDestructor, success) {
  // Создаём два вектора: ваш и std::vector
  {
      s21::Vector<int> cstm = {1, 2, 3};
      std::vector<int> orig = {1, 2, 3};

      // Проверяем, что оба вектора содержат данные
      EXPECT_NE(cstm.data(), nullptr);
      EXPECT_NE(orig.data(), nullptr);
  }

  // Векторы вышли из области видимости, их деструкторы были вызваны
  // Проверяем, что память освобождена (это можно проверить только косвенно)
  // Например, создадим новые векторы и убедимся, что они работают корректно
  s21::Vector<int> cstm_new = {4, 5, 6};
  std::vector<int> orig_new = {4, 5, 6};
  size_t expected = 3;
  EXPECT_EQ(cstm_new.size(), expected);
  EXPECT_EQ(orig_new.size(), expected);
}

TEST(VectorInsertOther, success) {
  s21::Vector<int> cstm = {1, 2, 3};

  // Вставка в начало
  auto it = cstm.insert(cstm.begin(), 0);
  assert(*it == 0);
  assert(cstm.size() == 4);

  // Вставка в середину
  it = cstm.insert(cstm.begin() + 2, 5);
  assert(*it == 5);
  assert(cstm.size() == 5);

  // Вставка в конец
  it = cstm.insert(cstm.end(), 10);
  assert(*it == 10);
  assert(cstm.size() == 6);

  // Вставка элемента, который ссылается на сам вектор
  it = cstm.insert(cstm.begin(), cstm.back());
  assert(*it == 10);
  assert(cstm.size() == 7);
}
TEST(VectorConstructorDefaultSize, success)
{
  s21::Vector<int> cstm_vctr;
  std::vector<int> std_vctr;
  ASSERT_EQ(cstm_vctr.size(), std_vctr.size());
}
TEST(VectorConstructorDefaultCapacity, success)
{
  s21::Vector<int> cstm_vctr;
  std::vector<int> std_vctr;
  ASSERT_EQ(cstm_vctr.capacity(), std_vctr.capacity());
}
TEST(VectorConstructorDefaultArray, success)
{
  s21::Vector<int> cstm_vctr;
  std::vector<int> std_vctr;
  ASSERT_EQ(cstm_vctr.data(), std_vctr.data());
}

TEST(VectorConstructorParametrizedSize, success)
{
  const int size = 3;
  s21::Vector<int> cstm_vctr(size);
  std::vector<int> std_vctr(size);
  ASSERT_EQ(cstm_vctr.size(), std_vctr.size());
}
TEST(VectorConstructorParametrizedSizeZero, success)
{
  const int size = 0;
  s21::Vector<int> cstm_vctr(size);
  std::vector<int> std_vctr(size);
  ASSERT_EQ(cstm_vctr.size(), std_vctr.size());
}
TEST(VectorConstructorParametrizedCapacity, success)
{
  const int size = 3;
  s21::Vector<int> cstm_vctr(size);
  std::vector<int> std_vctr(size);
  ASSERT_EQ(cstm_vctr.capacity(), std_vctr.capacity());
}
TEST(VectorConstructorParametrizedCapacityWithSizeZero, success)
{
  const int size = 0;
  s21::Vector<int> cstm_vctr(size);
  std::vector<int> std_vctr(size);
  ASSERT_EQ(cstm_vctr.capacity(), std_vctr.capacity());
}
TEST(VectorConstructorParametrizedArray, success)
{
  const int size = 3;
  s21::Vector<int> cstm_vctr(size);
  std::vector<int> std_vctr(size);
  EXPECT_NE(cstm_vctr.data(), std_vctr.data());
}
TEST(VectorConstructorParametrizedArrayWithSizeZero, success)
{
  const int size = 0;
  s21::Vector<int> cstm_vctr(size);
  std::vector<int> std_vctr(size);
  ASSERT_EQ(cstm_vctr.data(), std_vctr.data());
}
TEST(VectorConstructorInitSize, success)
{
  s21::Vector<int> cstm_vctr = {1, 2, 3};
  std::vector<int> std_vctr = {1, 2, 3};
  ASSERT_EQ(cstm_vctr.size(), std_vctr.size());
}
TEST(VectorConstructorInitSizeZero, success)
{
  s21::Vector<int> cstm_vctr = {};
  std::vector<int> std_vctr = {};
  ASSERT_EQ(cstm_vctr.size(), std_vctr.size());
}
TEST(VectorConstructorInitCapacity, success)
{
  s21::Vector<int> cstm_vctr = {1, 2, 3};
  std::vector<int> std_vctr = {1, 2, 3};
  ASSERT_EQ(cstm_vctr.capacity(), std_vctr.capacity());
}
TEST(VectorConstructorInitCapacityWithSizeZero, success)
{
  s21::Vector<int> cstm_vctr = {};
  std::vector<int> std_vctr = {};
  ASSERT_EQ(cstm_vctr.capacity(), std_vctr.capacity());
}
TEST(VectorConstructorInitWithSizeZero, success)
{
  s21::Vector<int> cstm_vctr = {};
  std::vector<int> std_vctr = {};
  const size_t size = 0;
  ASSERT_EQ(cstm_vctr.size(), size);
  ASSERT_EQ(std_vctr.size(), size);
}
TEST(VectorCopyConstructorSame, success)
{
  std::vector<int> std_original = {1, 2, 3};
  s21::Vector<int> s21_original = {1, 2, 3};
  std::vector<int> std_copy(std_original);
  s21::Vector<int> s21_copy(s21_original);
  ASSERT_EQ(std_original.size(), s21_original.size());
  ASSERT_EQ(std_original.capacity(), s21_original.capacity());
  for (long unsigned int i = 0; i < std_original.size(); i++)
  {
    ASSERT_EQ(std_original.data()[i], std_copy.data()[i]);
    ASSERT_EQ(s21_original.data()[i], s21_copy.data()[i]);

    ASSERT_EQ(std_original.data()[i], s21_copy.data()[i]);
    ASSERT_EQ(s21_original.data()[i], std_copy.data()[i]);
  }
}
TEST(VectorCopyConstructorDifferent, fail)
{
  std::vector<int> std_original = {1, 2, 3};
  s21::Vector<int> s21_original = {9, 8, 7};
  std::vector<int> copy_std_vctr(std_original);
  s21::Vector<int> copy_cstm_vctr(s21_original);
  for (long unsigned int i = 0; i < std_original.size(); i++)
  {
    ASSERT_NE(std_original.data()[i], s21_original.data()[i]);
  }
}

TEST(VectorMoveConstructor, success) {
  // Создаём исходные векторы
  s21::Vector<int> cstm = {1, 2, 3};
  std::vector<int> orig = {1, 2, 3};

  // Перемещаем векторы
  s21::Vector<int> cstm_moved(std::move(cstm));
  std::vector<int> orig_moved(std::move(orig));

  // Проверяем, что размеры совпадают
  EXPECT_EQ(cstm_moved.size(), orig_moved.size());

  // Проверяем, что содержимое совпадает
  for (size_t i = 0; i < cstm_moved.size(); ++i) {
      EXPECT_EQ(cstm_moved[i], orig_moved[i]);
  }

  // Проверяем, что исходные векторы пусты после перемещения
  size_t expected = 0;
  EXPECT_EQ(cstm.size(), expected);
  EXPECT_EQ(orig.size(), expected);

  // Проверяем, что capacity исходных векторов равна 0
  EXPECT_EQ(cstm.capacity(), expected);
  EXPECT_EQ(orig.capacity(), expected);

  // Проверяем, что указатели на данные исходных векторов равны nullptr
  EXPECT_EQ(cstm.data(), nullptr);
  EXPECT_EQ(orig.data(), nullptr);
}

// Тест для сравнения перемещающего присваивания
TEST(VectorMoveConstructorComparison, success) {
  s21::Vector<int> cstm1 = {1, 2, 3};
  s21::Vector<int> cstm2 = std::move(cstm1);

  std::vector<int> std_vec1 = {1, 2, 3};
  std::vector<int> std_vec2 = std::move(std_vec1);

  // Проверяем, что размеры совпадают
  EXPECT_EQ(cstm2.size(), std_vec2.size());

  // Проверяем, что содержимое совпадает
  for (size_t i = 0; i < cstm2.size(); ++i) {
      EXPECT_EQ(cstm2[i], std_vec2[i]);
  }

  // Проверяем, что исходный вектор пуст после перемещения
  size_t expected = 0;
  EXPECT_EQ(cstm1.size(), expected);
  EXPECT_EQ(std_vec1.size(), expected);
}

TEST(VectorMoveConstructorEmpty, success) {
  // Создаём пустые векторы
  s21::Vector<int> cstm;
  std::vector<int> orig;

  // Перемещаем векторы
  s21::Vector<int> cstm_moved(std::move(cstm));
  std::vector<int> orig_moved(std::move(orig));

  // Проверяем, что размеры совпадают
  EXPECT_EQ(cstm_moved.size(), orig_moved.size());

  size_t expected = 0;
  // Проверяем, что оба перемещённых вектора пусты
  EXPECT_EQ(cstm_moved.size(), expected);
  EXPECT_EQ(orig_moved.size(), expected);

  // Проверяем, что исходные векторы пусты после перемещения
  EXPECT_EQ(cstm.size(), expected);
  EXPECT_EQ(orig.size(), expected);

  // Проверяем, что capacity исходных векторов равна 0
  EXPECT_EQ(cstm.capacity(), expected);
  EXPECT_EQ(orig.capacity(), expected);

  // Проверяем, что указатели на данные исходных векторов равны nullptr
  EXPECT_EQ(cstm.data(), nullptr);
  EXPECT_EQ(orig.data(), nullptr);
}

TEST(VectorPushBackOther, fail)
{
  s21::Vector<int> cstm_vctr = {2, 4, 6, 8};
  std::vector<int> std_vctr = {2, 4, 6, 8};

  int s21_begin_size = cstm_vctr.size();
  int s21_start_capacity = cstm_vctr.capacity();
  int std_begin_size = std_vctr.size();
  int std_start_capacity = std_vctr.capacity();
  cstm_vctr.push_back(9);
  std_vctr.push_back(9);
  int s21_finish_capacity = cstm_vctr.capacity();
  int s21_end_size = cstm_vctr.size();
  int std_finish_capacity = std_vctr.capacity();
  int std_end_size = std_vctr.size();
  ASSERT_NE(s21_begin_size, s21_end_size);
  ASSERT_EQ(s21_finish_capacity, (s21_start_capacity * 2));
  ASSERT_NE(std_begin_size, std_end_size);
  ASSERT_EQ(std_finish_capacity, (std_start_capacity * 2));

  ASSERT_NE(s21_begin_size, std_end_size);
  ASSERT_EQ(s21_finish_capacity, (std_start_capacity * 2));
  ASSERT_NE(std_begin_size, s21_end_size);
  ASSERT_EQ(std_finish_capacity, (s21_start_capacity * 2));
}
TEST(VectorPushBackArray, success)
{
  s21::Vector<int> cstm_vctr = {2, 4, 6, 8};
  std::vector<int> std_vctr = {2, 4, 6, 8};

  cstm_vctr.push_back(9);
  std_vctr.push_back(9);

  for (long unsigned int i = 0; i < std_vctr.size(); i++)
  {
    ASSERT_EQ(std_vctr.data()[i], cstm_vctr.data()[i]);
  }
}
TEST(VectorPushBackArrayStdCstm, fail)
{
  s21::Vector<int> cstm_vctr = {2, 4, 6};
  std::vector<int> std_vctr = {9, 7, 5};

  cstm_vctr.push_back(8);
  std_vctr.push_back(3);

  for (long unsigned int i = 0; i < std_vctr.size(); i++)
  {
    ASSERT_NE(std_vctr.data()[i], cstm_vctr.data()[i]);
  }
}
TEST(VectorMoveConstructorSame, success)
{
  s21::Vector<int> cstm_orig = {2, 4, 6};
  int cstm_orig_size = cstm_orig.size();
  int cstm_orig_capacity = cstm_orig.capacity();
  s21::Vector<int> cstm_copy(cstm_orig);

  std::vector<int> std_orig = {2, 4, 6};
  int std_orig_size = std_orig.size();
  int std_orig_capacity = std_orig.capacity();
  std::vector<int> std_copy(std_orig);

  ASSERT_EQ(cstm_orig_size, std_orig_size);
  ASSERT_EQ(cstm_orig_capacity, std_orig_capacity);

  s21::Vector<int> move_cstm(std::move(cstm_copy));
  for (long unsigned int i = 0; i < std_orig.size(); i++)
  {
    ASSERT_EQ(move_cstm.data()[i], std_orig.data()[i]);
  }
}
TEST(VectorMoveConstructorDifferent, fail)
{
  s21::Vector<int> cstm_orig = {2, 4, 6};
  int cstm_orig_size = cstm_orig.size();
  int cstm_orig_capacity = cstm_orig.capacity();
  s21::Vector<int> cstm_copy(cstm_orig);

  std::vector<int> std_orig = {9, 7, 5};
  int std_orig_size = std_orig.size();
  int std_orig_capacity = std_orig.capacity();
  std::vector<int> std_copy(std_orig);

  ASSERT_EQ(cstm_orig_size, std_orig_size);
  ASSERT_EQ(cstm_orig_capacity, std_orig_capacity);

  s21::Vector<int> move_cstm(std::move(cstm_copy));
  for (long unsigned int i = 0; i < std_orig.size(); i++)
  {
    ASSERT_NE(move_cstm.data()[i], std_orig.data()[i]);
  }
}
TEST(VectorAt, success)
{
  std::vector<int> vctr_std = {2, 4, 6};
  s21::Vector<int> vctr_s21 = {2, 4, 6};

  for (long unsigned int i = 0; i < vctr_std.size(); i++)
  {
    ASSERT_EQ(vctr_std.at(i), vctr_s21.at(i));
  }
}
TEST(VectorAtOutOfRange, fail)
{
  std::vector<int> vctr_std = {2, 4, 6};
  s21::Vector<int> vctr_s21 = {2, 4, 6};

  EXPECT_THROW(vctr_std.at(10), std::out_of_range);
  EXPECT_THROW(vctr_s21.at(10), std::out_of_range);
}
TEST(VectorOperatorArray, success)
{
  int middle = 3;
  s21::Vector<int> vctr_cstm = {1, middle, 5};
  ASSERT_EQ(vctr_cstm[1], middle);
  std::vector<int> vctr_std = {1, middle, 5};
  ASSERT_EQ(vctr_std[1], middle);

  ASSERT_EQ(vctr_cstm[1], vctr_std[1]);
}
TEST(VectorOperatorArrayDifferent, fail)
{
  s21::Vector<int> vctr_cstm = {1, 3, 5};
  std::vector<int> vctr_std = {1, 3, 5};
  long unsigned int index_for_compare = 10;
  if (index_for_compare < vctr_std.size())
  {
    ASSERT_NE(vctr_cstm[index_for_compare], vctr_std[index_for_compare]);
  }
}
TEST(VectorFront, success)
{
  int first_element = 9;
  std::vector<int> orig = {first_element, 5, 1};
  s21::Vector<int> cstm = {first_element, 5, 1};
  ASSERT_EQ(orig.front(), cstm.front());
  ASSERT_EQ(orig.front(), first_element);
  ASSERT_EQ(first_element, cstm.front());
}
TEST(VectorFrontkEmpty, success)
{ 
  s21::Vector<int> cstm = {};
  EXPECT_THROW(cstm.front(), std::out_of_range);
}
TEST(VectorBack, success)
{
  int last_element = 11;
  std::vector<int> orig = {9, 5, last_element};
  s21::Vector<int> cstm = {9, 5, last_element};
  ASSERT_EQ(orig.back(), cstm.back());
  ASSERT_EQ(orig.back(), last_element);
  ASSERT_EQ(last_element, cstm.back());
}
TEST(VectorBackEmpty, success)
{ 
  s21::Vector<int> cstm = {};
  EXPECT_THROW(cstm.back(), std::out_of_range);
}
TEST(VectorEmpty, fail)
{
  s21::Vector<int> cstm = {1, 3, 5};
  ASSERT_FALSE(cstm.empty());
  std::vector<int> orig = {1, 3, 5};
  ASSERT_FALSE(orig.empty());
}
TEST(VectorEmpty, success)
{
  s21::Vector<int> cstm;
  ASSERT_TRUE(cstm.empty());
  std::vector<int> orig;
  ASSERT_TRUE(orig.empty());
}

TEST(VectorMaxSize, success)
{
  std::vector<int> orig = {1, 2, 3};
  s21::Vector<int> cstm = {1, 2, 3};
  ASSERT_EQ(orig.max_size(), cstm.max_size());
}

TEST(VectorReserve, success)
{
  std::vector<int> orig = {1, 2, 3};
  ASSERT_EQ(orig.capacity(), orig.size());
  int capacity_new = 98;
  orig.reserve(capacity_new);
  s21::Vector<int> cstm = {1, 2, 3};
  ASSERT_EQ(cstm.capacity(), cstm.size());
  cstm.reserve(capacity_new);
  ASSERT_EQ(orig.capacity(), cstm.capacity());
}
TEST(VectorReserveSecond, success) {
  std::vector<int> orig = {0};
  s21::Vector<int> cstm = {0};
  ASSERT_EQ(orig.size(), cstm.size());
  ASSERT_EQ(orig.capacity(), cstm.capacity());
  
  std::random_device rd;  // Источник энтропии (случайное начальное значение)
  std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)
    
  // Задаём диапазон случайных чисел (например, от 0 до 99)
  std::uniform_int_distribution<> dist(0, 99);
    
  for (size_t i = 0; i < 64; i++) {
    // Генерация случайного числа
    int x = dist(gen);
    orig.push_back(x);
    cstm.push_back(x);
    ASSERT_EQ(orig.size(), cstm.size());
    ASSERT_EQ(orig.capacity(), cstm.capacity());
  }
}

TEST(VectorShrink, success)
{
  std::vector<int> orig = {1, 2, 3};
  ASSERT_EQ(orig.capacity(), orig.size());
  int capacity_new = 98;
  orig.reserve(capacity_new);
  orig.shrink_to_fit();

  size_t size = 3;

  s21::Vector<int> cstm = {1, 2, 3};
  ASSERT_EQ(cstm.capacity(), cstm.size());
  cstm.reserve(capacity_new);
  cstm.shrink_to_fit();

  ASSERT_EQ(orig.capacity(), size);
  ASSERT_EQ(size, cstm.capacity());
  ASSERT_EQ(orig.size(), size);
  ASSERT_EQ(size, cstm.size());
}
TEST(VectorClear, success)
{
  std::vector<int> orig = {1, 2, 3};
  s21::Vector<int> cstm = {1, 2, 3};

  int size_before = orig.size();
  int cstm_size_before = cstm.size();
  ASSERT_EQ(size_before, cstm_size_before);

  int capacity_before = orig.capacity();
  int cstm_capacity_before = cstm.capacity();
  ASSERT_EQ(capacity_before, cstm_capacity_before);

  orig.clear();
  cstm.clear();

  int size_after = orig.size();
  int cstm_size_after = cstm.size();
  int expected_size = 0;
  ASSERT_EQ(expected_size, size_after);
  ASSERT_EQ(expected_size, cstm_size_after);

  int capacity_after = orig.capacity();
  int cstm_capacity_after = cstm.capacity();
  int expected_capacity = 3;
  ASSERT_EQ(expected_capacity, capacity_after);
  ASSERT_EQ(expected_capacity, cstm_capacity_after);

  ASSERT_NE(size_before, size_after);
  ASSERT_NE(cstm_size_before, cstm_size_after);

  ASSERT_EQ(capacity_before, capacity_after);
  ASSERT_EQ(cstm_capacity_before, cstm_capacity_after);
}
TEST(VectorBegin, success)
{
  int first = 333;
  std::vector<int> orig = {first, 22, 1};
  s21::Vector<int> cstm = {first, 22, 1};
  std::vector<int>::iterator orig_iter = orig.begin();
  s21::Vector<int>::iterator cstm_iter = cstm.begin();
  ASSERT_EQ(first, *orig_iter);
  ASSERT_EQ(first, *cstm_iter);
}
TEST(VectorOperatorMinusMinusPre, success)
{
  std::vector<int> orig = {1, 22, 333};
  s21::Vector<int> cstm = {1, 22, 333};
  size_t expected = 0;
  ASSERT_NE(cstm.size(), expected);

  std::vector<int>::iterator orig_iter = orig.end();
  // int expected_value = *orig_iter;
  s21::Vector<int>::iterator cstm_iter = cstm.end();

  --orig_iter;
  --cstm_iter;

  // ASSERT_EQ(expected_value, *cstm_iter);
  ASSERT_EQ(*orig_iter, *cstm_iter);

  --orig_iter;
  // expected_value = *orig_iter;
  --cstm_iter;
  // ASSERT_EQ(expected_value, *cstm_iter);
  ASSERT_EQ(*orig_iter, *cstm_iter);
}

TEST(VectorOperatorMinusMinusPost, success)
{
  std::vector<int> orig = {1, 22, 333};
  s21::Vector<int> cstm = {1, 22, 333};
  size_t expected = 0;
  ASSERT_NE(cstm.size(), expected);
  s21::Vector<int>::iterator cstm_iter = cstm.end();
  std::vector<int>::iterator orig_iter = orig.end();
  
  orig_iter--;
  cstm_iter--;
  
  ASSERT_EQ(*orig_iter, *cstm_iter);
}

TEST(VectorEnd, success)
{
  int last = 333;
  std::vector<int> orig = {1, 22, last};
  s21::Vector<int> cstm = {1, 22, last};
  size_t expected = 0;
  ASSERT_NE(cstm.size(), expected);
  ASSERT_NE(orig.size(), expected);

  std::vector<int>::iterator orig_iter = orig.end(); 
  s21::Vector<int>::iterator cstm_iter = cstm.end();

  ASSERT_NE(orig_iter, orig.begin());
  ASSERT_NE(cstm_iter, cstm.begin());
  
  orig_iter--;
  cstm_iter--;

  ASSERT_EQ(last, *cstm_iter);
  ASSERT_EQ(last, *orig_iter);
}

TEST(VectorOperatorPlusPlusPre, success)
{
  std::vector<int> orig = {1, 22, 333};
  std::vector<int>::iterator orig_iter = orig.begin();
  ++orig_iter;
  int expected_value = *orig_iter;

  s21::Vector<int> cstm = {1, 22, 333};
  s21::Vector<int>::iterator cstm_iter = cstm.begin();
  ++cstm_iter;
  ASSERT_EQ(expected_value, *cstm_iter);
}

TEST(VectorOperatorPlusPlusPost, success)
{
  std::vector<int> orig = {1, 22, 333};
  std::vector<int>::iterator orig_iter = orig.begin();
  orig_iter++;
  int expected_value = *orig_iter;

  s21::Vector<int> cstm = {1, 22, 333};
  s21::Vector<int>::iterator cstm_iter = cstm.begin();
  cstm_iter++;
  ASSERT_EQ(expected_value, *cstm_iter);
}



//  тест разделить. Проверить удаление в начале середине, вне итератора, пустой вектор. Capacity, size
TEST(VectorEraseFirst, success)
{
  int future_first = 10;

  std::vector<int> orig = {0, future_first, 221, 3332, 44443};
  std::vector<int>::iterator orig_iter = orig.begin();
  orig.erase(orig_iter);

  s21::Vector<int> cstm = {0, future_first, 221, 3332, 44443};
  s21::Vector<int>::iterator cstm_iter = cstm.begin();
  cstm.erase(cstm_iter);

  ASSERT_EQ(orig.capacity(), cstm.capacity());
  ASSERT_EQ(orig.size(), cstm.size());
  orig_iter = orig.begin();
  ASSERT_EQ(future_first, *orig_iter);
  cstm_iter = cstm.begin();
  ASSERT_EQ(future_first, *cstm_iter);
}

//  Удаление в конце
TEST(VectorEraseLast, success)
{
  int future_last = 3332;

  std::vector<int> orig = {0, 10, 221, future_last, 44443};
  std::vector<int>::iterator orig_iter = orig.end();
  --orig_iter;
  orig.erase(orig_iter);

  s21::Vector<int> cstm = {0, 10, 221, future_last, 44443};
  s21::Vector<int>::iterator cstm_iter = cstm.end();
  --cstm_iter;
  cstm.erase(cstm_iter);

  ASSERT_EQ(orig.capacity(), cstm.capacity());
  ASSERT_EQ(orig.size(), cstm.size());
  orig_iter = orig.end();
  --orig_iter;
  ASSERT_EQ(future_last, *orig_iter);
  cstm_iter = cstm.end();
  --cstm_iter;
  ASSERT_EQ(future_last, *cstm_iter);
}

//  удаление вне вектора. Т.к. метод erase() прописан по-другому, то поведение оригинала я не сравниваю со своей реализацией.
// Оригинал не выбрасывает исключений.
TEST(VectorEraseOutBegin, fail)
{
  s21::Vector<int> cstm = {0, 10, 221};
  s21::Vector<int>::iterator cstm_iter = cstm.end();
  int shift = -1000;
  cstm_iter = cstm.begin() + shift;
  EXPECT_THROW(cstm.erase(cstm_iter), std::out_of_range);
}
TEST(VectorEraseOutEnd, fail)
{
  s21::Vector<int> cstm = {0, 10, 221};
  s21::Vector<int>::iterator cstm_iter = cstm.end();
  int shift = 1000;
  cstm_iter = cstm.begin() + shift;
  EXPECT_THROW(cstm.erase(cstm_iter), std::out_of_range);
}

TEST(VectorPopBack, success) {
  std::vector<int> orig = {0, 1, 22, 333, 4444};
  orig.pop_back();
  s21::Vector<int> cstm = {0, 1, 22, 333, 4444};
  cstm.pop_back();
  
  auto cstm_iter = cstm.begin();
  auto orig_iter = orig.begin();
  for (; cstm_iter < cstm.end(); ++cstm_iter, ++orig_iter) {
    ASSERT_EQ(*cstm_iter, *orig_iter);
  }
  ASSERT_EQ(cstm.size(), orig.size());
}

TEST(VectorPopBackOneElement, success) {
  std::vector<int> orig = {333};
  s21::Vector<int> cstm = {333};
  orig.pop_back();
  cstm.pop_back();
  ASSERT_EQ(cstm.size(), orig.size());
  ASSERT_EQ(cstm.capacity(), orig.capacity());
}

TEST(VectorPopBackZeroElement, success) {
  std::vector<int> orig = {};
  s21::Vector<int> cstm = {};

  orig.pop_back();
  cstm.pop_back();

  std::cout << cstm.capacity() << std::endl;
  ASSERT_EQ(cstm.capacity(), orig.capacity());
}

TEST(VectorSwapEqualElements, success) {
  std::vector<int> orig_first = {0, 1, 22};
  std::vector<int> orig_second = {333, 4444, 55555};
  orig_first.swap(orig_second);
  
  s21::Vector<int> cstm_first = {0, 1, 22};
  s21::Vector<int> cstm_second = {333, 4444, 55555};
  cstm_first.swap(cstm_second);

  auto cf_iter = cstm_first.begin();
  auto of_iter = orig_first.begin();
  for(; cf_iter < cstm_first.end(); ++cf_iter, ++of_iter) {
    ASSERT_EQ(*cf_iter, *of_iter);
  }
  ASSERT_EQ(cstm_first.size(), orig_first.size());
  ASSERT_EQ(cstm_first.capacity(), orig_first.capacity());
}

TEST(VectorSwapNotEqualElements, success) {
  int fourth = 666666;

  std::vector<int> orig_first = {0, 1, 22};
  std::vector<int> orig_second = {333, 4444, 55555, fourth};
  orig_first.swap(orig_second);
  
  s21::Vector<int> cstm_first = {0, 1, 22};
  s21::Vector<int> cstm_second = {333, 4444, 55555, fourth};
  cstm_first.swap(cstm_second);
  
  ASSERT_EQ(cstm_first.size(), orig_first.size());
  ASSERT_EQ(cstm_first.capacity(), orig_first.capacity());
  
  auto of_iter = orig_first.end();
  --of_iter;
  ASSERT_EQ(fourth, *of_iter);
  
  auto cf_iter = cstm_first.end();
  --cf_iter;
  ASSERT_EQ(fourth, *cf_iter);
}

TEST(VectorSwapOneEmpty, success) {
  int fourth = 666666;

  std::vector<int> orig_first = {};
  std::vector<int> orig_second = {4444, 55555, fourth};
  orig_first.swap(orig_second);

  s21::Vector<int> cstm_first = {};
  s21::Vector<int> cstm_second = {4444, 55555, fourth};
  cstm_first.swap(cstm_second);
  
  auto cf_iter = cstm_first.begin();
  auto of_iter = orig_first.begin();
  for(; cf_iter < cstm_first.end(); ++cf_iter, ++of_iter) {
    ASSERT_EQ(*cf_iter, *of_iter);
  }
  ASSERT_EQ(orig_first.size(), cstm_first.size());
  ASSERT_EQ(orig_first.capacity(), cstm_first.capacity());
  ASSERT_EQ(orig_second.size(), cstm_second.size());
  ASSERT_EQ(orig_second.capacity(), cstm_second.capacity());
}

TEST(VectorSwapAllEmpty, success) {
  std::vector<int> orig_first = {};
  std::vector<int> orig_second = {};
  orig_first.swap(orig_second);

  s21::Vector<int> cstm_first = {};
  s21::Vector<int> cstm_second = {};
  cstm_first.swap(cstm_second);
  
  auto cf_iter = cstm_first.begin();
  auto of_iter = orig_first.begin();
  for(; cf_iter < cstm_first.end(); ++cf_iter, ++of_iter) {
    ASSERT_EQ(*cf_iter, *of_iter);
  }
  ASSERT_EQ(orig_first.size(), cstm_first.size());
  ASSERT_EQ(orig_first.capacity(), cstm_first.capacity());
  ASSERT_EQ(orig_second.size(), cstm_second.size());
  ASSERT_EQ(orig_second.capacity(), cstm_second.capacity());
}

TEST(VectorInsert, success)
{
  std::vector<int> orig = {0, 1, 22};
  std::vector<int>::iterator orig_iter = orig.end();
  orig.insert(orig_iter, 333);
  orig_iter = orig.end();
  orig.insert(orig_iter, 4444);
  orig_iter = orig.begin();
  orig.insert(orig_iter, -1);

  s21::Vector<int> cstm = {0, 1, 22};
  s21::Vector<int>::iterator cstm_iter = cstm.end();
  cstm.insert(cstm_iter, 333);
  cstm_iter = cstm.end();
  cstm.insert(cstm_iter, 4444);
  cstm_iter = cstm.begin();
  cstm.insert(cstm_iter, -1);

  orig_iter = orig.begin();
  cstm_iter = cstm.begin();
  for (; orig_iter != orig.end(); cstm_iter++, orig_iter++)
  {
    ASSERT_EQ(*cstm_iter, *orig_iter);
  }
}
TEST(VectorInsertMiddle, success) {
  std::vector<int> orig = {0, 11, 3333, 44444};
  s21::Vector<int> cstm = {0, 11, 3333, 44444};
  
  auto orig_iter = orig.begin() + 2;
  auto cstm_iter = cstm.begin() + 2;
  
  orig.insert(orig_iter, 222);  
  cstm.insert(cstm_iter, 222);

  orig_iter = orig.begin();
  cstm_iter = cstm.begin();
  for (; orig_iter < orig.end(); cstm_iter++, orig_iter++)
  {
    ASSERT_EQ(*cstm_iter, *orig_iter);
  }
}

TEST(VectorInsertEmpty, success) {
  std::vector<int> orig = {};
  std::vector<int>::iterator orig_iter = orig.end();
  orig.insert(orig_iter, 333);
  orig_iter = orig.end();
  orig.insert(orig_iter, 4444);
  orig_iter = orig.begin();
  orig.insert(orig_iter, -1);

  s21::Vector<int> cstm = {};
  s21::Vector<int>::iterator cstm_iter = cstm.end();
  cstm.insert(cstm_iter, 333);
  cstm_iter = cstm.end();
  cstm.insert(cstm_iter, 4444);
  cstm_iter = cstm.begin();
  cstm.insert(cstm_iter, -1);

  orig_iter = orig.begin();
  cstm_iter = cstm.begin();
  for (; orig_iter != orig.end(); cstm_iter++, orig_iter++)
  {
    ASSERT_EQ(*cstm_iter, *orig_iter);
  }
}

TEST(VectorInsertManyInMiddle, success) {
  s21::Vector<int> cstm = {0, 1, 2, 6, 7, 8, 9};
  auto cstm_pos = cstm.begin() + 3;
  cstm.insert_many(cstm_pos, 3, 4, 5);

  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  cstm_pos = cstm.begin();
  auto expected_pos = expected.begin();
  for (; expected_pos < expected.end(); ++expected_pos, ++cstm_pos) {
    ASSERT_EQ(*cstm_pos, *expected_pos);
  }
}

TEST(VectorInsertManyEnd, success) {
  s21::Vector<int> cstm = {0, 1, 2, 3, 4, 5, 6};
  auto cstm_pos = cstm.end();
  cstm.insert_many(cstm_pos, 7, 8, 9);

  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  cstm_pos = cstm.begin();
  auto expected_pos = expected.begin();
  for (; expected_pos < expected.end(); ++expected_pos, ++cstm_pos) {
    ASSERT_EQ(*cstm_pos, *expected_pos);
  }
}

TEST(VectorInsertManyEmpty, success) {
  s21::Vector<int> cstm = {};
  auto cstm_pos = cstm.begin();
  EXPECT_THROW(*cstm_pos, std::out_of_range);
  cstm.insert_many(cstm_pos, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto expected_pos = expected.begin();
  cstm_pos = cstm.begin();
  for (; expected_pos < expected.end(); ++expected_pos, ++cstm_pos) {
    ASSERT_EQ(*cstm_pos, *expected_pos);
  }
}

TEST(VectorInsertManyBegin, success) {
  s21::Vector<int> cstm = {3, 4, 5, 6, 7, 8, 9};
  auto cstm_pos = cstm.begin();
  cstm.insert_many(cstm_pos, 0, 1, 2);

  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  auto expected_pos = expected.begin();
  cstm_pos = cstm.begin();
  for (; expected_pos < expected.end(); ++expected_pos, ++cstm_pos) {
    ASSERT_EQ(*cstm_pos, *expected_pos);
  }
}

TEST(VectorInsertOutBegin, success) {
  s21::Vector<int> cstm = {};
  auto cstm_pos = cstm.begin() - 2;
  EXPECT_THROW(cstm.insert(cstm_pos, 10), std::out_of_range);
}

TEST(VectorInsertOutEnd, success) {
  s21::Vector<int> cstm = {};
  auto cstm_pos = cstm.end() + 2;
  EXPECT_THROW(cstm.insert(cstm_pos, 10), std::out_of_range);
}

TEST(VectorInsertManyBackEmpty, success) {

  std::vector<int> expected = {3332, 221, 10};
  s21::Vector<int> cstm = {};
  cstm.insert_many_back(3332, 221, 10);
  
  auto expected_iter = expected.begin();
  auto cstm_iter = cstm.begin();

  for (; cstm_iter < cstm.end(); cstm_iter++, expected_iter++) {
    ASSERT_EQ(*cstm_iter, *expected_iter);
  }
}

TEST(VectorInsertManyBackFull, success) {

  std::vector<int> expected = {44443, 3332, 221, 10};
  s21::Vector<int> cstm = {44443, 3332};
  cstm.insert_many_back(221, 10);

  auto expected_iter = expected.begin();
  auto cstm_iter = cstm.begin();

  for (; cstm_iter < cstm.end(); cstm_iter++, expected_iter++) {
    ASSERT_EQ(*cstm_iter, *expected_iter);
  }
}