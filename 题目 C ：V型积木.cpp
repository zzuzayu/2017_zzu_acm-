/*************************************************************
Time Limit: 1 Sec  Memory Limit: 128 MB
Description
 Dr.Wu的宝宝1岁了，所以Dr.Wu准备买些积木给宝宝玩，促进孩子大脑的发育。由于宝宝太小，
所以他将高低不同的积木摆放的毫无规律（如图A）。然而Dr.Wu发现，如果从当前的积木中抽走
一部分（图B，C中虚线的即表示抽走的积木），剩下的积木能够呈现出“V”形，即积木的高度先
严格递减，然后严格递增。图B中，需要抽走三个积木，剩下的积木就可以呈现出“V”形，而图C
中仅需抽走一根积木。Dr.Wu需要你帮忙找出最少抽走多少积木，剩下的积木就能呈现出“V”型？

Input
第一行： T     表示以下有T组测试数据（1≤T ≤8）
对每组测试数据：
第一行:    N表示积木的个数。 （2<N<=100），
第二行是空格隔开的N个正整数，每个正整数Hi表示第i个积木的高度（0<Hi<=10000）。
输出中，仅一个数，即最少抽走的积木数。如果怎么抽走积木都无法呈现出“V”形，则输出“No Solution”。
Output
每组测试数据，输出占一行，仅一个数，即最少抽走的积木数。如果怎么抽走积木都无法呈现出“V”形，则输出“No Solution”。
Sample Input
2
6
50  30  40  10  20  60
6
5  4  3  1  2  6
Sample Output
1
0
*****************************************************************
题解：一开始想着bfs来着，然后gg。后来学习到最长上升子序列，然后就明白了什么...
遍历每一个积木，求得其左边序列的最长下降子序列以及右边最长上升子序列，和最大的就是抽掉的最少的。
***********************************************************************/
#include <bits/stdc++.h>

using namespace std;
int shumu;
int jm[1050];
int b[1050];
int weizhi;
int res;
int maxv=1000000+7;
int ss()
{
   int len=0;
   b[0]=0;
   for(int i=weizhi;i<shumu;i++)
   {
        if(jm[i]>b[len])
       {
           len++;
           b[len]=jm[i];
       }
       else
       {
           for(int j=1;j<=len;j++)
           {
               if(jm[i]<=b[j])
               {
                   b[j]=jm[i];
                   break;
               }
           }
       }
   }
   return len;
}
int xj()
{
    int len=0;
   b[0]=maxv;
   for(int i=0;i<weizhi+1;i++)
   {
       if(jm[i]<b[len])
       {
           len++;
           b[len]=jm[i];
       }
       else
       {
           for(int j=1;j<=len;j++)
           {
               if(jm[i]>=b[j])//大于等于都换，否则长度算出来有问题
               {
                   b[j]=jm[i];
                   break;
               }
           }
       }
   }
   return len;
}
int main()
{
    int T;
    cin>>T;
    for(int i=0;i<T;i++)
    {
        cin>>shumu;
        int yc=0;
        memset(jm,0,sizeof(jm));
        for(int j=0;j<shumu;j++)
        {
            cin>>jm[j];
        }
            res=shumu;
            for(int k=0;k<shumu;k++)
            {
                    weizhi=k;
                    int m,n;
                    m=ss();n=xj();
                    if(m==1||n==1)
                    {
                        continue;
                    }
                    int u=shumu-m-n+1;
                    if(res>u)res=u;              
            }
            if(res<shumu-2)
            {
                cout<<res<<endl;
            }
            else
            {
                cout<<"No Solution"<<endl;
            }
    }
    return 0;
}
