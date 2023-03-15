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
}
