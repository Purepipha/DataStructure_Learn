#pragma once
// Vector source code
#define DEFAULT_CAPACITY 3  // 默认初始容量(实际应用中可设置为更大)
using Rank = int;
template <typename T>
class Vector
{
private:
    Rank _size;
    int _capacity;
    T * _elem;
protected:
    void copyFrom(T const * A, Rank lo, Rank hi);
public:
    Vector(int c = DEFAULT_CAPACITY) {_elem = new T[_capacity = c]; _size = 0;} // 默认
    Vector(T const * A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(Vector<T> const & V, Rank lo, Rank hi) // 向量区间复制
    { copyFrom(V._elem, lo, hi); }
    Vector(Vector<T> const & V) // 向量整体复制
    { copyFrom(V._elem, 0, V._size);}
    ~Vector() { delete []_elem; }// 释放内部空间
};

template <typename T>
void Vector<T>::copyFrom(T const * A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = DEFAULT_CAPACITY < 2*(hi - lo) ? 2*(hi - lo) : DEFAULT_CAPACITY];  // 分配空间
    for (_size = 0; lo < hi; _size++, lo++) // A[lo,hi)内的元素注意复制到
        _elem[_size] = A[lo];   // _elem[0,hi - lo)中
}   // O(hi - lo) = O(n)