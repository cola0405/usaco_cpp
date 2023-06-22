#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

bool comfortable(vector<int> & t){
    for(auto temperature : t){
        if(temperature>0){
            return false;
        }
    }
    return true;
}

int main(){
    int N, M;
    cin>>N>>M;

    vector<int> target(101,0);
    for(int i=0; i<N; i++){
        int s,t,c;
        cin>>s>>t>>c;
        for(int j=s; j<=t; j++){
            target[j] += c;
        }
    }

    vector<vector<int>> acs;
    for(int i=0; i<M; i++){
        vector<int> t(4);
        cin>>t[0]>>t[1]>>t[2]>>t[3];
        acs.push_back(t);
    }

    vector<int> v(M);
    int ans = INT_MAX;
    for(int num=1; num<=M; num++){
        fill(v.begin(), v.end(), 0);
        fill(v.end()-num, v.end(), 1);

        do {
            int cost = 0;
            vector<int> temp(target);
            for(int i = 0; i < M; ++i) {
                if (v[i]) {
                    int a = acs[i][0], b = acs[i][1];
                    int p = acs[i][2], m = acs[i][3];
                    for(int j=a; j<=b; j++){
                        temp[j] -= p;
                    }
                    cost += m;
                }
            }
            if(comfortable(temp)){
                ans = min(cost, ans);
            }
        } while (next_permutation(v.begin(), v.end()));
    }
    cout<<ans<<endl;
}