#include <iostream>
using namespace std;

int main(){

    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);

    int k,n;
    cin>>k>>n;

    // 还没到x就已经过线了
    int already = 1;
    while((1+already)*already < k*2){
        already++;
    }

    for(int i=0; i<n; i++){
        int x;
        cin>>x;

        if(x>=already){
            cout<<already<<endl;
            continue;
        }

        // 求出还未过线的最极限的h
        int h = 1;
        while(2*h*h - x*x + x <= k*2){
            h++;
        }
        h--;

        // up+down
        // ps:下降的时候注意是((h-1) - x)*(h-x)/2 和上时不太一样，差了最顶上的一项
        int d = (2*h*h - x*x + x)/2;
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