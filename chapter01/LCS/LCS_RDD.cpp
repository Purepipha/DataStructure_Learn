// LSC_RDD.cpp -- 递归 + 减而治之 + 分而治之
#include <iostream>
#include <algorithm>
// 求A[0,m]与B[0,n]的最大公共子序列长度
void LCS_RDD(char A[],int m, char B[], int n, int &length);  // [0,m]和[0,n]
// int LCS_RDD(char A[], int m, char B[], int n);

int main()
{
    using namespace std;
    char cha[12] = "EDUCATIONAL";
    char chb[10] = "ADVANTAGE";
    int length = 0;
    LCS_RDD(cha, 10, chb, 8, length);
    // LCS_RDD(cha, 11, chb, 9, length);
    cout << length << endl;
    return 0;
}

void LCS_RDD(char A[],int m, char B[], int n, int &length)
{
    if (m < 0 || n < 0)
        return;
    if (A[m] == B[n])
    {
        LCS_RDD(A, m - 1, B, n - 1, length);
        length++;
    }
    int lengthA = 0;
    int lengthB = 0;
    if (A[m] != B[n])
    {
        LCS_RDD(A, m - 1, B, n, lengthA);
        LCS_RDD(A, m, B, n - 1, lengthB);
    }
    lengthA > lengthB ? length += lengthA : length += lengthB;
}

// int LCS_RDD(char A[], int m, char B[], int n)
// {
//     if (m < 0 || n < 0)
//         return 0;
//     if (A[m] == B[n])
//         return LCS_RDD(A, m - 1, B, n - 1) + 1;
//     else
//         return std::max<int>(LCS_RDD(A, m - 1, B , n),LCS_RDD(A, m, B, n-1));
// }