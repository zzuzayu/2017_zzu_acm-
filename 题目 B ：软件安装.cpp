/************************************
Time Limit: 1 Sec  Memory Limit: 128 MB
Description
Dr.Kong有一个容量为N MB (1 <= N <= 50,000)的存储磁盘,不妨设地址空间编号为1到N。现在他需要安装一些软件， 
每个软件要占用一定大小的容量且必须装在连续的地址空间里。比如发出指令“1 100”，表示需要申请100 MB的存储空间。
如果有多个满足条件的连续空间，则选择起始地址最小的一个进行分配。若没有足够的连续空间，将不安装此软件（即使有
足够多的不连续存储空间）。系统可以不定时的卸载软件，释放磁盘的空间。比如：发出“2 23 100”，表示释放起始地址
为23的连续100MB大小的容量。释放时，不需要考虑这些空间里是否安装过软件。
请你编写一个程序，帮助Dr.Kong处理M (1 <= M <= 50,000)个按指令次序请求的任务。第一个请求到来前，磁盘是空的。
Input
第1行:     N  M
第2…M+1行: 每行描述了一个请求，如果是申请，则用2个数字 1 Mi 表示； 如果是释放，则用3个数字 2 Di Mi表示。数据之间用一个空格隔开. （1<=Di ,Mi<= 50,000）
Output
对于每个申请指令，输出占1行。如果请求能被满足，输出满足条件的最小起始地址；如果请求无法被满足，输出0。对于每个释放指令，不产生输出。

Sample Input
10  6
1  3
1  3
1  3
1  3
2  5  5
1  6

Sample Output
1
4
7
0
5

************************************************
题解：学长说用线段树做，然而本渣渣并不会线段树那么高级的玩意啊，这可咋整捏？
然后后面发现set有个equal_range函数炒鸡好用呀，如果用这函数然后去更新区间貌
似时间复杂度也是nlogn呀。但是还有个小小滴问题，更新区间时间复杂度是降下来了，
查找咋整捏？想了个歪法子，就是用多个set分别把长度大于p[i]的空闲区间存起来。
然后到时候可以按照要求的区间长度来找入口查找，就没必要一个个全遍历了。
***************************************/
#include <bits/stdc++.h>

using namespace std;
const int maxn=50005;
set<int> mem;//标记所有起始空闲地址
set<int>::iterator it;
int kx[maxn+1];//所有空闲起始地址的空闲空间
set<int> kxcs[20];  //分别存储所有长度大于等于p[i]的起始地址
const int p[20]={1,2,3,4,5,6,7,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};//分组
pair<set<int>::const_iterator,set<int>::const_iterator> pr;
void insertit(int insertcs,int len);
void deleteit(int deletecs);
int lg2(int len)
{
    int getit;
    int i=0;
    for(;p[i]<=len&&i<20;i++);
    getit=i-1;
    return getit;
}
int searchit(int len)//查找
{
    int addr=lg2(len);//选择入口
    set<int>::iterator itit;
    for(itit=kxcs[addr].begin();itit!=kxcs[addr].end();itit++)//从入口开始遍历
    {
        int getcs=*itit;
        if(kx[getcs]>=len)
        {
            int afterlen=kx[getcs]-len;
            int aftercs=getcs+len;
            kx[aftercs]=afterlen;
            deleteit(getcs);
            if(afterlen!=0)
            {
                insertit(aftercs,afterlen);
            }
            return getcs;
        }
    }
    return 0;
}
void insertit(int insertcs,int len)//添加 起始地址与长度
{
    int addr=lg2(len);
    mem.insert(insertcs);//更新总数据
    kx[insertcs]=len;
    for(int i=0;i<=addr;i++)//更新分组数据
    {
        kxcs[i].insert(insertcs);
    }
  /*  for(set<int>::iterator itit=mem.begin();itit!=mem.end();itit++)
    {
        cout<<*itit<<endl;
    }*/
}
void deleteit(int deletecs)
{
    int addr=lg2(kx[deletecs]);
    kx[deletecs]=0;
    mem.erase(deletecs);
    for(int i=0;i<=addr;i++)
    {
    kxcs[i].erase(deletecs);
    }
}
int m,n,sta,di,mi;
int main()
{
    memset(kx,0,sizeof(kx));
    kx[maxn]=maxn;
    scanf("%d %d",&n,&m);
    mem.insert(0);
    mem.insert(maxn);//用于保护，以免出现段错误
    insertit(1,n);
    while(m--)
    {
        scanf("%d",&sta);
        if(sta==1)
        {
            scanf("%d",&mi);
            printf("%d\n",searchit(mi));
        }
        else
        {
            scanf("%d %d",&di,&mi);
            int flag=false;
            int si=di;
            if(si>n)continue;
            int ei=di+mi-1;
            if(ei>n)ei=n;//限制边界
            pr=mem.equal_range(di);//该函数可以从容器中返回第一个大于等于或大于指定数的数
            it=pr.first;
            it--;//往后一个即为最后一个比它小的
            if(*it+kx[*it]-1>=ei&&*it+kx[*it]-1>=si-1)continue;//新区间直接被原先区间覆盖，那该次释放无意义 
            if(*it+kx[*it]-1>=si-1)//如果最后一个比它小的结束地址大于本次释放区间起始地址，则这两个区间将连起来，初始地址将是*it
            {
                si=*it;
                deleteit(*(it++));//先删除该区间，下面重建，因为还不知道区间长度
            }
            else it++;
            while(true)
            {
                if(*it+kx[*it]-1>ei)//遍历新的释放空间会重合的所有区间，当某区间结束地址比新区间的结束地址大时遍历结束
                {
                    if(*it<=ei+1)//该区间与新区间相连接起来
                    {
                        ei=*it+kx[*it]-1;
                        deleteit(*it);//连接起来则全算为新区间的，把该区间删除
                    }
                    insertit(si,ei-si+1);//把新区间加进去
                    break;
                }
                if(*it<=ei)
                {
                    deleteit(*(it++));//区间起始地址小于等于新区间结束地址都是要和新区间重合的
                }
                else it++;
            }
        }
    }
    return 0;
}
