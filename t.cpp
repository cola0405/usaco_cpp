#include<iostream>
using namespace std;
int main()
{
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    int bb,ba,sb,sa,sans,gb,ga,gans,pb,pa,pans;
    cin>>bb>>ba>>sb>>sa>>gb>>ga>>pb>>pa;
    pans=pa-pb;
    gans=(ga+pans)-gb;
    sans=(sa+gans)-sb;
    cout<<sans<<endl;
    cout<<gans<<endl;
    cout<<pans<<endl;
}
