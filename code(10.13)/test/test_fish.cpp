#include<iostream>
#include"fish.h"
using namespace std;
void print(fish *p)
{
    cout<<"id: "<<p->getID()<<endl;
    cout<<"Point: "<<p->getPoint()<<" (HP:"<<p->getHP()<<" \t maxHP:"<<p->getMaxHP()<<"\tSpeed:"<<p->getSp()<<"\tAttack:"<<p->getAtt()<<")"<<endl;
    cout<<"x: "<<p->getX()<<"\t";
    cout<<"y: "<<p->getY()<<endl;
}
int main()
{
    fish mkch;
    print(&mkch);
    mkch.increaseHealth();
    print(&mkch);
    return 0;
}
