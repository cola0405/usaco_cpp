#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;


int main(){
    long long N, K;
    cin>>N>>K;

    vector<long long> days;
    for(int r=0; r<N; r++){
        long long d;
        cin>>d;
        days.push_back(d);
    }

    long long ans = K+1;
    long long end = days[0];

    for(int i=1; i<N; i++){
        long long gap = days[i] - end;
        if(gap < K+1){
            ans += gap;
        }else{
            ans += K+1;
        }
        end = days[i];
    }

    cout<<ans<<endl;



}