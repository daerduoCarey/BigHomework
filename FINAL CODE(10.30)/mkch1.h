#include "fish.h"

class mkch1:public fish{

    private:
        int round,point,id,lv,exp,x,y,hp,maxHp,att,sp,status;
        int pic[N+1][M+1];
        int DEAD,ALIVE;
        int INIT_HP,INIT_SP,LEAST_HP,MOST_HP;
        int Food_Value,Kill_Value;
        int MAX_INT;
        //int guessSp[MAX_PLAYER+1];   //注意revive后不能猜，真实速度>=guessSp[did],他还可以加点;

        void refreshGraph();
        void refreshData();
        void assignLeftPoint();
        //void refreshGuessSpeed();

        int evalueDanger(int dx,int dy);  //评估时需注意吃完水藻后风险降低
        int evalueProfit(int dx,int dy);
        int evalueDangerRevive(int dx,int dy);  //评估时需注意吃完水藻后风险降低
        int evalueProfitRevive(int dx,int dy);

        int dis(int x1,int y1,int x2,int y2);
        int max(int Inta,int Intb);
        int min(int Inta,int Intb);
        int abs(int Inta);

    public:
        void init();
        void play();
        void revive(int &toX,int &toY);
};

int mkch1::max(int Inta,int Intb)
{
    if(Inta>Intb) return Inta; else return Intb;
}

int mkch1::min(int Inta,int Intb)
{
    if(Inta<Intb) return Inta; else return Intb;
}

int mkch1::abs(int Inta)
{
    if(Inta>0) return Inta; else return -Inta;
}

int mkch1::dis(int x1,int y1,int x2,int y2)
{
     return abs(x1-x2)+abs(y1-y2);
}

void mkch1::refreshGraph()
{
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            pic[i][j]=askWhat(i,j);
    return ;
}

void mkch1::refreshData()
{
    point=getPoint();
    id=getID();
    lv=getLevel();
    exp=getExp();
    x=getX();
    y=getY();
    hp=getHP();
    maxHp=getMaxHP();
    att=getAtt();
    sp=getSp();
}

void mkch1::init()
{
    //const int initialized
    DEAD=-1,ALIVE=1;
    INIT_HP=6,INIT_SP=3,LEAST_HP=20,MOST_HP=100;
    Food_Value=10,Kill_Value=100;
    MAX_INT=1000000000;

    round=0;
    refreshData();
    refreshGraph();

    //initialize the points
    for(int i=1;i<=INIT_HP;i++) increaseHealth();
    for(int i=1;i<=INIT_SP;i++) increaseSpeed();
    for(int i=1;i<=10;i++) increaseStrength();
}

int mkch1::evalueDangerRevive(int dx,int dy)  //评估时需注意吃完水藻后风险降低
{
    int sum=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
        {
            int t=pic[i][j];
            if(t>0)
            {
                if(round<10)
                {
                    if(dis(i,j,dx,dy)<4) sum += 100;
                    else if(dis(i,j,dx,dy)<8) sum+=10;
                }
                else if(round<100)
                {
                    if(dis(i,j,dx,dy)<6) sum += 100;
                    else if(dis(i,j,dx,dy)<12) sum+=10;
                }
                else
                {
                    if(dis(i,j,dx,dy)<12) sum += 100;
                    else if(dis(i,j,dx,dy)<20) sum+=10;
                }
            }
        }
    if(round<50&&getPoint()>5) sum-=100;
    else if(getPoint()>30) sum-=1000;
    else if(getPoint()>20) sum-=300;
    else if(getPoint()>10) sum-=100;
    return sum;
}

int mkch1::evalueProfitRevive(int dx,int dy)
{
    int sum=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
        {
            if(dis(i,j,dx,dy)==1)
            {
                if(pic[i][j]==FOOD) sum+=Food_Value*100;
                else if(pic[i][j]>0&&askHP(pic[i][j])<=getAtt()+getPoint()) sum+=Kill_Value*10000;
            }
            else if(dis(i,j,dx,dy)<=getSp())
            {
                if(pic[i][j]==FOOD) sum+=Food_Value;
                else if(pic[i][j]>0&&askHP(pic[i][j])<=getAtt()+getPoint()) sum+=Kill_Value;
            }
            else if(dis(i,j,dx,dy)<=3*getSp())
            {
                if(pic[i][j]==FOOD) sum+=Food_Value/10;
                else if(pic[i][j]>0&&askHP(pic[i][j])<=getAtt()+getPoint()) sum+=Kill_Value/10;
            }
        }
    return sum;
}

int mkch1::evalueDanger(int dx,int dy)  //评估时需注意吃完水藻后风险降低
{
    int sum=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
        {
            int t=askWhat(i,j);
            if(t>0)
            {
                if(round<10)
                {
                    if(dis(i,j,dx,dy)<4) sum += 100;
                    else if(dis(i,j,dx,dy)<8) sum+=10;
                }
                else if(round<100)
                {
                    if(dis(i,j,dx,dy)<6) sum += 100;
                    else if(dis(i,j,dx,dy)<12) sum+=10;
                }
                else
                {
                    if(dis(i,j,dx,dy)<12) sum += 100;
                    else if(dis(i,j,dx,dy)<20) sum+=10;
                }
            }
        }
    if(round<50&&getPoint()>5) sum-=100;
    else if(getPoint()>30) sum-=1000;
    else if(getPoint()>20) sum-=300;
    else if(getPoint()>10) sum-=100;
    return sum;
}

int mkch1::evalueProfit(int dx,int dy)
{
    int sum=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
        {
            if(dis(i,j,dx,dy)==1)
            {
                if(askWhat(i,j)==FOOD) sum+=Food_Value*100;
                else if(askWhat(i,j)>0&&askHP(askWhat(i,j))<=getAtt()+getPoint()) sum+=Kill_Value*10000;
            }
            else if(dis(i,j,dx,dy)<=getSp())
            {
                if(askWhat(i,j)==FOOD) sum+=Food_Value;
                else if(askWhat(i,j)>0&&askHP(askWhat(i,j))<=getAtt()+getPoint()) sum+=Kill_Value;
            }
            else if(dis(i,j,dx,dy)<=3*getSp())
            {
                if(askWhat(i,j)==FOOD) sum+=Food_Value/10;
                else if(askWhat(i,j)>0&&askHP(askWhat(i,j))<=getAtt()+getPoint()) sum+=Kill_Value/10;
            }
        }
    return sum;
}

void mkch1::assignLeftPoint()
{
    int leftPoint=getPoint();
    if(round<40)
    {
        if(getHP()<=LEAST_HP/*||getHP()*10/getMaxHP()<8*/)
        {
            for(int i=1;i<=leftPoint;i++) {increaseHealth();/*cout<<"加血  hp: "<<getHP()<<"  maxhp:"<<getMaxHP()<<"   Least: "<<LEAST_HP;getchar();*/}
        }
        else if(getHP()>=MOST_HP)
        {
            for(int i=1;i<=leftPoint;i++) increaseSpeed();
        }
        else
        {
            for(int i=1;i<=1;i++) increaseHealth();
            for(int i=1;i<=2;i++) increaseSpeed();
        }
    }
    else
    {
        if(leftPoint>0)
        {
            if(getHP()<=LEAST_HP||getHP()*10/getMaxHP()<7)
            {
               while(getHP()<=MOST_HP&&getPoint()>0) increaseHealth();
            }
            if(getSp()<=30)
            {
                int tmp=getSp();
                while(getPoint()>0&&getSp()<=min(tmp+getPoint()*2/3,30)) increaseSpeed();
            }
        }
    }
}

void mkch1::play()
{
    cout<<id<<"  PLAY,in"<<endl;
    round++;
    //cout<<round<<"-";
    refreshData();
    refreshGraph();

    //evaluate where to go
    int danger[N+1][M+1]={0},profit[N+1][M+1]={0};
    int listd[N*M+1]={0},listp[N*M+1]={0},listx[N*M+1]={0},listy[N*M+1]={0};
    int t=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
        {
            t++;
            danger[i][j]=evalueDanger(i,j);
            profit[i][j]=evalueProfit(i,j);
            listp[t]=profit[i][j];
            listd[t]=danger[i][j];
            listx[t]=i;listy[t]=j;
        }

    for(int i=1;i<t;i++)
        for(int j=i+1;j<=t;j++)
            if((listp[i]<listp[j])||(listp[i]==listp[j]&&listd[i]>listd[i]))
            {
                int r=listp[i];listp[i]=listp[j];listp[j]=r;
                r=listd[i];listd[i]=listd[j];listd[j]=r;
                r=listx[i];listx[i]=listx[j];listx[j]=r;
                r=listy[i];listy[i]=listy[j];listy[j]=r;
            }

    bool f=false;
    int toX,toY;
    for(int i=1;i<=t&&(!f);i++)
    {
        if(listd[i]<200)
            f=move(listx[i],listy[i]);
        if(f) {toX=listx[i];toY=listy[i];}
    }
    if(f)
    {
        int a1[5]={0,1,0,-1,0},a2[5]={0,0,1,0,-1};
        int tx,ty;int food[5]={0},kill[5]={0};
        for(int i=1;i<=4;i++)
        {
            tx=getX()+a1[i];ty=getY()+a2[i];
            if((tx>=1&&tx<=N)||(ty>=1&&ty<=M))
            {
                int tmp=askWhat(tx,ty);
                if(tmp>0&&askHP(tmp)<=getPoint()+getAtt())
                {
                    kill[i]=1;
                }
                else if(tmp==FOOD&&getAtt()>=1)
                {
                    food[i]=1;
                }
            }
        }

        //attack player
        int maxKill=0,maxKillAddPoint=MAX_INT,maxKillDanger=evalueDanger(getX(),getY());
        for(int i=1;i<=4;i++)
            if(kill[i])
            {
                tx=getX()+a1[i];ty=getY()+a2[i];
                int tmp=askWhat(tx,ty);
                if((evalueDanger(tx,ty)<=maxKillDanger+10)&&(max(0,askHP(tmp)-getAtt())<maxKillAddPoint))
                {
                    maxKill=i;
                    //cout<<askHP(tmp)<<"@@@";
                    maxKillAddPoint=max(0,askHP(tmp)-getAtt());
                    maxKillDanger=evalueDanger(tx,ty);
                }
            }
        if(maxKill) {
            for(int i=1;i<=maxKillAddPoint;i++) increaseStrength();
            attack(getX()+a1[maxKill],getY()+a2[maxKill]);
            //cout<<"----ATT"<<maxKillAddPoint<<"ACK---";
        }

        //attack food
        maxKill=0,maxKillDanger=evalueDanger(getX(),getY());
        for(int i=1;i<=4;i++)
            if(food[i])
            {
                tx=getX()+a1[i];ty=getY()+a2[i];
                if((evalueDanger(tx,ty)<=maxKillDanger+10))
                {
                    maxKill=i;
                    maxKillDanger=evalueDanger(tx,ty);
                }
            }
        if(maxKill) attack(getX()+a1[maxKill],getY()+a2[maxKill]);
    }

    //assign leftPoint
    assignLeftPoint();

    refreshData();
    refreshGraph();

    cout<<id<<"   PLAY,out"<<endl;
}

void mkch1::revive(int &toX,int &toY)
{
    cout<<id<<"   REVIVE,in"<<endl;
    round+=2;

    //add hp
    while(getHP()<=MOST_HP&&getPoint()>0) increaseHealth();

    //evaluate where to revive
    int danger[N+1][M+1]={0},profit[N+1][M+1]={0};
    int listd[N*M+1]={0},listp[N*M+1]={0},listx[N*M+1]={0},listy[N*M+1]={0};
    int t=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
        {
            t++;
            danger[i][j]=evalueDangerRevive(i,j);
            profit[i][j]=evalueProfitRevive(i,j);
            listp[t]=profit[i][j];
            listd[t]=danger[i][j];
            listx[t]=i;listy[t]=j;
        }
    for(int i=1;i<t;i++)
        for(int j=i+1;j<=t;j++)
            if(listd[i]>listd[j]||(listd[i]==listd[j]&&listp[i]<listp[i]))
            {
                int r=listp[i];listp[i]=listp[j];listp[j]=r;
                r=listd[i];listd[i]=listd[j];listd[j]=r;
                r=listx[i];listx[i]=listx[j];listx[j]=r;
                r=listy[i];listy[i]=listy[j];listy[j]=r;
            }
    bool f=false;
    for(int i=1;i<=t&&(!f);i++)
    {
        f=move(listx[i],listy[i]);
        if(f) {toX=listx[i];toY=listy[i];}
    }
    cout<<id<<"   REVIVE,out"<<endl;
}



//可自行增加所需函数所需函数及变量，但需保证上面每个函数的完整与可调用

//不要使用全局变量！！
