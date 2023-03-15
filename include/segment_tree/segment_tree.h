#pragma once

#include <cassert>
#include <cmath>
#include <span>

#define left(i) (2 * i)
#define right(i) (2 * i + 1)
#define parent(i) ((i) / 2)

inline size_t compute_size(size_t n)
{
    size_t exp = static_cast<size_t>(log2(n - 1)) + 2;
    return static_cast<size_t>(pow(2, exp));
}

// Tree starts from index 1, and nonValue is stored in the first
template <typename T>
class SegmentTree
{
    typedef T Combine(T, T);

public:
    SegmentTree(std::span<T> data, Combine* combineFcn, T noneValue);
    ~SegmentTree();

    T Query(size_t left, size_t right) const;
    void Update(size_t index, T newValue);
    void Insert(size_t index, T value);
    void PushBack(T value);

    T operator[](size_t index) const;

    size_t GetCount() const;
    const T* GetTree() const;
    size_t GetTreeSize() const;

private:
    T* tree;
    Combine* combineFcn;
    size_t count;
    size_t size;
    T noneValue;
};

template <typename T>
SegmentTree<T>::SegmentTree(std::span<T> _data, Combine* _combineFcn, T _noneValue)
    : combineFcn{ _combineFcn }
    , count{ _data.size() }
    , size{ compute_size(_data.size()) }
    , noneValue{ _noneValue }
{
    tree = new T[size];
    tree[0] = noneValue;

    size_t mid = size / 2;
    size_t i = 0;

    for (; i < count; ++i)
    {
        tree[mid + i] = _data[i];
    }

    for (i += mid; i < size; ++i)
    {
        tree[i] = noneValue;
    }

    i = mid - 1;
    while (i > 0)
    {
        tree[i] = combineFcn(tree[left(i)], tree[right(i)]);
        --i;
    }
}

template <typename T>
SegmentTree<T>::~SegmentTree()
{
    delete[] tree;
}

template <typename T>
T SegmentTree<T>::Query(size_t left, size_t right) const
{
    assert(left < right);

    T result = noneValue;

    size_t leafLeft = size / 2 + left;
    size_t leafRight = size / 2 + right - 1;

    while (leafLeft <= leafRight)
    {
        if (leafLeft % 2 == 1)
        {
            result = combineFcn(tree[leafLeft], result);
        }

        if (leafRight % 2 == 0)
        {
            result = combineFcn(result, tree[leafRight]);
        }

        leafLeft = parent(leafLeft + 1);
        leafRight = parent(leafRight - 1);
    }

    return result;
}

template <typename T>
void SegmentTree<T>::Update(size_t index, T newValue)
{
    size_t i = size / 2 + index;

    tree[i] = newValue;

    while (i > 1)
    {
        size_t parentIndex = parent(i);
        tree[parentIndex] = combineFcn(tree[left(parentIndex)], tree[right(parentIndex)]);
        i = parentIndex;
    }
}

template <typename T>
void SegmentTree<T>::Insert(size_t index, T value)
{
    assert(0 <= index && index <= size / 2);

    if (count == size / 2)
    {
        T* old = tree;
        tree = new T[size * 2];
        tree[0] = noneValue;

        memcpy(tree + size, old + size / 2, size / 2 * sizeof(T));

        for (size_t i = 0; i < size / 2; ++i)
        {
            tree[size + size / 2 + i] = noneValue;
        }

        delete[] old;

        size *= 2;
    }

    size_t mid = size / 2;
    size_t ptr = count;

    while (index != ptr)
    {
        tree[mid + ptr] = tree[mid + ptr - 1];
        --ptr;
    }

    tree[mid + index] = value;
    ++count;

    size_t i = mid - 1;
    while (i > 0)
    {
        tree[i] = combineFcn(tree[left(i)], tree[right(i)]);
        --i;
    }
}

template <typename T>
void SegmentTree<T>::PushBack(T value)
{
    if (count == size / 2)
    {
        T* old = tree;
        tree = new T[size * 2];
        tree[0] = noneValue;

        memcpy(tree + size, old + size / 2, size / 2 * sizeof(T));

        for (size_t i = 0; i < size / 2; ++i)
        {
            tree[size + size / 2 + i] = noneValue;
        }

        delete[] old;

        size *= 2;

        size_t mid = size / 2;
        tree[mid + count] = value;
        ++count;

        size_t i = mid - 1;
        while (i > 0)
        {
            tree[i] = combineFcn(tree[left(i)], tree[right(i)]);
            --i;
        }

        return;
    }

    Update(count, value);
    ++count;
}

template <typename T>
size_t SegmentTree<T>::GetCount() const
{
    return count;
}

template <typename T>
const T* SegmentTree<T>::GetTree() const
{
    return tree;
}

template <typename T>
size_t SegmentTree<T>::GetTreeSize() const
{
    return size;
}

template <typename T>
T SegmentTree<T>::operator[](size_t index) const
{
    return tree[size / 2 + index];
}