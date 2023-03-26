#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "segment_tree/segment_tree.h"

#include <vector>

TEST_CASE("Memory leak check")
{
#if defined(_WIN32) && defined(_DEBUG)
    // Enable memory-leak reports
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif
}

int Combine(int a, int b)
{
    return a + b;
}

/*
                 36
          20            16
      13      7      9      7
    5    8  4   3  7   2  1   6
*/

TEST_CASE("Initialize 1")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    SegmentTree<int> tree{ data, Combine, 0 };

    REQUIRE_EQ(tree.GetTreeSize(), 16);

    for (int i = 0; i < 8; ++i)
    {
        REQUIRE_EQ(tree[i], data[i]);
    }

    const int* p = tree.GetTree();

    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 36);
    REQUIRE_EQ(p[2], 20);
    REQUIRE_EQ(p[3], 16);
    REQUIRE_EQ(p[4], 13);
    REQUIRE_EQ(p[5], 7);
    REQUIRE_EQ(p[6], 9);
    REQUIRE_EQ(p[7], 7);
    REQUIRE_EQ(p[8], 5);
    REQUIRE_EQ(p[9], 8);
    REQUIRE_EQ(p[10], 4);
    REQUIRE_EQ(p[11], 3);
    REQUIRE_EQ(p[12], 7);
    REQUIRE_EQ(p[13], 2);
    REQUIRE_EQ(p[14], 1);
    REQUIRE_EQ(p[15], 6);
}

TEST_CASE("Initialize 2")
{
    int data[7] = { 5, 8, 4, 3, 7, 2, 1 };
    SegmentTree<int> tree{ data, Combine, 0 };

    REQUIRE_EQ(tree.GetTreeSize(), 16);

    for (int i = 0; i < 7; ++i)
    {
        REQUIRE_EQ(tree[i], data[i]);
    }

    const int* p = tree.GetTree();

    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 30);
    REQUIRE_EQ(p[2], 20);
    REQUIRE_EQ(p[3], 10);
    REQUIRE_EQ(p[4], 13);
    REQUIRE_EQ(p[5], 7);
    REQUIRE_EQ(p[6], 9);
    REQUIRE_EQ(p[7], 1);
    REQUIRE_EQ(p[8], 5);
    REQUIRE_EQ(p[9], 8);
    REQUIRE_EQ(p[10], 4);
    REQUIRE_EQ(p[11], 3);
    REQUIRE_EQ(p[12], 7);
    REQUIRE_EQ(p[13], 2);
    REQUIRE_EQ(p[14], 1);
    REQUIRE_EQ(p[15], 0);
}

TEST_CASE("Update")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    SegmentTree<int> tree{ data, Combine, 0 };

    const int* p = tree.GetTree();

    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 36);
    REQUIRE_EQ(p[2], 20);
    REQUIRE_EQ(p[3], 16);
    REQUIRE_EQ(p[4], 13);
    REQUIRE_EQ(p[5], 7);
    REQUIRE_EQ(p[6], 9);
    REQUIRE_EQ(p[7], 7);
    REQUIRE_EQ(p[8], 5);
    REQUIRE_EQ(p[9], 8);
    REQUIRE_EQ(p[10], 4);
    REQUIRE_EQ(p[11], 3);
    REQUIRE_EQ(p[12], 7);
    REQUIRE_EQ(p[13], 2);
    REQUIRE_EQ(p[14], 1);
    REQUIRE_EQ(p[15], 6);

    tree.Update(4, 10);

    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 39);
    REQUIRE_EQ(p[2], 20);
    REQUIRE_EQ(p[3], 19);
    REQUIRE_EQ(p[4], 13);
    REQUIRE_EQ(p[5], 7);
    REQUIRE_EQ(p[6], 12);
    REQUIRE_EQ(p[7], 7);
    REQUIRE_EQ(p[8], 5);
    REQUIRE_EQ(p[9], 8);
    REQUIRE_EQ(p[10], 4);
    REQUIRE_EQ(p[11], 3);
    REQUIRE_EQ(p[12], 10);
    REQUIRE_EQ(p[13], 2);
    REQUIRE_EQ(p[14], 1);
    REQUIRE_EQ(p[15], 6);
}

TEST_CASE("Query")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    SegmentTree<int> tree{ data, Combine, 0 };

    REQUIRE_EQ(tree.Query(0, 2), 13);
    REQUIRE_EQ(tree.Query(0, 8), 36);
    REQUIRE_EQ(tree.Query(1, 7), 25);
    REQUIRE_EQ(tree.Query(0, 7), 30);
    REQUIRE_EQ(tree.Query(3, 4), 3);
    REQUIRE_EQ(tree.Query(2, 6), 16);
}

TEST_CASE("Insert 1")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    SegmentTree<int> tree{ data, Combine, 0 };

    tree.Insert(3, 9);

    const int* p = tree.GetTree();

    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 45);
    REQUIRE_EQ(p[2], 39);
    REQUIRE_EQ(p[3], 6);
    REQUIRE_EQ(p[4], 26);
    REQUIRE_EQ(p[5], 13);
    REQUIRE_EQ(p[6], 6);
    REQUIRE_EQ(p[7], 0);
    REQUIRE_EQ(p[8], 13);
    REQUIRE_EQ(p[9], 13);
    REQUIRE_EQ(p[10], 10);
    REQUIRE_EQ(p[11], 3);
    REQUIRE_EQ(p[12], 6);
    REQUIRE_EQ(p[13], 0);
    REQUIRE_EQ(p[14], 0);
    REQUIRE_EQ(p[15], 0);
    REQUIRE_EQ(p[16], 5);
    REQUIRE_EQ(p[17], 8);
    REQUIRE_EQ(p[18], 4);
    REQUIRE_EQ(p[19], 9);
    REQUIRE_EQ(p[20], 3);
    REQUIRE_EQ(p[21], 7);
    REQUIRE_EQ(p[22], 2);
    REQUIRE_EQ(p[23], 1);
    REQUIRE_EQ(p[24], 6);
    REQUIRE_EQ(p[25], 0);
    REQUIRE_EQ(p[26], 0);
    REQUIRE_EQ(p[27], 0);
    REQUIRE_EQ(p[28], 0);
    REQUIRE_EQ(p[29], 0);
    REQUIRE_EQ(p[30], 0);
    REQUIRE_EQ(p[31], 0);
}

TEST_CASE("Insert 2")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    SegmentTree<int> tree1{ data, Combine, 0 };
    SegmentTree<int> tree2{ data, Combine, 0 };

    tree1.Insert(8, 123);
    tree2.PushBack(123);

    for (int i = 0; i < tree1.GetTreeSize(); ++i)
    {
        REQUIRE_EQ(tree1.GetTree()[i], tree2.GetTree()[i]);
    }
}

TEST_CASE("Copy ctor")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    const SegmentTree<int> tree1{ data, Combine, 0 };
    SegmentTree<int> tree2{ tree1 };

    REQUIRE_EQ(tree1.GetCount(), tree2.GetCount());
    REQUIRE_EQ(tree1.GetTreeSize(), tree2.GetTreeSize());
    REQUIRE_NE(tree1.GetTree(), tree2.GetTree());

    for (int i = 0; i < tree1.GetTreeSize(); ++i)
    {
        REQUIRE_EQ(tree1.GetTree()[i], tree2.GetTree()[i]);
    }
}

TEST_CASE("Copy assign")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    int data2[4] = { 1, 2, 3, 4 };
    const SegmentTree<int> tree1{ data, Combine, 0 };
    SegmentTree<int> tree2{ data2, Combine, 0 };

    const int* p = tree2.GetTree();

    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 10);
    REQUIRE_EQ(p[2], 3);
    REQUIRE_EQ(p[3], 7);
    REQUIRE_EQ(p[4], 1);
    REQUIRE_EQ(p[5], 2);
    REQUIRE_EQ(p[6], 3);
    REQUIRE_EQ(p[7], 4);

    tree2 = tree1;

    p = tree2.GetTree();
    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 36);
    REQUIRE_EQ(p[2], 20);
    REQUIRE_EQ(p[3], 16);
    REQUIRE_EQ(p[4], 13);
    REQUIRE_EQ(p[5], 7);
    REQUIRE_EQ(p[6], 9);
    REQUIRE_EQ(p[7], 7);
    REQUIRE_EQ(p[8], 5);
    REQUIRE_EQ(p[9], 8);
    REQUIRE_EQ(p[10], 4);
    REQUIRE_EQ(p[11], 3);
    REQUIRE_EQ(p[12], 7);
    REQUIRE_EQ(p[13], 2);
    REQUIRE_EQ(p[14], 1);
    REQUIRE_EQ(p[15], 6);

    REQUIRE_EQ(tree1.GetCount(), tree2.GetCount());
    REQUIRE_EQ(tree1.GetTreeSize(), tree2.GetTreeSize());
    REQUIRE_NE(tree1.GetTree(), tree2.GetTree());

    for (int i = 0; i < tree1.GetTreeSize(); ++i)
    {
        REQUIRE_EQ(tree1.GetTree()[i], tree2.GetTree()[i]);
    }
}

TEST_CASE("Move ctor")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    SegmentTree<int> tree1{ data, Combine, 0 };
    SegmentTree<int> tree2{ std::move(tree1) };

    REQUIRE_EQ(tree1.GetCount(), 0);
    REQUIRE_EQ(tree1.GetTreeSize(), 0);
    REQUIRE_EQ(tree1.GetTree(), nullptr);

    const int* p = tree2.GetTree();

    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 36);
    REQUIRE_EQ(p[2], 20);
    REQUIRE_EQ(p[3], 16);
    REQUIRE_EQ(p[4], 13);
    REQUIRE_EQ(p[5], 7);
    REQUIRE_EQ(p[6], 9);
    REQUIRE_EQ(p[7], 7);
    REQUIRE_EQ(p[8], 5);
    REQUIRE_EQ(p[9], 8);
    REQUIRE_EQ(p[10], 4);
    REQUIRE_EQ(p[11], 3);
    REQUIRE_EQ(p[12], 7);
    REQUIRE_EQ(p[13], 2);
    REQUIRE_EQ(p[14], 1);
    REQUIRE_EQ(p[15], 6);
}

TEST_CASE("Move assign")
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    int data2[4] = { 1, 2, 3, 4 };
    SegmentTree<int> tree1{ data, Combine, 0 };
    SegmentTree<int> tree2{ data2, Combine, 0 };

    const int* p = tree2.GetTree();

    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 10);
    REQUIRE_EQ(p[2], 3);
    REQUIRE_EQ(p[3], 7);
    REQUIRE_EQ(p[4], 1);
    REQUIRE_EQ(p[5], 2);
    REQUIRE_EQ(p[6], 3);
    REQUIRE_EQ(p[7], 4);

    tree2 = std::move(tree1);

    REQUIRE_EQ(tree1.GetCount(), 0);
    REQUIRE_EQ(tree1.GetTreeSize(), 0);
    REQUIRE_EQ(tree1.GetTree(), nullptr);

    p = tree2.GetTree();
    REQUIRE_EQ(p[0], 0);
    REQUIRE_EQ(p[1], 36);
    REQUIRE_EQ(p[2], 20);
    REQUIRE_EQ(p[3], 16);
    REQUIRE_EQ(p[4], 13);
    REQUIRE_EQ(p[5], 7);
    REQUIRE_EQ(p[6], 9);
    REQUIRE_EQ(p[7], 7);
    REQUIRE_EQ(p[8], 5);
    REQUIRE_EQ(p[9], 8);
    REQUIRE_EQ(p[10], 4);
    REQUIRE_EQ(p[11], 3);
    REQUIRE_EQ(p[12], 7);
    REQUIRE_EQ(p[13], 2);
    REQUIRE_EQ(p[14], 1);
    REQUIRE_EQ(p[15], 6);
}