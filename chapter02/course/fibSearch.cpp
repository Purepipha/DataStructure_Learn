// fibSearch.cpp -- 斐波那契查找
// versionA
#include "Vector/Vector.h"
template <typename T>   // 在有序向量区间[lo, hi)查找元素e
static Rank fibSearch(T * S, T const & e, Rank lo, Rank hi)
{
    Fib fib(hi - lo);
    while (lo < hi)
    {
        while (hi - lo < fib.get()) fib.prev();
        Rank mi = (lo + hi) >> 1;   // 轴点居中(区间宽度折半，等效于其数值右移一位)
        if (e < S[mi]) hi = mi;     // 深入前半段[lo,mi)
        else if (S[mi] < e) lo = mi + 1;    // 深入后半段(mi,hi)
        else return mi;
    }
    return -1;
}