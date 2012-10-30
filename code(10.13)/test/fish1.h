
#ifndef _FISH1_H_
#define _FISH1_H_
class fish
{
    private:
        int id;
        void setID(int dID) {id=dID;}
    public:
        fish()
        {
            id=1;
        }
        int getID() {return id;}
        virtual void print(){}
};
#endif

