#include "../List/List.h"
template <typename T>
class Stack : public List<T>{
public:
    void push(T const& e) { insertAsFirst(e); }//入栈
    T pop() { return remove(first()); }//出栈
    T & top() { return (*this)[0]; } //取顶
};