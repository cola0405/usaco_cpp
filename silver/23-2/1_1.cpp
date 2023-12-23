// 暴力只能过4个

#include <bits/stdc++.h>
using namespace std;

int T,N;
long long tC,tM;
long long friends[100][3];

bool valid(int money){
    long long cLow = 0, cHigh = tC-1;     // 给 c upgrade 的可行范围
    for(int i=0; i<N; i++){
        long long needC=friends[i][0], needM=friends[i][1], wait=friends[i][2];
        if(needC == needM) continue;
        cHigh = (wait + needM*money - needM*tM - needC*tC) / (needM-needC);
        cLow = ((tC+tM) + needM*money - needM*tM - needC*tC) / (needM-needC);
    }
    return cLow<=cHigh;
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
