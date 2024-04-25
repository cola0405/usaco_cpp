#include<bits/stdc++.h>
using namespace std;

int A=1, B=2, C=3;
vector<pair<int,int>> moves;
int ans = 0;
vector<string> tube = {"", "", "", ""};
string &c = tube[C];

void pour(int src, int dst){
    moves.push_back({src,dst});
    if(tube[dst].empty()) tube[dst].push_back(tube[src].back());
    tube[src].pop_back();
}

void clear_tube(int t, int t1, int t2){     // from t to t1 or t2
    while(tube[t].size() > 1){
        if(tube[t].back() == tube[t1].back()) pour(t,t1);
        else pour(t,t2);
    }
}

void simplify(string& s){       // remove consecutive same elements
    string tmp;
    for(auto ch : s){
        if(tmp.empty() || tmp.back() != ch) tmp.push_back(ch);
    }
    s = tmp;
}

void clear_c(){
    if(!c.empty()){
        if(c.back() == tube[A].back()) pour(C,A);
        else pour(C,B);
    }
}

void solve(){
    int n,p;
    cin>>n>>p;
    cin>>tube[A]>>tube[B];
    simplify(tube[A]);
    simplify(tube[B]);

    if(tube[A][0] == tube[B][0]){
        // make the head different (ps: it will not affect the min operation)
        tube[B].insert(0,1,'0' + (tube[B][0]-'0')^3);
    }

    ans = tube[A].size() + tube[B].size() - 2;
    if(ans > 1) ans++;
    cout<<ans<<endl;
    if(p == 1) return;

    // sort the tubes
    if(tube[A].size() > tube[B].size()){
        int T = A;
        A = B;
        B = T;
    }
    // if a.top == b.top, pour the longer one to the shorter
    if(tube[A].back() == tube[B].back()) pour(B,A);
    if(tube[A].size() == 1){
        clear_tube(B,A,C);
        clear_c();
    }else{
        pour(B,C);   // to beaker
        if(c[0] != tube[A][0]){
            clear_tube(A,B,C);
            clear_tube(B,A,C);
        }else{
            clear_tube(B,A,C);
            clear_tube(A,B,C);
        }
        clear_c();
    }
    for(auto& [src,dst] : moves) cout<<src<<" "<<dst<<endl;
}

int main(){
    // freopen("2.in","r",stdin);
    // freopen("2.out","w",stdout);

    int T;
    cin>>T;
    for(int u=0; u<T; u++){
        moves = {};
        ans=0, A=1, B=2;
        tube = {"", "", "", ""};
        solve();
    }
    return 0;
}

/*
1
5 3
21212
22211

212
212

*/