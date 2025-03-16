// greedy
// 1.let two tubes have different end color
// 2.clear the tube by pouring it to another tube and beaker
// 3.clear another tube
// 4.clear beaker

/*
Q1: why we can just insert the color in the front of the string
insert the different color in front will not affect the final answer
for example:
origin:
12
1212

insertion:
212
1212

the min op is both 7

for origin: the greedy strategy is to clear the shorter tube, so we need to move out the "1"
for insertion: altought we don't need to clear the tube now, but we need to do the extra operation to move the 1 in tube-A

Q2: how to figure out the order of operations for 3 containers?
first of all, the order really matters!
check out this example:
1212
21

wrong solution:
121    2  =>   121    2  => Game Over
21             2

in the above example, we pour A to C, then we try to clear B, but fail
now let's try clear A first
121    2  =>   1    2    =>   1    2   =>  1   => Done!
21             21             2            2

for the correct order we need another example
121
212

also try two solutions:
12    1    =>    12    1    =>    1    1    =>    1    => Done!
212              2                2               2

12    1    =>    1    1    =>    Game Over
212              212

the problem is we need to avoid the situation that two containers have the same color on the top
then these two color is actually the back() and front() of a tube!
so we can get the conclusion:
when back() == front(), we should clear another tube first to avoid the conflict
when back() != front(), we can just clear the current tube 
 */


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

    // make sure the bottom of two tubes are the same color
    if(t[A][0] == t[B][0]){     
        // this operation will not affect the final answer
        t[B].insert(t[B].begin(), '0' + (t[B][0]-'0')^3);       
    }
    int ans = t[A].size() + t[B].size() - 2;    // "2" is the bottom of the tube
    if(ans>1) ans++;    // ans>1, which means we need to use t3 and we need to pour back
    cout<<ans<<endl;
    if(p == 1 || ans == 0) return;

    // make sure the end of tube-A and tube-B are different
    if(t[A].size() > 1 && t[A].back() == t[B].back()) pour(A, B);
    if(t[A].size() > 1 && t[A].back() == t[A].front()){   
        pour(A,C);          // the longer to C makes more sense
        clear_tube(B);      // clear another tube first
        clear_tube(A);
    }else{
        clear_tube(A);      // clear current tube first1
        clear_tube(B);
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

/*
1
2 3
12
22

1
3 3
1212
1111


 */