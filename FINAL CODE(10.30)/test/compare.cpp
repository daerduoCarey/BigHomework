#include<iostream>
using namespace std;
int id[100]={0},a[100]={0},b[100]={0},n;
bool com(int i,int j)
{
    if(a[i]>a[j]||(a[i]==a[j]&&b[i]>b[j])) return true;
    else return false;
}
void swap(int i,int j)
{
    int tmp;
    tmp=id[i];id[i]=id[j];id[j]=tmp;
    tmp=a[i];a[i]=a[j];a[j]=tmp;
    tmp=b[i];b[i]=b[j];b[j]=tmp;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) id[i]=i;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<n;i++)
        for(int j=i+1;j<=n;j++)
            if(com(i,j)) swap(i,j);
    for(int i=1;i<=n;i++) cout<<id[i]<<"  ";
    cout<<endl;
    return 0;
}
