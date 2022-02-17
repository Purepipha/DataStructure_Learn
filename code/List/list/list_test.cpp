#include "list_test.h"
#include <ctime>
#include <cstdlib>
const int N = 20;
template <typename T> struct Show{
    virtual void operator()(T const& e) { cout << e << " "; }
};
template <typename T> void show(List<T> & L)
{ L.traverse(Show<T>()); cout << endl; }
int main(){
    List<int> L;//创建空列表
    for (int i = 0; i < N; i++)//给空列表添加元素
        L.insertAsFirst(rand() % N);
    int r = 0;//统计数目
    clock_t start, end;//统计程序开始结束时间
    for (Posi(int) p = L.first(); r < N; r++){//从头到尾依次遍历，输出
        cout << p->data;
        cout << " ";
        p = p->succ;
    }
    cout << endl;
    start = clock();
    L.sort(L.first(), N);//使用选择排序
    end = clock();
    cout << "Sort time: " << double(end - start)/CLOCKS_PER_SEC << endl;
    r = 0;
    for (Posi(int) p = L.first(); r < N; r++){
        cout << p->data;
        cout << " ";
        p = p->succ;
    }
    cout << endl;
    return 0;
}