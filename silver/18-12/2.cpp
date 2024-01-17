#include<bits/stdc++.h>
using namespace std;

int n,arrive,spend;
vector<vector<int>> cows;

bool cmp(const vector<int>& a, const vector<int>& b){
    return a[0] < b[0];
}

struct PQcmp {
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        return a[2] < b[2];     // 级别从高到低
    }
};

int main(){
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);

    cin>>n;
    for(int i=0; i<n; i++){
        cin>>arrive>>spend;
        cows.push_back({arrive, spend, i});
    }
    sort(cows.begin(), cows.end(), cmp);
    priority_queue<vector<int>, vector<vector<int>>, PQcmp> pq;
    int i = 0, cur = 0;

    while(i<n){
        if(pq.empty()){
            vector<int> top = pq.top();
            arrive = top[0], spend = top[1];
            cur = arrive + spend;
            pq.pop();

            while(i<n && cows[i][0] < cur){
                pq.push(cows[i]);
                i++;
            }
        }
        else{
            vector<int> top = pq.top();
            arrive = top[0], spend = top[1];
            cur += spend;
            pq.pop();
        }
    }

    cout<<1<<endl;

}