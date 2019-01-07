#include<iostream>
#include<stdio.h>
#include<list>
#include<string>
using namespace std;

int pg_sz;//ҳ���С

//���ҳ���Ƿ�����
bool page_is_full(list<int> &l)
{
    if(l.size()==pg_sz)
        return true;
    return false;
}

//�ж�n�Ƿ�����ҳ����,���ǣ�����ָ���Ԫ�ص�iterator
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

//��ӡ��ǰҳ�����
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
                    3,5,9,1,8,9,5,2,9,2,5,1,8,6,8};//��ַ�������У�ҳ��ţ�
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
        cin>>pg_sz;//ҳ���С��ҳ�����˾�ִ���û��㷨
        list<int> page;//��listʵ��ҳ��
        int fail_num=0;//ʧЧ����
        cout<<endl;
        //����pageno[]
        for(int i=0;i<num;i++)
        {
            print_page(page);
            list<int>::iterator it=is_in_page(page,pageno[i]);//����µ�Ԫ���Ƿ���ҳ����
            if((it==page.end())&&!page_is_full(page))//ҳ��û��������Ԫ�ز���ҳ����,���µ�һ�����ҳ��ĩβ
            {
                page.push_back(pageno[i]);
                continue;
            }
            else if((it==page.end())&&page_is_full(page))//�µ�Ԫ�ز���ҳ���У���ҳ������������һ��pop�������µ�һ��push��
            {
                fail_num++;
                page.pop_front();
                page.push_back(pageno[i]);
                    continue;
            }
            else//�µ�Ԫ����ҳ���У�ɾ��ԭ����Ԫ�أ����µ�Ԫ��push��
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
        cin>>pg_sz;//ҳ���С��ҳ�����˾�ִ���û��㷨
        list<int> page;//��listʵ��ҳ��
        int fail_num=0;//ʧЧ����
        cout<<endl;
        //����pageno[]
        for(int i=0;i<num;i++)
        {
            print_page(page);
            list<int>::iterator it=is_in_page(page,pageno[i]);//����µ�Ԫ���Ƿ���ҳ����
            if((it==page.end())&&!page_is_full(page))//���ҳ��û��������Ԫ�ز���ҳ���У�ֱ�Ӽ���Ԫ�ؼ���
            {
                page.push_back(pageno[i]);
                continue;
            }
            else if((it==page.end())&&page_is_full(page))//����µ�Ԫ�ز���ҳ���У���ҳ������
            {
                int earliest_appear_index[pg_sz]={num};//��¼ҳ����ÿһ��Ԫ����һ��������ֵ��±�λ�ã���ʼ��Ϊ���ֵ�����������
                for(int k=0;k<pg_sz;k++)
                    earliest_appear_index[k]=num;
                int index=0;//���ڱ���earliest_appear_index[]
                for(list<int>::iterator ii=page.begin();ii!=page.end();ii++)//����ҳ����ÿһ��Ԫ��
                {
                    for(int t=i;t<num;t++)//�ӵ�ǰλ��i��ʼ�������pageno[]��Ѱ��������ָ���ֵ���±�λ��
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
                //Ѱ��earliest_appear_index[]��������һ����±꣬����Ҫ��̭����һ����±�
                for(int t=0;t<pg_sz;t++)
                {
                    if(earliest_appear_index[t]>max)
                    {
                        max_index=t;
                        max=earliest_appear_index[t];
                    }
                }
                //��iteratorҲ��ɶ�Ӧmax_index���±�
                list<int>::iterator target=page.begin();
                for(int t=0;t<max_index;t++)
                    target++;

                fail_num++;
                page.erase(target);//��ҳ����ɾ������Ԫ��
                page.push_back(pageno[i]);//���µ�Ԫ�ط���ҳ��
                continue;
            }
            else//�µ�Ԫ����ҳ���У�ʲôҲ����
            {
                continue;
            }
        }
        cout<<endl<<"HIT RATE:"<<1-(double)fail_num/num<<endl;
    }
    else if(input=="FIFO")
    {
        cout<<"PLEASE ENTER THE PAGE SIZE(Ex.4):";
        cin>>pg_sz;//ҳ���С��ҳ�����˾�ִ���û��㷨
        list<int> page;//��listʵ��ҳ��
        int fail_num=0;//ʧЧ����
        cout<<endl;
        //����pageno[]
        for(int i=0;i<num;i++)
        {
            print_page(page);
            list<int>::iterator it=is_in_page(page,pageno[i]);//����µ�Ԫ���Ƿ���ҳ����
            if((it==page.end())&&!page_is_full(page))//���ҳ��û��������Ԫ�ز���ҳ���У�ֱ�Ӽ���Ԫ�ؼ���
            {
                page.push_back(pageno[i]);
                continue;
            }
            else if((it==page.end())&&page_is_full(page))//����µ�Ԫ�ز���ҳ���У���ҳ������,����һ��pop�������µ�һ��push��
            {
                fail_num++;
                page.pop_front();
                page.push_back(pageno[i]);
                    continue;
            }
            else//�µ�Ԫ����ҳ���У�ʲôҲ����
            {
                continue;
            }
        }
        cout<<endl<<"HIT RATE:"<<1-(double)fail_num/num<<endl;
    }
    return 0;
}
