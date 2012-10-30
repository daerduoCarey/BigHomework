#include<iostream>
using namespace std;
#include"player1.h"
const int ROUND=100;
int min(int x,int y)
{
    if(x<y) return x;
    else return y;
}
int max(int x,int y)
{
    if(x<y) return y;
    else return x;
}
class env
{
    private:
        int total=0;
        void *player[MAX_PLAYER+1];
        int f[N+1][M+1]={0};
        int hp[MAX_PLAYER+1]={0},x[MAX_PLAYER+1]={0},y[MAX_PLAYER+1]={0};
        int level[MAX_PLAYER+1]={0},maxhp[MAX_PLAYER+1]={0},att[MAX_PLAYER+1]={0};
        int exp[MAX_PLAYER+1]={0},sp[MAX_PLAYER+1]={0},point[MAX_PLAYER+1]={0};
    public:
        void init();
        void round();
        void plant();
        void outputResult();
        int askWhat(int dx,dy) {return field[dx][dy];}
        int askHP(int dID) {return HP[dID];}
        void attack(int dID,int dx,int dy);
        void move(int dID,int dx,int dy);
        int getHP(int dID) {return hp[dID];}
        int getExp(int dID) {return exp[dID];}
}
void env::attack(int dID,int dx,int dy)
{
    int attackID=f[dx][dy];
    if(attackID==-1&&att[dID]>=1)
    {
        exp[dID]++;
        hp[dID]=min(maxhp[dID],hp[dID]+max(2,maxhp[dID]/10));
    }
    else
    {
        hp[attackID]-=att[dID];
        exp[dID]+=max(1,level[attackID]/2);
    }
}
void env::move(int dID,int dx,int dy)
{
    x[dID]=dx;y[dID]=dy;
}
void env::outputResult()
{
    //输出最终结果
}
void env::init()
{
    //初始化每个player，调用XXX.init(),调用XXX.setID(int dID);
    total=2;
    player1 mkch1;
    player[1]=&mkch1;
    player[1]->init();
    player[1]->setID(1);
    player1 mkch2;
    player[1]=&mkch2;
    player[1]->init();
    player[1]->setID(2);
}
void round()
{
    int pID[MAX_PLAYER+1]={0},pSpeed[MAX_PLAYER+1]={0},pHp[MAX_PLAYER+1]={0};
    for(int i=1;i<=total;i++)
    {
        if(hp[i]>=1)
        {
            pID[i]=i;
            pSpeed[i]=sp[i];
            pHp[i]=hp[i];
        }
    }
    int tmp;
    for(int i=1;i<total;i++)
        for(int j=i;j<=total;j++)
            if(pSpeed[i]<pSpeed[j]||(pSpeed[i]==pSpeed[j]&&pHp[i]<pHp[j]))
            {
                tmp=pId[i];pID[i]=pID[j];pID[j]=tmp;
                tmp=pSpeed[i];pSpeed[i]=pSpeed[j];pSpeed[j]=tmp;
                tmp=pHp[i];pHp[i]=pID[j];pHp[j]=tmp;
            }
    //unfinished
}
void env::plant()
{
    //更新水藻位置
}
int main()
{
    env env;
    env.init();
    for(int i=1;i<=ROUND;i++)
    {
        env.round();
        if(i%5==0) env.plant();
        env.outputResult();
    }
    return 0;
}
