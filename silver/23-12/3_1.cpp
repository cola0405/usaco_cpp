// 前缀后缀问题，解析看不懂 -- 以后再研究吧

#include<bits/stdc++.h>
using namespace std;

int T, C, t, pos = 0;
unordered_set<int> target;
unordered_map<int, int> shot_cnt;    // the number of shooting at pos
string commands;

vector<int> build_prefix(){
    unordered_set<int> s(target);
    vector<int> res = {0};
    for(int i=0; i<C; i++){
        if(commands[i] == 'F'){
            shot_cnt[pos]++;
            if(s.find(pos) != s.end()){
                res.push_back(res.back() + 1);
                s.erase(pos);
                continue;
            }
                 
        }
        else if(commands[i] == 'L') pos--;
        else pos++;
        res.push_back(res.back());
    }
    return res;
}

vector<vector<int>> build_suffix(){     // suf[i] represents the maximum number of targets could be shot using commands[i:] 
    vector<unordered_map<int, int>> sc(5, unordered_map<int, int>(shot_cnt));     // the shot_cnt for 5 offset
    vector<vector<int>> res(5, vector<int>(C+1));       // suffix for 5 offset
    for(int i=C-1; i>=0; i--){
        for(int j=0; j<5; j++){
            int offset = j-2;
            // when the shot_cnt == 1, which means it's the first time we shot at the current target
            if(commands[i] == 'F' && sc[j][pos+offset] == 1) res[j][i] = res[j][i+1] + 1;
            else res[j][i] = res[j][i+1];
            if(commands[i] == 'F') sc[j][pos+offset]--;
        }
        if(commands[i] == 'L') pos++;      // iteration from right to left 
        else if(commands[i] == 'R') pos--;
    }
    return res;
}

int main(){
    freopen("3.in", "r", stdin);
    freopen("3.out", "w", stdout);

    cin>>T>>C;
    for(int i=0; i<T; i++){
        cin>>t;
        target.insert(t);
    }
    cin>>commands;
    vector<int> pre = build_prefix();
    vector<vector<int>> suf = build_suffix();
    int ans = pre[C];   // didn't change the commands
    pos = 0;
    for(int i=0; i<C; i++){
        if(commands[i] == 'L'){
            int cnt1 = pre[i] + suf[3][i];    // L -> F
            if(target.find(pos) != target.end()) cnt1++;
            int cnt2 = pre[i] + suf[4][i];    // L -> R
            ans = max(ans, max(cnt1, cnt2));
            pos--;
        }
        else if(commands[i] == 'R'){
            int cnt1 = pre[i] + suf[1][i];    // R -> F
            if(target.find(pos) != target.end()) cnt1++;
            int cnt2 = pre[i] + suf[2][i];    // L -> R
            ans = max(ans, max(cnt1, cnt2));
            pos++;
        }else if(commands[i] == 'F'){
            int cnt1 = pre[i] + suf[2][i];    // F -> L
            int cnt2 = pre[i] + suf[3][i];    // F -> R
            ans = max(ans, max(cnt1, cnt2));
            if(target.find(pos) != target.end()) target.erase(pos);
        }
    }
    cout<<ans<<endl;
}

/*
有一些情况是压根就到不了 offset[2] 的
1 5
2
F

ans是0，而不是1
*/
