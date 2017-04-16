
/*
Time Limit: 1 Sec
Memory Limit: 128 MB
Description
田鼠MIUMIU来到了一片农田，农田可以看成是一个M*N个方格的矩阵。每个方格里放有一定的粮食。
MIUMIU看到这里，兴奋不已，它要拿走多多的粮食，以备过冬。但MIUMIU要么往前走（向右） ，
要么往下走。 但它很聪明，一定会找到一条拿走最多粮食的路径。
MIUMIU目前在入口位置, 坐标为（1,1），出口位置在坐标（M,N）。 
请你编程，计算一下当MIUMIU走出农田时,最多能拿走多少粮食。
Input
第一行：  M  N  （ 1≤M ,N ≤50 ）
接下来有M行， 每行有N个整数,分别表示方格中的粮食数  0≤ Aij≤100 (i=1,..M, j=1,…N)
（所有的数之间有一个空格）
Output
一个整数，表示MIUMIU能拿走的最多粮食数。
Sample Input
4  3
5  3  7
5  3  2
5  5  5
6  2  5
Sample Output
30
HINT
Source
*/
/**********************************************************************
题解:这是一道典型的动态规划题，由于考前未学，而只是见过一道类似的三角形的题，然后就把这道题转换为了三角形的题。
花费时间有点长...用dp的话倒是代码写起来很简单，虽然空间复杂度达到了n2，但是在此题无所谓，dp本来就是空间换时间。
*********************************************************************/


#include <bits/stdc++.h>


using namespace std;
const int maxn=105;
int dp[maxn][maxn];
int a[maxn][maxn];
int Dp(int m,int n)
{
    for(int i=m-1;i>=0;i--)
    {
        for(int j=n-1;j>=0;j--)
        {
            dp[i][j]=max(dp[i+1][j],dp[i][j+1])+a[i][j];
        }
    }
    return dp[0][0];
}
int main()
{
    int m,n;
    cin>>m>>n;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
            {
                cin>>a[i][j];
            }
    }
    cout<<Dp(m,n)<<endl;
    return 0;
}
