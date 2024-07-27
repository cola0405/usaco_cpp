// suffix + offset + math

// 难点在于如何求出修改之后的有效击中目标
// 这里用suffix解决
// 然后通过维护cnt数组来解决不同的offset问题
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int T, C, t, pos=0, ans=0, res, x;
string c;
unordered_map<int, int> cnt,target;                // s is backup

void init(){        // 方便重置pos、cnt等
    pos = res = 0;
    cnt.clear();
    for(int i=0; i<C; i++){
        if(c[i] == 'L') pos--;
        if(c[i] == 'R') pos++;
        if(c[i] == 'F') {
            if(++cnt[pos] == 1 && target[pos]) res++;      // valid hit
        }
    }
}
void l2f(){
    init();
    for(int i=C-1; i>=0; i--){
        if(c[i] == 'L'){
            pos++;
            // 这里cnt==0，是含suffix的，为0即表示suffix和prefix都没有射击此pos
            ans = max(ans, res + (target[pos] && cnt[pos]==0));
        }
        else if(c[i] == 'R') pos--;
        else{
            // 如果--cnt[pos]==0, 首先suffix并没有新增的有效射击（每个suffix的偏移射击都已经更新到cnt了）
            // 然后其同时还表示这个目标已经没法射击到了，故-1
            if(target[pos] && --cnt[pos] == 0) res--;      

            // 这个是偏移后的射击，如果是有效射击，则+1
            if(target[pos+1] && ++cnt[pos+1] == 1) res++;
        }
    }
}

void l2r(){
    init();
    for(int i=C-1; i>=0; i--){
        if(c[i] == 'L') pos++, ans = max(ans, res);
        else if(c[i] == 'R') pos--;
        else{
            if(target[pos] && --cnt[pos] == 0) res--;
            if(target[pos+2] && ++cnt[pos+2] == 1) res++;
        }
    }
}

void r2f(){
    init();
    for(int i=C-1; i>=0; i--){
        if(c[i] == 'L') pos++;
        else if(c[i] == 'R') pos--, ans = max(ans, res + (target[pos] && cnt[pos]==0));
        else{
            if(target[pos] && --cnt[pos] == 0) res--;       // update cnt, make detection valid
            if(target[pos-1] && ++cnt[pos-1] == 1) res++;   // new position
        }
    }
}

void r2l(){
    init();
    for(int i=C-1; i>=0; i--){
        if(c[i] == 'L') pos++;
        else if(c[i] == 'R') pos--, ans = max(ans, res);
        else{
            if(target[pos] && --cnt[pos] == 0) res--;
            if(target[pos-2] && ++cnt[pos-2] == 1) res++;
        }
    }
}

void f2l(){
    init();
    for(int i=C-1; i>=0; i--){
        if(c[i] == 'L') pos++;
        else if(c[i] == 'R') pos--;
        else{
            if(target[pos] && --cnt[pos] == 0) res--;
            if(target[pos-1] && ++cnt[pos-1] == 1) res++;  
            ans = max(ans, res);     
        }
    }
}

void f2r(){
    init();
    for(int i=C-1; i>=0; i--){
        if(c[i] == 'L') pos++;
        else if(c[i] == 'R') pos--;
        else{
            if(target[pos] && --cnt[pos] == 0) res--;       // update cnt, make detection valid
            if(target[pos+1] && ++cnt[pos+1] == 1) res++;   // new position
            ans = max(ans, res);
        }
    }
}

int main()
{
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin>>T>>C;
    for(int i=0; i<T; i++){
        cin>>x;
        target[x] = 1;
    }
    cin>>c;
    init();
    ans = res;

    l2f();
    r2f();
    l2r();
    r2l();
    f2l();
    f2r();
    cout<<ans<<endl;
    return 0;
}


/*
3 5
0 1 2
RRFRF
(3)

5 12
-1 0 1 2 4
RFRFRFLFLFLF
(4)

3 6
-1 0 1
FRFFLF
(3)


*/
