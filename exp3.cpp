#include<iostream>
#include<stdio.h>
#include<list>
#include<string>
using namespace std;

int pg_sz;//页表大小

//检查页表是否已满
bool page_is_full(list<int> &l)
{
    if(l.size()==pg_sz)
        return true;
    return false;
}

//判断n是否已在页表当中,若是，返回指向该元素的iterator
list<int>::iterator is_in_page(list<int> &l,int n)
{
    list<int>::iterator res=l.end();
    for(list<int>::iterator i=l.begin();i!=l.end();i++)
    {
        if(*i==n)
            return i;
    }
    return res;
}

//打印当前页表情况
void print_page(list<int> &page)
{
    cout<<"PAGE:";
    for(list<int>::iterator i=page.begin();i!=page.end();i++)
        cout<<*i<<" ";
    cout<<endl;
}

int main()
{
    int num=30;
    int pageno[num]={2,3,1,5,3,8,9,8,7,5,2,4,1,2,2,
                    3,5,9,1,8,9,5,2,9,2,5,1,8,6,8};//地址访问序列（页面号）
    cout<<"PAGE NUMBER FOR EACH ADDRESS IS:"<<endl;
    int t=0;
    for(int i=0;i<num;i++)
    {
        if(t==4)
        {
            cout<<endl;
            t=0;
        }
        printf("pageno[%d]=%d\t",i,pageno[i]);
        t++;
    }

    cout<<endl<<endl<<"PLEASE ENTER THE SCHEDULING ALOGORITHM(OPT OR LRU OR FIFO):";
    string input;
    cin>>input;

    if(input=="LRU")
    {
        cout<<"PLEASE ENTER THE PAGE SIZE(Ex.4):";
        cin>>pg_sz;//页表大小，页表满了就执行置换算法
        list<int> page;//用list实现页表
        int fail_num=0;//失效次数
        cout<<endl;
        //遍历pageno[]
        for(int i=0;i<num;i++)
        {
            print_page(page);
            list<int>::iterator it=is_in_page(page,pageno[i]);//检查新的元素是否在页表中
            if((it==page.end())&&!page_is_full(page))//页表没有满且新元素不在页表中,将新的一项加入页表末尾
            {
                page.push_back(pageno[i]);
                continue;
            }
            else if((it==page.end())&&page_is_full(page))//新的元素不在页表中，但页表已满，将第一项pop出，将新的一项push入
            {
                fail_num++;
                page.pop_front();
                page.push_back(pageno[i]);
                    continue;
            }
            else//新的元素在页表中，删除原来的元素，将新的元素push入
            {
                page.erase(it);
                page.push_back(pageno[i]);
            }
        }
        cout<<endl<<"HIT RATE:"<<1-(double)fail_num/num<<endl;
    }
    else if(input=="OPT")
    {
        cout<<"PLEASE ENTER THE PAGE SIZE(Ex.4):";
        cin>>pg_sz;//页表大小，页表满了就执行置换算法
        list<int> page;//用list实现页表
        int fail_num=0;//失效次数
        cout<<endl;
        //遍历pageno[]
        for(int i=0;i<num;i++)
        {
            print_page(page);
            list<int>::iterator it=is_in_page(page,pageno[i]);//检查新的元素是否在页表中
            if((it==page.end())&&!page_is_full(page))//如果页表没有满且新元素不在页表中，直接加新元素即可
            {
                page.push_back(pageno[i]);
                continue;
            }
            else if((it==page.end())&&page_is_full(page))//如果新的元素不在页表中，但页表已满
            {
                int earliest_appear_index[pg_sz]={num};//记录页表中每一项元素下一次最早出现的下标位置，初始化为最大值，即不会出现
                for(int k=0;k<pg_sz;k++)
                    earliest_appear_index[k]=num;
                int index=0;//用于遍历earliest_appear_index[]
                for(list<int>::iterator ii=page.begin();ii!=page.end();ii++)//遍历页表中每一项元素
                {
                    for(int t=i;t<num;t++)//从当前位置i开始往后遍历pageno[]，寻找最早出现该数值的下标位置
                    {
                        if(pageno[t]==*ii)
                        {
                            earliest_appear_index[index]=t;
                            break;
                        }
                    }
                    index++;
                }
                int max_index=0;int max=0;
                //寻找earliest_appear_index[]中最大的那一项的下标，就是要淘汰的那一项的下标
                for(int t=0;t<pg_sz;t++)
                {
                    if(earliest_appear_index[t]>max)
                    {
                        max_index=t;
                        max=earliest_appear_index[t];
                    }
                }
                //将iterator也变成对应max_index的下标
                list<int>::iterator target=page.begin();
                for(int t=0;t<max_index;t++)
                    target++;

                fail_num++;
                page.erase(target);//在页表中删除该项元素
                page.push_back(pageno[i]);//将新的元素放入页表
                continue;
            }
            else//新的元素在页表中，什么也不做
            {
                continue;
            }
        }
        cout<<endl<<"HIT RATE:"<<1-(double)fail_num/num<<endl;
    }
    else if(input=="FIFO")
    {
        cout<<"PLEASE ENTER THE PAGE SIZE(Ex.4):";
        cin>>pg_sz;//页表大小，页表满了就执行置换算法
        list<int> page;//用list实现页表
        int fail_num=0;//失效次数
        cout<<endl;
        //遍历pageno[]
        for(int i=0;i<num;i++)
        {
            print_page(page);
            list<int>::iterator it=is_in_page(page,pageno[i]);//检查新的元素是否在页表中
            if((it==page.end())&&!page_is_full(page))//如果页表没有满且新元素不在页表中，直接加新元素即可
            {
                page.push_back(pageno[i]);
                continue;
            }
            else if((it==page.end())&&page_is_full(page))//如果新的元素不在页表中，但页表已满,将第一项pop出，将新的一项push入
            {
                fail_num++;
                page.pop_front();
                page.push_back(pageno[i]);
                    continue;
            }
            else//新的元素在页表中，什么也不做
            {
                continue;
            }
        }
        cout<<endl<<"HIT RATE:"<<1-(double)fail_num/num<<endl;
    }
    return 0;
}
