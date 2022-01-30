// fib_M.cpp -- 动态规划
#include <iostream>
long long fib_M(int n, long long M[]);

int main()
{
    using namespace std;
    int n;
    cout << "Enter a integer: ";
    cin >> n;
    long long *M = new long long[n + 1];
    for (int i = 0; i < n; i++)
        cout << i << ": " << fib_M(i, M) << endl;
    return 0;
}

long long fib_M(int n, long long M[])
{
    if (n < 2)
        return M[n] = n;
    if (M[n - 1] > 0 && M[n - 2] > 0) // 前两项存在
        M[n] = M[n - 1] + M[n - 2];
    else // 前两项不存在
        M[n] = fib_M(n - 1, M) + fib_M(n - 2, M);
    return M[n];
}