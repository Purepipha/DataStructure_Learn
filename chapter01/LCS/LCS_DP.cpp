#include <iostream>
#include <algorithm>
int LCS_DP(char A[], int m, char B[], int n);
int main()
{
    using namespace std;
    char cha[12] = "EDUCATIONAL";
    char chb[10] = "ADVANTAGE";
    int length = LCS_DP(cha, 10, chb, 8);
    cout << length << endl;
    return 0;
}
int LCS_DP(char A[], int m, char B[], int n)
{
    int tab[m+1][n+1] = {0};
    for (int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
            if (A[i-1] == B[j-1])
            {
                tab[i][j] = tab[i-1][j-1] + 1;
            }
            else
            {
                tab[i][j] = std::max<int>(tab[i][j-1],tab[i-1][j]);
            }
    }
    return tab[m][n];
}