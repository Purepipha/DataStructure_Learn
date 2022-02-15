// visit_example.cpp -- 实现加一，减一，加倍，求和操作
// 加一
#include "Vector.h"
template <typename T>   // 假设T可直接递增或已重载"++"
struct Increase     // 函数对象：通过重载()实现
{
    virtual void operator()(T & e) {e++;}
};
template <typename T>   // FIXME左值和右值不匹配
void increase(Vector<T> & V)
{
    V.traverse(Increase<T>());
}
// 减一
template <typename T>   // 假定T可直接递减或重载"--"
void Decrease(T & e)    // 模板函数指针
{
    e--;
}
template <typename T>
void decrease(Vector<T> & V)
{
    V.traverse(Decrease);
}
// 加倍
template <typename T>
class Redouble
{
private:
    int _n;  // 倍数
public:
    Redouble(int n = 2) : _n(n) {}
    virtual void operator()(T & e) { e *= _n; }
};
template <typename T>
void redouble(Vector<T> & V)
{
    V.traverse(Redouble<T>());
}
// // 求和
// template <typename T>
// class Sum
// {
// private:
//     T _sum_value;
// public:
//     Sum(T sum_value = 0) : _sum_value(sum_value){ }
//     void operator()(T & e) { _sum_value += e; }
//     T value() { return _sum_value; }
// };

// template <typename T>
// T sum(Vector<T> const & V)
// {
//     Sum<T> sum1;
//     V.traverse(sum1());
//     return sum1.value();
// }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     Vector<int> nums(9);
//     nums[0] = 1;
//     nums[1] = 2;
//     nums[2] = 3;
//     int i = 0;
//     increase(nums);
//     cout << nums[i] << endl;
//     return 0;
// }