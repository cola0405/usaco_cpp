#include<bits/stdc++.h>
using namespace std;

int A=1, B=2, C=3;
vector<pair<int,int>> moves;
int ans = 0;
vector<string> tube = {"", "", "", ""};
string &a = tube[A], &b = tube[B], &c = tube[C];

int flag = -1;

void clear_tube(int a, int b, int c,int keep){
    int last = a;
    while(tube[a].size() > keep){
        if(tube[b].size() == 0){
            tube[b].push_back(tube[a].back());
            moves.push_back({a,b});
        }
        else if(tube[a].back() == tube[b].back()){
            moves.push_back({a,b});
        }
        else if(tube[c].size() == 0){
            tube[c].push_back(tube[a].back());
            moves.push_back({a,c});
        }
        else{
            moves.push_back({a,c});
        }
        tube[a].pop_back();
        ans++;
    }
}

void simplify(string& s){
    string tmp;
    for(auto ch : s){
        if(tmp.size() == 0 || tmp.back() != ch){
            tmp.push_back(ch);
        }
    }
    s = tmp;
}

void clear_c(){
    if(c.size()>0){
        if(a.size()==0 || c.back() == a.back()){
            a += c;
            moves.push_back({C,A});
            c = "";
            ans++;
        }
        else if (b.size()==0 || c.back() == b.back()){
            b += c;
            moves.push_back({C,B});
            c = "";
            ans++;
        }
    }
}

void solve(){
    int n,p;
    cin>>n>>p;
    cin>>a>>b;
    simplify(a);
    simplify(b);
    if(a.size() == 1){   // a is pure
        if(a[0] == b[0]){
            clear_tube(B,A,C,0);
            clear_c();
        }else{
            clear_tube(B,A,C,1);
            clear_c();
        }
        cout<<ans<<endl;
        if(p >= 2){
            for(auto& [src,dst] : moves){
                cout<<src<<" "<<dst<<endl;
            }
        }
        return;
    }else if(b.size() == 1){    // b is pure
        if(a[0] == b[0]){
            clear_tube(A,B,C,0);
            clear_c();
        }else{
            clear_tube(A,B,C,1);
            clear_c();
        }
        cout<<ans<<endl;
        if(p >= 2){
            for(auto& [src,dst] : moves){
                cout<<src<<" "<<dst<<endl;
            }
        }
        return;
    }

    if(a[0] == b[0]){   // when the bottom is the same, we must clear one tube
        // clear tube-a (default)
        flag = 1;
        char head = a[0];
        clear_tube(A,B,C,0);    // make a empty
        if(head == b.back()){
            a = c;
            c = "";
            moves.push_back({C,A});
            ans++;
        }
        clear_tube(B,A,C,1);
        clear_c();
    }
    else{
        flag = 2;
        // make tube-a clean (clean, not empty)
        clear_tube(A,B,C,1);
        clear_c();
        clear_tube(B,A,C,1);
        clear_c();
    }

    // cout<<ans<<" "<< flag<<endl;
    cout<<ans<<endl;
    if(p >= 2){
        for(auto& [src,dst] : moves){
            cout<<src<<" "<<dst<<endl;
        }
    }
}

int main(){
    freopen("2.in","r",stdin);
    freopen("2.out","w",stdout);

    int T;
    cin>>T;
    for(int u=0; u<T; u++){
        moves.clear();
        tube[C] = "";
        ans = 0;
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