// long long
// 比原来枚举的方法快了有十几倍
// 数值大了之后，那些乘方的运算其实是很耗时的


#include <iostream>
#include <cmath>
using namespace std;

int main(){
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);

    long long k,n;
    cin>>k>>n;

    int already = 1;
    while((1+already)*already < k*2){
        already++;
    }

    for(int i=0; i<n; i++){
        long long x;
        cin>>x;

        if(x>=already){
            cout<<already<<endl;
            continue;
        }
        // ps:下降的时候注意是((h-1) - x)*(h-x)/2 和上时不太一样，差了最顶上的一项
        long long h = sqrt((2*k + x*x - x) / 2);
        long long d = (2*h*h - x*x + x)/2;
        int ans = h + (h-x);
        if(d == k){
            cout<<ans<<endl;
        }else if(k-d <= h){
            cout<<ans+1<<endl;
        }else{
            cout<<ans+2<<endl;
        }
    }
}