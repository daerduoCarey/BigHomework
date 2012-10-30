//fish.h

const int MAX=10;

class fish
{
    private:
        static int hp[MAX+1];
        int id;
        void setID(int dID) {id=dID;}
    public:
        void init(int dID) {setID(dID);hp[id]=10;}
        int getHp()
        {
            cout<<"第"<<id<<"号鱼的生命值是："<<hp[id]<<endl;
        }
        void changeHp(int dHP)
        {
            hp[id]=dHP;
        }
        void printFromMe()
        {
            for(int i=1;i<=5;i++) cout<<id<<":--->第"<<i<<"号鱼的生命值是："<<hp[i]<<endl;
            cout<<endl;
        }
};

int fish::hp[MAX+1];

