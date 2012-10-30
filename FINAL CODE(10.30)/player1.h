#include "fish.h"

class player1:public fish{

    public:
    void init();
    void play();
    void revive(int &rx,int &ry);

    int getDis(int dx,int dy);
    int max(int a,int b);
    int min(int a,int b);
};

int player1::max(int a,int b)
{
    if(a<b) return b; else return a;
}

int player1::min(int a,int b)
{
    if(a<b) return a; else return b;
}

int player1::getDis(int dx,int dy)
{
    return abs(dx-getX())+abs(dy-getY());
}

void player1::init()
{
    for(int i=1;i<=1;i++) increaseHealth();
    for(int i=1;i<=3;i++) increaseSpeed();
    for(int i=1;i<=6;i++) increaseStrength();
}

void player1::play()
{

    int randx,randy;
    int x,y,newPoint=getPoint();
    if(newPoint>3)
    {
        int a1,a2,a3;
        a1=2;
        a2=1;
        a3=1;
        for(int i=1;i<=a3;i++) increaseHealth();
        for(int i=1;i<=a2;i++) increaseStrength();
        for(int i=1;i<=a1;i++) increaseSpeed();
    }
    randx=rand()%N+1;
    randy=rand()%M+1;
    int trytime=1;
    while(move(randx,randy)==false&&trytime<=1000000)
    {
        randx=rand()%N+1;
        randy=rand()%M+1;
        trytime++;
    }
    x=getX();y=getY();
    int randa[4]={-1,0,1,0},randb[4]={0,-1,0,1},randnum;
    randnum=rand()%4;
    trytime=1;
    while(attack(x+randa[randnum],y+randb[randnum])==false&&trytime<=100)
    {
        randnum=rand()%4;
        trytime++;
    }

}

void player1::revive(int &rx,int &ry)
{

    int randx,randy;
    randx=rand()%N+1;
    randy=rand()%M+1;
    rx=randx;ry=randy;

}




//可自行增加所需函数所需函数及变量，但需保证上面每个函数的完整与可调用

//不要使用全局变量！！
