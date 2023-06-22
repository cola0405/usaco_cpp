#include <iostream>
#include <vector>

using namespace std;

int main(){

    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);

    vector<int> bronze(2), silver(2), gold(2), platinum(2);
    cin>>bronze[0]>>bronze[1];
    cin>>silver[0]>>silver[1];
    cin>>gold[0]>>gold[1];
    cin>>platinum[0]>>platinum[1];

    int g2p = platinum[1] - platinum[0];
    int s2g = gold[1] - gold[0] + g2p;
    int b2s = silver[1] - silver[0] + s2g;

    cout<<b2s<<endl;
    cout<<s2g<<endl;
    cout<<g2p<<endl;
}