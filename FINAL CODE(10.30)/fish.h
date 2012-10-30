#pragma once

#ifndef _FISH_H_
#define _FISH_H_

#include<ctime>
#include<cmath>

const int N=40;//��ͼ�����귶Χ1-N
const int M=40;//��ͼ�����귶Χ1-M
const int MAX_PLAYER=40;//������������ID��1-MAX_PLAYER
const int MAX_FOOD=50;//ˢ��ʳ������
const int FOOD_ROUND=5;//ˢ��ʳ��غ���
const int EMPTY=0;//����Ϊ��
const int FOOD=-1;//ʳ��
const int LEVEL_POINT=3;//�����ܻ�õĵ���

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
    void setID(int dID) {id=dID;} //����ID��ֻ�ɱ�����һ��
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
    bool move(int dx,int dy);//�ƶ���ĳ��λ��
    bool attack(int dx,int dy);//����ĳ��λ��
    int getPoint(){return point;}//���ص�ǰ���ʣ�����
    int getLevel(){return level[id];}//���ص�ǰ��ҵȼ�
    int getExp(){return exp;}//���ص�ǰ��Ҿ���
    int getX(){return x;}//���ص�ǰ��Һ�����
    int getY(){return y;}//���ص�ǰ���������
    int getHP(){return hp[id];}//���ص�ǰ�������ֵ
    int getMaxHP(){return maxhp;}//���ص�ǰ�����������
    int getAtt(){return att;}//���ص�ǰ��ҹ�����
    int getSp(){return sp;}//���ص�ǰ����ٶ�
    int getID(){return id;}//��ȡ���ID
    int askWhat(int dx,int dy){return envAsk(dx,dy);}//���ص�ͼĳ��λ�����ݣ����ID��FOOD��EMPTY��
    int askHP(int dID){return hp[dID];}//ѯ��ĳ�����ID��ǰѪ��
    int askLevel(int dID){return level[dID];}
    int getBonusExp() {return BonusExp;}
    bool increaseHealth();//����health����1
    bool increaseStrength();//����Strength����1
    bool increaseSpeed();//����Speed����1
    bool decreaseHealth();//����health����1
    bool decreaseStrength();//����Strength����1
    bool decreaseSpeed();//����Speed����1
    void decreaseExp(int dExp);
    void decreaseLevel();
    void changeHp(int dhp);
    void refreshLV();
    int getGrade();
    void changeX(int dx);
    void changeY(int dy);

    virtual void init(){}//��ʼ��������ÿһ�����¿�ʼ������
    virtual void play(){}//�ж�������ÿ�غ��ж�������
    virtual void revive(int &rx,int &ry){}//����ʱ���ã���������ѡ�񸴻�λ�ã������Ϸ��������
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

//�������������躯�������������豣֤����ÿ��������������ɵ���

//��Ҫʹ��ȫ�ֱ���!!!
