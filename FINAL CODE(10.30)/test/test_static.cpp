#include<iostream>
#include<cstdlib>
using namespace std;
#include"fish.h"

fish *player[MAX+1];

void print()
{
    for(int i=1;i<=5;i++) player[i]->getHp();
    cout<<endl;
    return ;
}

int main()
{
    for(int i=1;i<=5;i++)
    {
        player[i]=(fish *)malloc(sizeof(fish)*1);
        player[i]->init(i);
    }
    int f,num,x;
    print();
    cin>>f>>num>>x;
    while(f)
    {
        if(f==1)
        {
            player[num]->changeHp(x);
            print();
        }
        else if(f==2)
        {
            player[num]->printFromMe();
        }
        cin>>f>>num>>x;
    }
    return 0;
}
