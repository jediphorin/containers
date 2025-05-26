/*#include <list>
#include <gtest/gtest.h>
#include "../s21_containers.h"
#include "../funcs/s21_list.hpp"

TEST(ListInsert, endPosition) {
    int value = 777;

    s21::List<int> cstm = {1, 2, 3, 4, 5};
    auto citer = cstm.end();
    cstm.insert(citer, value);

    std::list<int> orig = {1, 2, 3, 4, 5};
    auto oiter = orig.end();
    orig.insert(oiter, value);

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}

TEST(ListInsert, middlePosition) {
    int value = 66;

    s21::List<int> cstm = {1, 2, 3, 4, 5};
    auto citer = cstm.end();
    --citer;
    --citer;
    cstm.insert(citer, value);

    std::list<int> orig = {1, 2, 3, 4, 5};
    auto oiter = orig.end();
    --oiter;
    --oiter;
    orig.insert(oiter, value);

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}

TEST(ListInsert, beginPosition) {
    int value = 8888;

    s21::List<int> cstm = {1, 2, 3, 4, 5};
    auto citer = cstm.begin();
    cstm.insert(citer, value);

    std::list<int> orig = {1, 2, 3, 4, 5};
    auto oiter = orig.begin();
    orig.insert(oiter, value);

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListInsert, sizeAfterBeginInsert)
{
    int value = 8888;

    s21::List<int> cstm = {1, 2, 3, 4, 5};
    auto citer = cstm.begin();
    cstm.insert(citer, value);

    std::list<int> orig = {1, 2, 3, 4, 5};
    auto oiter = orig.begin();
    orig.insert(oiter, value);

    ASSERT_EQ(orig.size(), cstm.size());
}
TEST(ListInsert, sizeAfterMiddleInsert)
{
    int value = 66;

    s21::List<int> cstm = {1, 2, 3, 4, 5};
    auto citer = cstm.end();
    --citer;
    --citer;
    cstm.insert(citer, value);

    std::list<int> orig = {1, 2, 3, 4, 5};
    auto oiter = orig.end();
    --oiter;
    --oiter;
    orig.insert(oiter, value);

    ASSERT_EQ(orig.size(), cstm.size());
}
TEST(ListInsert, sizeAfterEndInsert)
{
    int value = 777;

    s21::List<int> cstm = {1, 2, 3, 4, 5};
    auto citer = cstm.end();
    cstm.insert(citer, value);

    std::list<int> orig = {1, 2, 3, 4, 5};
    auto oiter = orig.end();
    orig.insert(oiter, value);

    ASSERT_EQ(orig.size(), cstm.size());
}

TEST(ListConstructor, size)
{
    s21::List<int> cstm = {1, 2, 3, 4, 5};
    std::list<int> orig = {1, 2, 3, 4, 5};

    ASSERT_EQ(orig.size(), cstm.size());
}

TEST(ListSwap, full) {

    int expected1[] = {0, 1, 2, 3, 4, 5, 6};
    int expected2[] = {10, 221, 3332, 44443, 555554, 6666665, 77777776};

    s21::List<int> cstm1 = {10, 221, 3332, 44443, 555554, 6666665, 77777776};
    s21::List<int> cstm2 = {0, 1, 2, 3, 4, 5, 6};

    cstm1.swap(cstm2);

    auto citer2 = cstm2.begin();
    auto citer1 = cstm1.begin();

    for (size_t i = 0; i < sizeof(expected2) / sizeof(expected2[0]); i++, citer2++) {
        ASSERT_EQ(*citer2, expected2[i]);
    }
    for (size_t i = 0; i < sizeof(expected1) / sizeof(expected1[0]); i++, citer1++) {
        ASSERT_EQ(*citer1, expected1[i]);
    }
}

TEST(ListSwap, empty) {
    
    int expected[] = {};

    s21::List<int> cstm1 = {};
    s21::List<int> cstm2 = {};

    cstm1.swap(cstm2);

    auto citer2 = cstm2.begin();
    auto citer1 = cstm1.begin();

    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); i++, citer2++) {
        ASSERT_EQ(*citer2, expected[i]);
    }
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); i++, citer1++) {
        ASSERT_EQ(*citer1, expected[i]);
    }
}

TEST(ListSwap, mixed) {

    int expected1[] = {};
    int expected2[] = {10, 221, 3332, 44443, 555554, 6666665, 77777776};

    s21::List<int> cstm1 = {10, 221, 3332, 44443, 555554, 6666665, 77777776};
    s21::List<int> cstm2 = {};

    cstm1.swap(cstm2);

    auto citer2 = cstm2.begin();
    auto citer1 = cstm1.begin();

    for (size_t i = 0; i < sizeof(expected2) / sizeof(expected2[0]); i++, citer2++) {
        ASSERT_EQ(*citer2, expected2[i]);
    }
    for (size_t i = 0; i < sizeof(expected1) / sizeof(expected1[0]); i++, citer1++) {
        ASSERT_EQ(*citer1, expected1[i]);
    }
}

TEST(ListErase, first)
{
    std::list<int> orig = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {1, 2, 3, 4, 5};

    auto oiter = orig.begin();
    auto citer = cstm.begin();

    auto oresult = orig.erase(oiter);
    cstm.erase(citer);
    citer = cstm.begin();
    ASSERT_EQ(*oresult, *citer);
}

TEST(ListErase, sizeFromFirst)
{
    std::list<int> orig = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {1, 2, 3, 4, 5};

    auto oiter = orig.begin();
    auto citer = cstm.begin();

    orig.erase(oiter);
    cstm.erase(citer);
    ASSERT_EQ(orig.size(), cstm.size());
}
TEST(ListErase, last)
{
    std::list<int> orig = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {1, 2, 3, 4, 5};

    auto oiter = orig.end();
    auto citer = cstm.end();  

    oiter--;
    citer--;

    orig.erase(oiter);
    cstm.erase(citer);
    
    oiter = orig.begin(), citer = cstm.begin();
    for (; oiter != orig.end(); oiter++, citer++)
    {
        ASSERT_EQ(*oiter, *citer);
    }
}
TEST(ListErase, sizeFromLast)
{
    std::list<int> orig = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {1, 2, 3, 4, 5};

    auto oiter = orig.end();
    auto citer = cstm.end();  

    oiter--;
    citer--;

    orig.erase(oiter);
    cstm.erase(citer);

    ASSERT_EQ(orig.size(), cstm.size());
}

TEST(ListErase, middle)
{
    std::list<int> orig = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {1, 2, 3, 4, 5};

    auto oiter = orig.end();
    auto citer = cstm.end();

    oiter--;
    citer--;
    oiter--;
    citer--;
    oiter--;
    citer--;
    
    orig.erase(oiter);
    cstm.erase(citer);

    oiter = orig.begin(), citer = cstm.begin();
    for (; oiter != orig.end(); oiter++, citer++)
    {
        ASSERT_EQ(*oiter, *citer);
    }
}
TEST(ListErase, sizeFromMiddle)
{
    std::list<int> orig = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {1, 2, 3, 4, 5};

    auto oiter = orig.end();
    auto citer = cstm.end();

    oiter--;
    citer--;
    oiter--;
    citer--;
    oiter--;
    citer--;
    
    orig.erase(oiter);
    cstm.erase(citer);

    ASSERT_EQ(orig.size(), cstm.size());
}

TEST(ListReverse, ordinary)
{
    s21::List<int> cstm = {1, 2, 3, 4, 5};
    std::list<int> orig = {1, 2, 3, 4, 5};

    cstm.reverse();
    orig.reverse();

    auto citer = cstm.begin();
    auto oiter = orig.begin();
    for (; citer != cstm.end(); ++citer, ++oiter)
    {
        ASSERT_EQ(*citer, *oiter);
    }
}
TEST(ListSplice, size)
{
    std::list<int> expected_list = {1, 2, 3, 4};

    std::list<int> a = {1, 2};
    std::list<int> b = {3, 4};
    a.splice(a.end(), b);

    s21::List<int> target_list = {1, 2};
    s21::List<int> source_list = {3, 4};
    target_list.splice(target_list.cend(), source_list);

    ASSERT_EQ(target_list.size(), a.size());
    ASSERT_EQ(source_list.size(), b.size());
}
TEST(ListSplice, inEnd)
{
    std::list<int> expected_list = {1, 2, 3, 4};

    std::list<int> a = {1, 2};
    std::list<int> b = {3, 4};
    a.splice(a.end(), b);

    s21::List<int> target_list = {1, 2};
    s21::List<int> source_list = {3, 4};
    target_list.splice(target_list.cend(), source_list);

    auto eli = expected_list.begin();
    auto tli = target_list.begin();
    for (; tli != target_list.end(); ++tli, ++eli)
    {
        ASSERT_EQ(*tli, *eli);
    }
}
TEST(ListSplice, inBegin)
{
    std::list<int> expected_list = {3, 4, 1, 2};

    std::list<int> a = {1, 2};
    std::list<int> b = {3, 4};
    a.splice(a.begin(), b);

    s21::List<int> target_list = {1, 2};
    s21::List<int> source_list = {3, 4};
    target_list.splice(target_list.cbegin(), source_list);

    auto eli = expected_list.begin();
    auto tli = target_list.begin();
    for (; tli != target_list.end(); ++tli, ++eli)
    {
        ASSERT_EQ(*tli, *eli);
    }
}
TEST(ListSplice, inMiddle)
{
    std::list<int> expected_list = {1, 3, 4, 2};

    std::list<int> a = {1, 2};
    std::list<int> b = {3, 4};
    a.splice(++(a.begin()), b);

    s21::List<int> target_list = {1, 2};
    s21::List<int> source_list = {3, 4};
    target_list.splice(++(target_list.cbegin()), source_list);

    auto eli = expected_list.begin();
    auto tli = target_list.begin();
    for (; tli != target_list.end(); ++tli, ++eli)
    {
        ASSERT_EQ(*tli, *eli);
    }
}

TEST(ListUnique, begin)
{
    std::list<int> expected_list = {1, 2, 3, 4};
    auto eli = expected_list.begin();

    s21::List<int> cstm = {1, 1, 1, 2, 3, 4};
    cstm.unique();

    for (auto i = cstm.begin(); i != cstm.end(); ++i, ++eli)
    {
        ASSERT_EQ(*i, *eli);
    }
}
TEST(ListUnique, middle)
{
    std::list<int> expected_list = {1, 2, 3, 4};
    auto eli = expected_list.begin();

    s21::List<int> cstm = {1, 2, 2, 2, 3, 4};
    cstm.unique();

    for (auto i = cstm.begin(); i != cstm.end(); ++i, ++eli)
    {
        ASSERT_EQ(*i, *eli);
    }
}
TEST(ListUnique, end)
{
    std::list<int> expected_list = {1, 2, 3, 4};
    auto eli = expected_list.begin();

    s21::List<int> cstm = {1, 2, 3, 4, 4, 4};
    cstm.unique();

    for (auto i = cstm.begin(); i != cstm.end(); ++i, ++eli)
    {
        ASSERT_EQ(*i, *eli);
    }
}

//  excel22
TEST(ListMerge, a_OneThree)
{
    std::list<int> orig1 = {5};
    std::list<int> orig2 = {1, 4, 9};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {5};
    s21::List<int> cstm2 = {1, 4, 9};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, ab_notSorted)
{
    std::list<int> orig1 = {4, 5, 6, 7};
    std::list<int> orig2 = {1, 2, 3, 8, 3};    
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {4, 5, 6, 7};
    s21::List<int> cstm2 = {1, 2, 3, 8, 3};    
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, b_firstListEmpty) {
    std::list<int> orig1 = {};
    std::list<int> orig2 = {1, 2, 3};
    orig1.merge(orig2);

    s21::List<int> cstm1;
    s21::List<int> cstm2 = {1, 2, 3};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, bc_secondListEmpty) {
    std::list<int> orig1 = {4, 5, 6};
    std::list<int> orig2 = {};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {4, 5, 6};
    s21::List<int> cstm2;
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, c_allElementsSmaller) {
    std::list<int> orig1 = {4, 5, 6};
    std::list<int> orig2 = {1, 2, 3};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {4, 5, 6};
    s21::List<int> cstm2 = {1, 2, 3};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, cd_v3test)
{
    std::list<int> orig1 = {2, 4, 6};
    std::list<int> orig2 = {1, 3, 5};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {2, 4, 6};
    s21::List<int> cstm2 = {1, 3, 5};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, d_s21v3test)
{
    std::list<int> orig1 = {2, 4, 6};
    std::list<int> orig2 = {1};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {2, 4, 6};
    s21::List<int> cstm2 = {1};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}

TEST(ListMerge, de_s21v3test2)
{
    std::list<int> orig1 = {2, 4, 6};
    std::list<int> orig2 = {1, 3, 5};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {2, 4, 6};
    s21::List<int> cstm2 = {1, 3, 5};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, e_curGreaterThanActOneAndOne)
{
    std::list<int> orig1 = {4};
    std::list<int> orig2 = {1, 2};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {4};
    s21::List<int> cstm2 = {1, 2};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, ef_curGreaterThanActTwoAndTwo)
{
    std::list<int> orig1 = {3, 4};
    std::list<int> orig2 = {1, 2};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {3, 4};
    s21::List<int> cstm2 = {1, 2};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, f_curGreaterThanActTwoAndOne)
{
    std::list<int> orig1 = {5, 9};
    std::list<int> orig2 = {1};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {5, 9};
    s21::List<int> cstm2 = {1};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, fg_curLessOrEqThanActOneAndOne)
{
    std::list<int> orig1 = {1};
    std::list<int> orig2 = {4};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {1};
    s21::List<int> cstm2 = {4};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, g_curLessOrEqThanActOneAndTwo)
{
    std::list<int> orig1 = {1};
    std::list<int> orig2 = {4, 6};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {1};
    s21::List<int> cstm2 = {4, 6};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, gh_curLessOrEqThanActTwoAndOne)
{
    std::list<int> orig1 = {1, 4};
    std::list<int> orig2 = {6};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {1, 4};
    s21::List<int> cstm2 = {6};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, h_curLessOrEqThanActTwoAndOne)
{
    std::list<int> orig1 = {1, 8};
    std::list<int> orig2 = {3};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {1, 8};
    s21::List<int> cstm2 = {3};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, hj_curLessOrEqThanActTwoAndTwo)
{
    std::list<int> orig1 = {1, 2};
    std::list<int> orig2 = {3, 9};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {1, 2};
    s21::List<int> cstm2 = {3, 9};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel 1
TEST(ListMerge, j_zeroZero)
{
    std::list<int> orig1 = {};
    std::list<int> orig2 = {};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {};
    s21::List<int> cstm2 = {};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel2
TEST(ListMerge, jk_zeroOne)
{
    std::list<int> orig1 = {};
    std::list<int> orig2 = {1};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {};
    s21::List<int> cstm2 = {1};
    cstm1.merge(cstm2);

    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel3
TEST(ListMerge, k_oneZero)
{
    std::list<int> orig1 = {1};
    std::list<int> orig2 = {};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1};
    s21::List<int> cstm2 = {};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel4
TEST(ListMerge, kl_oneLessOne)
{
    std::list<int> orig1 = {1};
    std::list<int> orig2 = {2};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1};
    s21::List<int> cstm2 = {2};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel5
TEST(ListMerge, l_oneMoreOne)
{
    std::list<int> orig1 = {2};
    std::list<int> orig2 = {1};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {2};
    s21::List<int> cstm2 = {1};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel6
TEST(ListMerge, lm_twoOne)
{
    std::list<int> orig1 = {2, 3};
    std::list<int> orig2 = {1};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {2, 3};
    s21::List<int> cstm2 = {1};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel7
TEST(ListMerge, m_oneTwo)
{
    std::list<int> orig1 = {1};
    std::list<int> orig2 = {2, 3};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1};
    s21::List<int> cstm2 = {2, 3};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel8
TEST(ListMerge, mn_twoOneV2)
{
    std::list<int> orig1 = {1, 3};
    std::list<int> orig2 = {2};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 3};
    s21::List<int> cstm2 = {2};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel9
TEST(ListMerge, n_oneTwoV2)
{
    std::list<int> orig1 = {2};
    std::list<int> orig2 = {1, 3};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {2};
    s21::List<int> cstm2 = {1, 3};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel10
TEST(ListMerge, no_twoOneV3)
{
    std::list<int> orig1 = {1, 2};
    std::list<int> orig2 = {3};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 2};
    s21::List<int> cstm2 = {3};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel11
TEST(ListMerge, o_oneTwoV3)
{
    std::list<int> orig1 = {3};
    std::list<int> orig2 = {1, 2};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {3};
    s21::List<int> cstm2 = {1, 2};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel12
TEST(ListMerge, op_twoTwo)
{
    std::list<int> orig1 = {1, 3};
    std::list<int> orig2 = {2, 4};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 3};
    s21::List<int> cstm2 = {2, 4};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel13
TEST(ListMerge, p_twoTwo_reversed)
{
    std::list<int> orig1 = {2, 4};
    std::list<int> orig2 = {1, 3};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {2, 4};
    s21::List<int> cstm2 = {1, 3};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel14
TEST(ListMerge, pq_twoTwoV2)
{
    std::list<int> orig1 = {1, 2};
    std::list<int> orig2 = {3, 4};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 2};
    s21::List<int> cstm2 = {3, 4};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel15
TEST(ListMerge, q_twoTwoV2_reversed)
{
    std::list<int> orig1 = {3, 4};
    std::list<int> orig2 = {1, 2};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {3, 4};
    s21::List<int> cstm2 = {1, 2};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel16
TEST(ListMerge, qr_twoTwoV3)
{
    std::list<int> orig1 = {1, 4};
    std::list<int> orig2 = {2, 3};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 4};
    s21::List<int> cstm2 = {2, 3};
    cstm1.merge(cstm2);
        
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel16
TEST(ListMerge, r_twoTwoV3_reversed)
{
    std::list<int> orig1 = {2, 3};
    std::list<int> orig2 = {1, 4};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {2, 3};
    s21::List<int> cstm2 = {1, 4};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel17
TEST(ListMerge, rs_threeTwo)
{
    std::list<int> orig1 = {1, 3, 5};
    std::list<int> orig2 = {2, 6};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 3, 5};
    s21::List<int> cstm2 = {2, 6};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel17
TEST(ListMerge, s_twothree)
{
    std::list<int> orig1 = {2, 6};
    std::list<int> orig2 = {1, 3, 5};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {2, 6};
    s21::List<int> cstm2 = {1, 3, 5};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel18
TEST(ListMerge, st_threeTwoV2)
{
    std::list<int> orig1 = {1, 5, 7};
    std::list<int> orig2 = {8, 9};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 5, 7};
    s21::List<int> cstm2 = {8, 9};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel17
TEST(ListMerge, t_twothreeV2)
{
    std::list<int> orig1 = {8, 9};
    std::list<int> orig2 = {1, 5, 7};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {8, 9};
    s21::List<int> cstm2 = {1, 5, 7};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel18
TEST(ListMerge, tu_threeThree)
{
    std::list<int> orig1 = {1, 3, 5};
    std::list<int> orig2 = {2, 4, 6};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 3, 5};
    s21::List<int> cstm2 = {2, 4, 6};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel19
TEST(ListMerge, u_threeThree_reversed)
{
    std::list<int> orig1 = {2, 4, 6};
    std::list<int> orig2 = {1, 3, 5};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {2, 4, 6};
    s21::List<int> cstm2 = {1, 3, 5};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel20
TEST(ListMerge, uv_threeThreeV2)
{
    std::list<int> orig1 = {1, 2, 3};
    std::list<int> orig2 = {5, 6, 7};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {1, 2, 3};
    s21::List<int> cstm2 = {5, 6, 7};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel21
TEST(ListMerge, v_threeThreeV2_reversed)
{
    std::list<int> orig1 = {5, 6, 7};
    std::list<int> orig2 = {1, 2, 3};
    orig1.merge(orig2);
    
    s21::List<int> cstm1 = {5, 6, 7};
    s21::List<int> cstm2 = {1, 2, 3};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
//  excel23
TEST(ListMerge, vw_threeOne)
{
    std::list<int> orig1 = {1, 4, 9};
    std::list<int> orig2 = {5};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {1, 4, 9};
    s21::List<int> cstm2 = {5};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}

//  успех
TEST(ListMerge, w_unsorted)
{
    std::list<int> orig1 = {4, 5, 6, 7};
    std::list<int> orig2 = {1, 2, 3, 9, 8, 1, 2, 3};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {4, 5, 6, 7};
    s21::List<int> cstm2 = {1, 2, 3, 9, 8, 1, 2, 3};    
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, wx_unsorted)
{
    std::list<int> orig1 = {4};
    std::list<int> orig2 = {9, 8, 1, 2, 3};
    orig1.merge(orig2);

    s21::List<int> cstm1 = {4};
    s21::List<int> cstm2 = {9, 8, 1, 2, 3};
    cstm1.merge(cstm2);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListMerge, x_yourself)
{
    std::list<int> orig1 = {4};
    orig1.merge(orig1);

    s21::List<int> cstm1 = {4};
    cstm1.merge(cstm1);
    
    auto i = orig1.begin();
    auto j = cstm1.begin();
    for (; i != orig1.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}

TEST(ListSort, a_emptyList)
{
    s21::List<int> cstm = {};
    cstm.sort();
}
TEST(ListSort, b_one_node)
{
    std::list<int> orig = {3};
    orig.sort();
    s21::List<int> cstm = {3};
    cstm.sort();
}
TEST(ListSort, c_two_nodes)
{
    std::list<int> orig = {9, 1};
    orig.sort();

    s21::List<int> cstm = {9, 1};
    cstm.sort();

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListSort, d_three_nodes)
{
    std::list<int> orig = {3, 2, 1};
    orig.sort();
    s21::List<int> cstm = {3, 2, 1};
    cstm.sort();
    
    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListSort, e_sorted_four_nodes)
{
    s21::List<int> cstm = {1, 2, 3, 4};
    cstm.sort();
    std::list<int> orig = {1, 2, 3, 4};
    orig.sort();

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListSort, d_five_nodes)
{
    s21::List<int> cstm = {1, 2, 4, 3, 1};
    cstm.sort();
    std::list<int> orig = {1, 2, 4, 3, 1};
    orig.sort();

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListSort, f_five_nodes)
{
    s21::List<int> cstm = {2, 1, 4, 1, 3};
    cstm.sort();
    std::list<int> orig = {2, 1, 4, 1, 3};
    orig.sort();

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListSort, g_five_nodes)
{
    s21::List<int> cstm = {1, 2, 4, 1, 3};
    cstm.sort();
    std::list<int> orig = {1, 2, 4, 1, 3};
    orig.sort();

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(ListSort, h_five_nodes)
{
    s21::List<int> cstm = {2, 1, 4, 3, 1};
    cstm.sort();
    std::list<int> orig = {2, 1, 4, 3, 1};
    orig.sort();

    auto i = orig.begin();
    auto j = cstm.begin();
    for (; i != orig.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}

TEST(InsertManyBack, a_simple)
{
    std::list<int> expected = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {1, 2, 3};
    cstm.insert_many_back(4, 5);
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(InsertManyBack, b_push_to_empty_list)
{
    std::list<int> expected = {4, 5};
    s21::List<int> cstm = {};
    cstm.insert_many_back(4, 5);
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(InsertManyBack, c_push_empty)
{
    std::list<int> expected = {4, 5};
    s21::List<int> cstm = {4, 5};
    cstm.insert_many_back();
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(InsertManyBack, d_push_empty_to_empty_list)
{
    std::list<int> expected = {};
    s21::List<int> cstm = {};
    cstm.insert_many_back();
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}

TEST(InsertManyFront, a_simple)
{
    std::list<int> expected = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {3, 4, 5};
    cstm.insert_many_front(1, 2);
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(InsertManyFront, b_push_empty_to_empty)
{
    std::list<int> expected = {};
    s21::List<int> cstm = {};
    cstm.insert_many_front();
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(InsertManyFront, c_push_to_empty_list)
{
    std::list<int> expected = {4, 5};
    s21::List<int> cstm = {};
    cstm.insert_many_front(4, 5);
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(InsertManyFront, d_push_empty)
{
    std::list<int> expected = {4, 5};
    s21::List<int> cstm = {4, 5};
    cstm.insert_many_front();
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}

TEST(InsertMany, a_simple)
{
    std::list<int> expected = {1, 2, 3, 4, 5};
    s21::List<int> cstm = {4, 5};
    auto iter = cstm.begin();
    cstm.insert_many(iter, 1, 2, 3);
    auto i = expected.begin();
    auto j = cstm.begin();
    for (; i != expected.end(); ++i, ++j)
    {
        ASSERT_EQ(*i, *j);
    }
}
TEST(IMOM, a_simple)
{
    s21::List<int> cstm = {1, 2, 3, 4};
    auto iter = cstm.begin();
    ++iter;
    cstm.insert_many(iter, 55, 66, 77);
    // auto iter2 = iter - 2;
    cstm.print_list();
}*/