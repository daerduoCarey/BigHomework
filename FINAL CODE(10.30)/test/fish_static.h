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
            cout<<"��"<<id<<"���������ֵ�ǣ�"<<hp[id]<<endl;
        }
        void changeHp(int dHP)
        {
            hp[id]=dHP;
        }
        void printFromMe()
        {
            for(int i=1;i<=5;i++) cout<<id<<":--->��"<<i<<"���������ֵ�ǣ�"<<hp[i]<<endl;
            cout<<endl;
        }
};

int fish::hp[MAX+1];

