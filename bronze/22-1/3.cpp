// 手写测试用例调试
// long long
// 0ll 这个是真坑啊
// 全部用long long，省事

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main(){
    long long t,n,i,r;
    cin>>t;
    for(r=0; r<t; r++){
        cin>>n;
        vector<long long> v(n);
        for(i=0; i<n; i++){
            cin>>v[i];
        }

        if(n==1){
            cout<<0<<endl;
            continue;
        }

        long long s = accumulate(v.begin(), v.end(), 0ll);
        long long final = v[0];
        for(i=1; i<n; i++){
            int gap = v[i]-v[i-1];
            if(gap == 0){
                continue;
            }
            if(gap>0){
                if(i+1<n && v[i+1]>=gap){
                    v[i] -= gap;
                    v[i+1] -= gap;
                }else{
                    cout<<-1<<endl;
                    break;
                }
                final = min(v[i], final);
            }else{
                if(i%2 == 0){
                    final = min(v[i], final);
                }else{
                    cout<<-1<<endl;
                    break;
                }
            }
        }

        if(i==n){
            long long ans = s - n*final;
            cout<<ans<<endl;
        }
    }
}


//1
//4
//2 3 3 2


