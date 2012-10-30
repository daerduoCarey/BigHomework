#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
using namespace std;
using namespace std;

#include <cmath>
#include <cstring>
#include <windows.h>
int envAsk(int dx,int dy);
bool canGet(int dx,int dy,int cx,int cy,int s);
void delFood(int dx,int dy);
bool haveAttacked(int dID);
bool haveMoved(int dID);
void envMove(int dID,int dx,int dy);
void envAttack(int dID,int dx,int dy,int type);
void deadQueue(int dID);
void printGraph();

const int TOTAL_PLAYER=10;
const int ROUND=500;
const int TIME=10;

#include"player1.h"
#include"mkch1.h"

int r;
int ha[MAX_PLAYER+1]={0},hm[MAX_PLAYER+1]={0};
int dead[2][MAX_PLAYER+1],dt[2]={0},dw[2]={0};
int actlist[MAX_PLAYER+1];

int f[N+1][M+1]={EMPTY};
fish *pl[MAX_PLAYER+1];

void printData(int did)
{
    cout<<did<<": "<<endl;
    cout<<"   Hp    : "<<pl[did]->getHP()<<endl;
    cout<<"   MaxHp : "<<pl[did]->getMaxHP()<<endl;
    cout<<"   Speed : "<<pl[did]->getSp()<<endl;
    cout<<"   Attack: "<<pl[did]->getAtt()<<endl;
    cout<<"   Exp   : "<<pl[did]->getExp()<<endl;
    cout<<"   LV    : "<<pl[did]->getLevel()<<endl;
    cout<<"   Bonus : "<<pl[did]->getBonusExp()<<endl;
    cout<<"   Point : "<<pl[did]->getGrade()<<endl;
    cout<<endl;
}

int envAsk(int dx,int dy)
{
    return f[dx][dy];
}
bool canGet(int dx,int dy,int cx,int cy,int s)
{
    if(abs(dx-cx)+abs(dy-cy)<=s) return true;
    else return false;
}
void delFood(int dx,int dy)
{
    if(f[dx][dy]==FOOD)
        f[dx][dy]=EMPTY;
}
bool haveAttacked(int dID)
{
    if(ha[dID]) return true;
    else return false;
}
bool haveMoved(int dID)
{
    if(hm[dID]) return true;
    else return false;
}
void clean()
{
    Sleep(TIME);
    system( "cls ");
}
void envAttack(int dID,int dx,int dy,int type)
{
    ha[dID]=1;
    //printGraph();
    //cout<<dID<<" has attacked at ("<<dx<<","<<dy<<")"<<endl;

    //if(type) getchar();

}
void envMove(int dID,int dx,int dy)
{

    f[dx][dy]=EMPTY;
    hm[dID]=1;
    f[pl[dID]->getX()][pl[dID]->getY()]=dID;
    //printGraph();
    //cout<<dID<<" has moved to ("<<pl[dID]->getX()<<","<<pl[dID]->getY()<<")"<<endl;

}
void deadQueue(int dID)
{
    int ff=r%2;
    if(dt[ff])
    {
        dw[ff]++;
        dead[ff][dw[ff]]=dID;
    }
    else
    {
        dt[ff]=dw[ff]=1;
        dead[ff][1]=dID;
    }
    f[pl[dID]->getX()][pl[dID]->getY()]=EMPTY;
}
void revives(int ff)
{
    int dl=dt[ff];
    int rX,rY;
    if(dl)
    {
        while(dl<=dw[ff])
        {
            hm[dead[ff][dl]]=ha[dead[ff][dl]]=1;
            pl[dead[ff][dl]]->revive(rX,rY);
            hm[dead[ff][dl]]=ha[dead[ff][dl]]=0;

            if(f[rX][rY]==EMPTY) f[rX][rY]=dead[ff][dl];
            else
            {
                rX=rand()%N+1;rY=rand()%M+1;
                while(f[rX][rY]!=EMPTY)
                {
                    rX=rand()%N+1;rY=rand()%M+1;
                }
                f[rX][rY]=dead[ff][dl];
            }

            pl[dead[ff][dl]]->changeX(rX);
            pl[dead[ff][dl]]->changeY(rY);


            //hp变化

            pl[dead[ff][dl]]->changeHp(max(1,pl[dead[ff][dl]]->getMaxHP()*0.1));

            //printGraph();
            //cout<<dead[ff][dl]<<" revived at ("<<rX<<","<<rY<<")"<<endl;
            //getchar();

            dl++;
            dead[ff][dl-1]=0;
        }
    }
    dt[ff]=dw[ff]=0;
}
void actions()
{

    int al=1;
    if(al)
    {

        while(al<=TOTAL_PLAYER&&pl[actlist[al]]->getHP()>=1)
        {

            pl[actlist[al]]->play();
            al++;
            actlist[al-1]=0;
        }
    }

}
bool compare(int i,int j)
{
    int x1,x2,x3,x4,y1,y2,y3,y4;
    x1=pl[i]->getSp();x2=pl[i]->getHP();x3=pl[i]->getMaxHP();x4=pl[i]->getGrade();
    y1=pl[j]->getSp();y2=pl[j]->getHP();y3=pl[j]->getMaxHP();y4=pl[j]->getGrade();
    if(x2<1&&y2<1) return false;
    if(x2<1) return true;
    if(y2<1) return false;
    if(x1<y1||(x1==y1&&x2<y2)||(x1==y1&&x2==y2&&x3<y3)||(x1==y1&&x2==y2&&x3==y3&&x4<y4))
        return true;
    else
        return false;
}
void swap(int i,int j)
{
    int tmp;
    tmp=actlist[i];actlist[i]=actlist[j];actlist[j]=tmp;
}
void round(int cr)
{
    /*if(cr == ROUND)
    {
        for(int i=1;i<=TOTAL_PLAYER;i++)
            printData(i);
        getchar();
    }*/
    for(int i=1;i<=MAX_PLAYER;i++) {ha[i]=0;hm[i]=0;}

    revives(cr%2);

    //给出actlish[]
    for(int i=1;i<=TOTAL_PLAYER;i++) actlist[i]=i;
    for(int i=1;i<TOTAL_PLAYER;i++)
        for(int j=i+1;j<=TOTAL_PLAYER;j++)
            if(compare(i,j)) swap(i,j);

    actions();
}
void refreshFood()
{
    //刷新水藻
    //cout<<"Refresh the FOODs!!!"<<endl;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(f[i][j]==FOOD) f[i][j]=EMPTY;
    int sum=1,randx,randy;
    while(sum<=MAX_FOOD)
    {
        randx=rand()%N+1;
        randy=rand()%M+1;
        while(f[randx][randy]!=EMPTY)
        {
            randx=rand()%N+1;
            randy=rand()%M+1;
        }
        f[randx][randy]=FOOD;
        sum++;
    }
}

void printGraph()
{
    clean();
    //cout<<"+";for(int i=1;i<=M;i++) cout<<"-";cout<<"+"<<endl;
    for(int i=1;i<=N;i++)
    {   cout<<"|";
        for(int j=1;j<=M;j++)
            if(f[i][j]>0) printf("%c",f[i][j]+'a'-1);
            else if(f[i][j]==FOOD) cout<<".";
            else cout<<" ";
        cout<<"|"<<endl;
    }
    cout<<"+";for(int i=1;i<=M;i++) cout<<"-";cout<<"+";
    cout<<endl;
}

int main()
{
    srand((unsigned)time(NULL));

    for(int i=1;i<=TOTAL_PLAYER-5;i++)
    {
        pl[i]=new player1();
        pl[i]->giveID(i);
        f[pl[i]->getX()][pl[i]->getY()]=pl[i]->getID();
        pl[i]->init();
    }

    for(int i=6;i<=TOTAL_PLAYER;i++)
    {
        pl[i]=new mkch1();
        pl[i]->giveID(i);
        f[pl[i]->getX()][pl[i]->getY()]=pl[i]->getID();
        pl[i]->init();
    }

    //printGraph();
    //for(int i=1;i<=TOTAL_PLAYER;i++)
    //   cout<<i<<" is born at ("<<pl[i]->getX()<<","<<pl[i]->getY()<<")"<<endl;

    for(r=1;r<=ROUND;r++)
    {
        if(r%5==1) {refreshFood();/*printGraph();*/}
        cout<<r<<"-";
        round(r);
    }

    for(int i=1;i<=TOTAL_PLAYER;i++)
            printData(i);

    cout<<"\n\nFollowing is the rank:\n";

    int ranka[MAX_PLAYER+1]={0};
    for(int i=1;i<=TOTAL_PLAYER;i++) ranka[i]=i;
    for(int i=1;i<TOTAL_PLAYER;i++)
        for(int j=i+1;j<=TOTAL_PLAYER;j++)
            if(pl[ranka[i]]->getGrade()>pl[ranka[j]]->getGrade())
                {
                    int tmp=ranka[i];ranka[i]=ranka[j];ranka[j]=tmp;
                }
    for(int i=TOTAL_PLAYER;i>=1;i--)
    {
        printf("%4d:  %d\n",TOTAL_PLAYER+1-i,ranka[i]);
    }
    system("pause");
    return 0;
}
