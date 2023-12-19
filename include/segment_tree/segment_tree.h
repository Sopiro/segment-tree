#pragma once

#include <cassert>
#include <cmath>
#include <span>

inline size_t compute_size(size_t n)
{
    size_t exp = size_t(std::log2(n - 1)) + 2;
    return size_t(std::pow(2, exp));
}

// Templated class implementation of a segment tree,
// which is a commonly used data structure for efficient range queries on arrays.
template <typename T>
class SegmentTree
{
    typedef T Combine(T, T);

public:
    SegmentTree(std::span<T> data, Combine* combineFcn, T noneValue);
    SegmentTree(std::initializer_list<T> data, Combine* combineFcn, T noneValue);
    ~SegmentTree() noexcept;

    SegmentTree(const SegmentTree& other);
    SegmentTree& operator=(const SegmentTree& other);
    SegmentTree(SegmentTree&& other) noexcept;
    SegmentTree& operator=(SegmentTree&& other) noexcept;

    T Query(size_t left, size_t right) const;
    void Update(size_t index, T newValue);
    void Insert(size_t index, T value);
    void PushBack(T value);

    T operator[](size_t index) const;

    size_t GetCount() const;
    const T* GetTree() const;
    size_t GetTreeSize() const;
    T GetNoneValue() const;

private:
    // Internal tree array
    // Root starts from index 1
    // nonValue is stored in the first element
    T* tree;

    // Combine function
    Combine* combineFcn;

    // Count of original elements in the tree
    size_t count;

    // Size of the segment tree array
    size_t size;

    size_t GetLeft(size_t i) const;
    size_t GetRight(size_t i) const;
    size_t GetParent(size_t i) const;
};

template <typename T>
inline SegmentTree<T>::SegmentTree(std::span<T> data, Combine* combineFcn, T noneValue)
    : combineFcn{ combineFcn }
    , count{ data.size() }
    , size{ compute_size(data.size()) }
{
    tree = new T[size];
    tree[0] = noneValue;

    size_t mid = size / 2;
    size_t i = 0;

    for (; i < count; ++i)
    {
        tree[mid + i] = data[i];
    }

    for (i += mid; i < size; ++i)
    {
        tree[i] = noneValue;
    }

    i = mid - 1;
    while (i > 0)
    {
        tree[i] = combineFcn(tree[GetLeft(i)], tree[GetRight(i)]);
        --i;
    }
}

template <typename T>
inline SegmentTree<T>::SegmentTree(std::initializer_list<T> data, Combine* combineFcn, T noneValue)
    : combineFcn{ combineFcn }
    , count{ data.size() }
    , size{ compute_size(data.size()) }
{
    tree = new T[size];
    tree[0] = noneValue;

    size_t mid = size / 2;
    size_t i = 0;

    for (; i < count; ++i)
    {
        tree[mid + i] = *(data.begin() + i);
    }

    for (i += mid; i < size; ++i)
    {
        tree[i] = noneValue;
    }

    i = mid - 1;
    while (i > 0)
    {
        tree[i] = combineFcn(tree[GetLeft(i)], tree[GetRight(i)]);
        --i;
    }
}

template <typename T>
inline SegmentTree<T>::~SegmentTree() noexcept
{
    delete[] tree;
}

template <typename T>
inline SegmentTree<T>::SegmentTree(const SegmentTree& other)
{
    combineFcn = other.combineFcn;
    count = other.count;
    size = other.size;

    tree = new T[size];
    memcpy(tree, other.tree, size * sizeof(T));
}

template <typename T>
inline SegmentTree<T>& SegmentTree<T>::operator=(const SegmentTree& other)
{
    if (this != &other)
    {
        delete[] tree;

        combineFcn = other.combineFcn;
        count = other.count;
        size = other.size;

        tree = new T[size];
        memcpy(tree, other.tree, size * sizeof(T));
    }

    return *this;
}

template <typename T>
inline SegmentTree<T>::SegmentTree(SegmentTree&& other) noexcept
{
    tree = other.tree;
    combineFcn = other.combineFcn;
    count = other.count;
    size = other.size;

    other.tree = nullptr;
    other.combineFcn = nullptr;
    other.count = 0;
    other.size = 0;
}

template <typename T>
inline SegmentTree<T>& SegmentTree<T>::operator=(SegmentTree&& other) noexcept
{
    if (this != &other)
    {
        delete[] tree;

        tree = other.tree;
        combineFcn = other.combineFcn;
        count = other.count;
        size = other.size;

        other.tree = nullptr;
        other.combineFcn = nullptr;
        other.count = 0;
        other.size = 0;
    }

    return *this;
}

template <typename T>
inline T SegmentTree<T>::Query(size_t left, size_t right) const
{
    assert(left < right);

    left += size / 2;
    right += size / 2 - 1;

    T leftValue = GetNoneValue();
    T rightValue = GetNoneValue();

    while (left <= right)
    {
        if (left & 1)
        {
            leftValue = combineFcn(leftValue, tree[left]);
        }

        if (~right & 1)
        {
            rightValue = combineFcn(tree[right], rightValue);
        }

        left = GetParent(left + 1);
        right = GetParent(right - 1);
    }

    return combineFcn(leftValue, rightValue);
}

template <typename T>
inline void SegmentTree<T>::Update(size_t index, T newValue)
{
    size_t i = size / 2 + index;

    tree[i] = newValue;

    while (i > 1)
    {
        size_t parentIndex = GetParent(i);
        tree[parentIndex] = combineFcn(tree[GetLeft(parentIndex)], tree[GetRight(parentIndex)]);
        i = parentIndex;
    }
}

template <typename T>
inline void SegmentTree<T>::Insert(size_t index, T value)
{
    assert(0 <= index && index <= size / 2);

    if (count == size / 2)
    {
        T* old = tree;
        tree = new T[size * 2];
        tree[0] = old[0];

        memcpy(tree + size, old + size / 2, size / 2 * sizeof(T));

        for (size_t i = 0; i < size / 2; ++i)
        {
            tree[size + size / 2 + i] = old[0];
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
        tree[i] = combineFcn(tree[GetLeft(i)], tree[GetRight(i)]);
        --i;
    }
}

template <typename T>
inline void SegmentTree<T>::PushBack(T value)
{
    if (count == size / 2)
    {
        T* old = tree;
        tree = new T[size * 2];
        tree[0] = old[0];

        memcpy(tree + size, old + size / 2, size / 2 * sizeof(T));

        for (size_t i = 0; i < size / 2; ++i)
        {
            tree[size + size / 2 + i] = old[0];
        }

        delete[] old;

        size *= 2;

        size_t mid = size / 2;
        tree[mid + count] = value;
        ++count;

        size_t i = mid - 1;
        while (i > 0)
        {
            tree[i] = combineFcn(tree[GetLeft(i)], tree[GetRight(i)]);
            --i;
        }

        return;
    }

    Update(count, value);
    ++count;
}

template <typename T>
inline size_t SegmentTree<T>::GetCount() const
{
    return count;
}

template <typename T>
inline const T* SegmentTree<T>::GetTree() const
{
    return tree;
}

template <typename T>
inline size_t SegmentTree<T>::GetTreeSize() const
{
    return size;
}

template <typename T>
inline T SegmentTree<T>::GetNoneValue() const
{
    return tree[0];
}

template <typename T>
inline size_t SegmentTree<T>::GetLeft(size_t i) const
{
    return 2 * i;
}

template <typename T>
inline size_t SegmentTree<T>::GetRight(size_t i) const
{
    return 2 * i + 1;
}

template <typename T>
inline size_t SegmentTree<T>::GetParent(size_t i) const
{
    return i / 2;
}

template <typename T>
inline T SegmentTree<T>::operator[](size_t index) const
{
    return tree[size / 2 + index];
}