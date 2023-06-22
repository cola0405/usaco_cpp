#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
int main(){

    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);


    int a,b,c,d;
    cin>>a>>b>>c>>d;

    vector<int> f(101,0);
    for(int i=a; i<b; i++){
        f[i] += 1;
    }
    for(int i=c; i<d; i++){
        f[i] += 1;
    }

    int ans = 0;
    for(int i=0; i<=100; i++){
        if(f[i]>=1){
            ans += 1;
        }
    }
    cout<<ans<<endl;
}