#include<iostream>
#include<cstdlib>
using namespace std;

#include"player1.h"
#include"player2.h"

int main()
{
    fish *player[10];
    player1 p;
    player2 q;
    player[1]=&p;
    player[2]=&q;
    cout<<player[1]->getID()<<endl;
    cout<<player[2]->getID()<<endl;
    player[1]->print();player[2]->print();
    return 0;
}
