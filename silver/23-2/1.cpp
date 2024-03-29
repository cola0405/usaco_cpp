// 暴力只能过4个

#include <bits/stdc++.h>
using namespace std;

int T,N;
long long tC,tM;
long long friends[100][3];
unordered_map<int, unordered_map<int>>

bool valid(int money){
    for(int a=0; a<=money; a++){    // 这个10^9 没办法优化
        int b = money-a;
        long long cTime=max(1ll,tC-a), mTime=max(1ll,tM-b);
        int flag = 1;
        for(int i=0; i<N; i++){
            long long needC=friends[i][0], needM=friends[i][1], wait=friends[i][2];
            if(needC*cTime + needM*mTime > wait){
                flag = 0;
                break;
            }
        }
        if(flag) return true;
    }
    return false;
}

int main(){
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);

    cin>>T;
    for(int r=0; r<T; r++){
        cin>>N>>tC>>tM;
        for(int i=0; i<N; i++){
            cin>>friends[i][0]>>friends[i][1]>>friends[i][2];
        }

        int low=0, high=tC+tM-2;
        while(low<high){
            int mid = (low+high)/2;
            if(valid(mid)) high = mid;
            else low = mid+1;
        }
        cout<<low<<endl;
    }
}
