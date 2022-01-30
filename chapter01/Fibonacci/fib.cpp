#include <iostream>
long long fib_R(int n);
long long fib_M(int n, long long M[]);         // 记忆递归
long long fib_D(int n);         // 动态规划
int main()
{
    using namespace std;
    int n;
    cout << "Enter a integer: ";
    cin >> n;
    long long * M = new long long[n + 1];
    for (int i = 0; i < n; i++)
        cout << i << ": " << fib_R(i) << "\t"
             << fib_M(i, M) << "\t" << fib_D(i)<< endl;
    return 0;
}
long long fib_R(int n)
{
    return n < 2 ? n : fib_R(n - 1) + fib_R(n - 2);
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

long long fib_D(int n)
{
    long long g = 0;
    long long f = 1;
    while (n--)
    {
        g = g + f;
        f = g - f;
    }
    return g;
}