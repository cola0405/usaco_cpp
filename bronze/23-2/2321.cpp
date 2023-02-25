#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;


int main(){
    long long N, T;
    cin>>N>>T;

    long long ans=0, last=0;
    for(int r=0; r<N; r++){
        long long di, bi;
        cin>>di>>bi;

        if(ans >= T || last >= T){
            break;
        }

        if(di <= last){
            ans += min(last+bi, T) - last;
            last += bi;
        }else{
            ans += min(di+bi-1, T) - di+1;
            last = di+bi-1;
        }
    }

    if(ans >= T){
        cout<<T<<endl;
    }else{
        cout<<ans<<endl;
    }

}