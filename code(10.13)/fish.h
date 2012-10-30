#pragma once

#ifndef _FISH_H_
#define _FISH_H_

#include<ctime>
#include<cmath>

const int N=40;//地图横坐标范围1-N
const int M=40;//地图纵坐标范围1-M
const int MAX_PLAYER=40;//最多玩家数量，ID从1-MAX_PLAYER
const int MAX_FOOD=50;//刷新食物数量
const int FOOD_ROUND=5;//刷新食物回合数
const int EMPTY=0;//格子为空
const int FOOD=-1;//食物
const int LEVEL_POINT=3;//升级能获得的点数

int min(int a,int b) {if(a<b) return a; else return b;}
int max(int a,int b) {if(a>b) return a; else return b;}
int expSum(int dL)
{
    int sum=0;
    for(int i=2;i<=dL;i++) sum+=i;
    return sum;
}

class fish{
private:
    int x,y,exp,maxhp,att,sp,id,point,BonusExp;
    static int hp[MAX_PLAYER+1];
    static int level[MAX_PLAYER+1];
    void setID(int dID) {id=dID;} //设置ID，只可被调用一次
public:
    fish()
    {

        //assign initial coordinates
        int randX,randY;
        randX=rand()%N+1;
        randY=rand()%M+1;
        while(envAsk(randX,randY)) {randX=rand()%N+1;randY=rand()%M+1;}
        x=randX;y=randY;

        //assign initial other datas
        point=10;
        maxhp=att=sp=0;
        exp=0;
        BonusExp=0;
    }
    ~fish(){}
    void giveID(int dID) {id=dID;level[id]=1;}
    bool move(int dx,int dy);//移动到某个位置
    bool attack(int dx,int dy);//攻击某个位置
    int getPoint(){return point;}//返回当前玩家剩余点数
    int getLevel(){return level[id];}//返回当前玩家等级
    int getExp(){return exp;}//返回当前玩家经验
    int getX(){return x;}//返回当前玩家横坐标
    int getY(){return y;}//返回当前玩家纵坐标
    int getHP(){return hp[id];}//返回当前玩家生命值
    int getMaxHP(){return maxhp;}//返回当前玩家生命上限
    int getAtt(){return att;}//返回当前玩家攻击力
    int getSp(){return sp;}//返回当前玩家速度
    int getID(){return id;}//获取玩家ID
    int askWhat(int dx,int dy){return envAsk(dx,dy);}//返回地图某个位置内容（玩家ID或FOOD或EMPTY）
    int askHP(int dID){return hp[dID];}//询问某个玩家ID当前血量
    int askLevel(int dID){return level[dID];}
    int getBonusExp() {return BonusExp;}
    bool increaseHealth();//增加health属性1
    bool increaseStrength();//增加Strength属性1
    bool increaseSpeed();//增加Speed属性1
    bool decreaseHealth();//减少health属性1
    bool decreaseStrength();//减少Strength属性1
    bool decreaseSpeed();//减少Speed属性1
    void decreaseExp(int dExp);
    void decreaseLevel();
    void changeHp(int dhp);
    void refreshLV();
    int getGrade();
    void changeX(int dx);
    void changeY(int dy);

    virtual void init(){}//初始化函数，每一局重新开始将调用
    virtual void play(){}//行动函数，每回合行动将调用
    virtual void revive(int &rx,int &ry){}//复活时调用，参数传回选择复活位置（若不合法则随机）
};

void fish::changeX(int dx)
{
    x=dx;
}
void fish::changeY(int dy)
{
    y=dy;
}
bool fish::move(int dx,int dy)
{

    if(dx<1||dx>N) return false;
    if(dy<1||dy>M) return false;
    int yuanX,yuanY;
    yuanX=x;yuanY=y;
    if(haveMoved(id)||haveAttacked(id)) return false;
    if(envAsk(dx,dy)==EMPTY&&canGet(dx,dy,x,y,sp))
    {
        x=dx;y=dy;
        envMove(id,yuanX,yuanY);
        return true;
    }
    else
        return false;

}
void fish::refreshLV()
{
    int total=0;
    while(expSum(level[id]+1)<=exp) {level[id]++;total++;}
    point+=3*total;
}
bool fish::attack(int dx,int dy)
{
    int type=0;
    if(dx<1||dx>N) return false;
    if(dy<1||dy>M) return false;
    if(haveAttacked(id)) return false;
    int result=envAsk(dx,dy);
    if(result!=EMPTY&&canGet(dx,dy,x,y,1))
    {
        if(att>=1&&result==FOOD)
        {
            hp[id]=min(maxhp,hp[id]+max(2,maxhp/10));
            exp++;
            refreshLV();
            delFood(dx,dy);
        }
        else
        {
            type=1;
            hp[result]-=att;
            if(hp[result]<1)
            {
                if(askLevel(result)>level[id]) BonusExp+=(askLevel(result)-level[id]);
                exp+=max(1,askLevel(result)/2);
                refreshLV();
                deadQueue(result);
            }
        }
        envAttack(id,dx,dy,type);
        return true;
    }
    else
        return false;

}
bool fish::increaseHealth()
{
    if(point>0)
    {
        point--;
        hp[id]+=2;
        maxhp+=2;
        return true;
    }
    else
        return false;
}
bool fish::decreaseHealth()
{
    if(maxhp>2)
    {
        maxhp-=2;
        return true;
    }
    else
        return false;
}
bool fish::increaseSpeed()
{
    if(point>0)
    {
        point--;
        sp++;
        return true;
    }
    else
        return false;
}
bool fish::decreaseSpeed()
{
    if(sp>1)
    {
        sp--;
        return true;
    }
    else
        return false;
}
bool fish::increaseStrength()
{
    if(point>0)
    {
        point--;
        att++;
        return true;
    }
    else
        return false;
}
void fish::changeHp(int dhp)
{
    hp[id]=dhp;
}
bool fish::decreaseStrength()
{
    if(att>1)
    {
        att--;
        return true;
    }
    else
        return false;
}
void fish::decreaseLevel()
{
    if(level[id]>1)
    {
        level[id]--;
        decreaseExp(expSum(level[id]));
    }
}
void fish::decreaseExp(int dExp)
{
    exp=dExp;
}
int fish::getGrade()
{
    return exp+2*BonusExp;
}

int fish::hp[MAX_PLAYER+1]={0};
int fish::level[MAX_PLAYER+1];

#endif

//可自行增加所需函数及变量，但需保证上面每个函数的完整与可调用

//不要使用全局变量!!!
