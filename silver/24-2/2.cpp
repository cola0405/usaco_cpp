// greedy
#include <bits/stdc++.h>
using namespace std;
int A=1,B=2,C=3;
vector<string> t;

string simplify(string s){
    string res;
    for(auto ch : s){
        if(res.empty() || ch != res.back()) res.push_back(ch);
    }
    return res;
}

void pour(int src, int dst){
    cout<<src<<' '<<dst<<'\n';
    if(t[dst].empty()) t[dst].push_back(t[src].back());
    t[src].pop_back();
}

void clear_tube(int i){
    while(t[i].size() > 1){
        if(t[i].back() == t[3^i].back()) pour(i, 3^i);
        else pour(i, C);
    }
}

void solve(){
    int n,p;
    cin>>n>>p;
    cin>>t[A]>>t[B];
    t[A] = simplify(t[A]);
    t[B] = simplify(t[B]);

    if(t[A][0] == t[B][0]){
        t[B].insert(t[B].begin(), '0' + (t[B][0]-'0')^3);
    }
    int ans = t[A].size() + t[B].size() - 2;    // "2" is the bottom of the tube
    if(ans>1) ans++;    // ans>1, which means we need to use t3 and we need to pour back
    cout<<ans<<endl;
    if(p == 1 || ans == 0) return;

    if(t[A].size() > t[B].size()) swap(A, B);
    // make sure the end of tube-A and tube-B is different
    if(t[B].back() == t[A].back()) pour(B, A);

    // the incorrect order will lead to the bad situation
    // A: 121   C:2
    // B: 2
    if(t[B].size() > 1 && t[B].back() == t[B][0]) {
        pour(B,C);
        clear_tube(A);
        clear_tube(B);      
    }else{
        clear_tube(B);
        clear_tube(A);
    }
    if(!t[C].empty()){
        if(t[C].back() == t[A].back()) pour(C, A);
        else pour(C, B);
    }
}

int main(){
    // freopen("2.in", "r", stdin);
    // freopen("2.out", "w", stdout);

    int T;
    cin>>T;
    while(T){
        t = {"", "", "", ""};
        A=1, B=2;
        solve();
        T--;
    }
}