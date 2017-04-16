/******************************************************************************
Time Limit: 2 Sec  Memory Limit: 128 MB

Description
某地区M座煤矿，其中第i号矿每年产量为Ai吨，现有火力发电厂一个，每年需用煤B吨，
每年运行的固定费用（包括折旧费，不包括煤的运费）为H元，每吨原煤从第i号矿运到
原有发电厂的运费为Ci0（i=1，2，…，M）。 
现规划新建一个发电厂，M座煤矿每年开采的原煤将全部供给这两座发电厂。现有N个备选
的厂址。若在第j号备选厂址建新厂，每年运行的固定费用为Hj元。每吨原煤从第i号矿运
到j号备选厂址的运费为Cij（i=1，2，…，M；j=1，2，…，N）。 
试问：应把新厂厂址选取在何处？M座煤矿开采的原煤应如何分配给两个发电厂，才能使
每年的总费用（发电厂运行费用与原煤运费之和）为最小。 

Input
第一行： T     表示以下有T组测试数据（1≤T ≤5）
对每组测试数据：
第1行：       M  B  H  N 
第2行：       A1  A2 …  Am               （0<=Ai<=500,   A1+A2+...+An>=B）
第3行：      H1  H2 …  Hn               （0<=Hi<=100）
第4行：       C10  C20 … Cm0              
第5行：       C11  C21 … Cm1 
                              …   … 
第n+4行：  C1n  C2n … Cmn              （0<=Cij<=50）
Output
每组测试数据，输出占一行，两个整数，即新厂址编号和总费用。如果有多个编号满足要求，输出最小的。

Sample Input
1
4  2  7  9 
3  1  10  3 
6  3  7  1  10  2  7  4  9 
1  2  4  3 
6  6  8  2 
4  10  8  4 
10  2  9  2 
7  6  6  2 
9  3  7  1 
2  1  6  9 
3  1  10  9 
4  2  1  8 
2  1  3  4

Sample Output
8 49

**********************************************************
题解：哈哈，这题写出来时间空间复杂度都超级低，嘿嘿（学长用时200+ms，我的0-4ms左右）。
大概思路呢就是先不管原发电厂要多少煤求出最小费用，然后在此期间，分别用了两个结构体数组
记忆运到原发电厂比新建发电厂贵的费用差和具有的煤的数量（rem0），以及新建发电厂比原发
电厂贵的费用差和具有的煤的数量（rem），然后看一下不管条件的最小费用后的给原发电厂的煤
是多了还是少了，如果多了，就从rem0里按每吨煤价值差小（sort）的在前面先算，一吨吨卸下来
（类似部分背包）。反之同理。
***********************************************************************/
#include <bits/stdc++.h>

using namespace std;
const int maxn=105;
struct Rem
{
    int value;
    int weight;
};
bool bmp(Rem a,Rem b)
{
    return (a.value<b.value);
}
int temp=0;
int a[maxn];int h[maxn];
int c0[maxn];
int c[maxn];
Rem rem[maxn];
Rem rem0[maxn];
int m,b,H,n;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
       temp=0;
       int res=1000000000+7;
       scanf("%d %d %d %d",&m,&b,&H,&n);
       for(int i=1;i<=m;i++)
       {
           scanf("%d",&a[i]);
       }
       for(int i=1;i<=n;i++)
       {
           scanf("%d",&h[i]);
       }
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&c0[i]);
        }
       int test=1;
       int u=1,r=1;
       int weight=0;
       int needweight=0;
       int num=0;
       for(;test<=n;test++)
       {
           temp=0;weight=0;needweight=0;u=1;r=1;
           for(int k=1;k<=m;k++)
           {
               scanf("%d",&c[k]);
               if(c[k]<c0[k])
               {
                   rem[u].value=c0[k]-c[k];
                   rem[u++].weight=a[k];
                   temp+=c[k]*a[k];
               }
               else
               {
                   rem0[r].value=c[k]-c0[k];
                   rem0[r++].weight=a[k];
                   temp+=c0[k]*a[k];
                   weight+=a[k];
               }
           }
           if(weight>=b)
           {
               sort(rem0+1,rem0+r,bmp);
               needweight=weight-b;
               for(int k=1;k<r;k++)
               {
                   if(rem0[k].weight>=needweight)
                   {
                        temp+=needweight*rem0[k].value;
                        needweight=0;
                        break;
                   }
                   else
                   {
                       needweight-=rem0[k].weight;
                        temp+=rem0[k].value*rem0[k].weight;
                   }
               }
               if(res>temp+H+h[test])
               {
                   res=temp+H+h[test];
                   num=test;
               }
           }
           else
           {
               sort(rem+1,rem+u,bmp);
                needweight=b-weight;
                for(int k=1;k<u;k++)
                {
                    if(rem[k].weight>=needweight)
                    {
                        needweight=0;
                        temp+=needweight*rem[k].value;
                        break;
                    }
                    else
                    {
                        needweight-=rem[k].weight;
                        temp+=rem[k].value*rem[k].weight;
                    }
                }
                if(res>temp+H+h[test])
               {
                   res=temp+H+h[test];
                   num=test;
               }
           }
       }
       printf("%d %d\n",num,res);
    }
    return 0;
}
