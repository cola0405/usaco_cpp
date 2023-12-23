// 暴力只能过4个

#include <bits/stdc++.h>
using namespace std;

int T,N;
long long C0,M0;
long long friends[100][3];

bool valid(int money){
    long long cLow = 0, cHigh = C0-1;     // 给 c upgrade 的可行范围
    for(int i=0; i<N; i++){
        long long needC=friends[i][0], needM=friends[i][1], wait=friends[i][2];
        if(needC < needM){  // 不等式变换时，涉及到 (needM-needC) , 需要判断正负
            cHigh = min(cHigh, static_cast<long long>(floor((wait + needM*(money-M0) - needC*C0) / float(needM-needC))));
            cLow = max(cLow, static_cast<long long>(ceil(((needC+needM) + needM*(money-M0) - needC*C0) / float(needM-needC))));
        }else if(needC > needM){
            cHigh = min(cHigh, static_cast<long long>(floor(((needC+needM) + needM*(money-M0) - needC*C0) / float(needM-needC))));
            cLow = max(cLow, static_cast<long long>(ceil((wait + needM*(money-M0) - needC*C0) / float(needM-needC))));
        }else if(needC == needM){
            if(needC*(C0+M0-money) > wait || needC*(C0+M0-money) < needC*2) return false;
        }
    }
    return cLow<=cHigh && cHigh<=money;
}

int main(){
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);

    cin>>T;
    for(int r=0; r<T; r++){
        cin>>N>>C0>>M0;
        for(int i=0; i<N; i++){
            cin>>friends[i][0]>>friends[i][1]>>friends[i][2];
        }

        int low=0, high=C0+M0-2;
        while(low<high){
            int mid = (low+high)/2;
            if(valid(mid)) high = mid;
            else low = mid+1;
        }
        cout<<low<<endl;
    }
}
