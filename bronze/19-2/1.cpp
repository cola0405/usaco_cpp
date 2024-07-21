#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    vector<int> p(3);
    for(int i=0; i<3; i++) cin>>p[i];
    sort(p.begin(), p.end());
    int min_op = min(p[1]-p[0], p[2]-p[1])-1;
    int max_op = max(p[1]-p[0], p[2]-p[1])-1;
    
    if(max_op == 0) cout<<0<<endl;
    else if(min_op == 1) cout<<1<<endl;
    else cout<<2<<endl;
    cout<<max_op<<endl;
    return 0;
}
