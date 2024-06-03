// not done yet, the result less than answer

#include<bits/stdc++.h>
using namespace std;

int T, C, t, pos = 0;
unordered_set<int> target;
unordered_set<int> L;                // {pos} store the hit target use commands[:cur]
unordered_map<int, int> first;       // {i: pos} record the first shoot to the target
string commands;

bool fisrt_shoot(int i){
    return target.find(i) != target.end() && L.find(i) == L.end();
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
    for(int i=0; i<C; i++){
        if(commands[i] == 'F'){
            if(target.find(pos) != target.end()){
                if(L.find(pos) == L.end()) first[i] = pos;     // only record the first shoot
                L.insert(pos);
            }
        }                                                                                    
        else if(commands[i] == 'L') pos--;
        else pos++;
    }
    
    vector<unordered_set<int>> right_valid(5);      // all valid shoot at right
    vector<unordered_set<int>> already(5);          // the target already be hit -- but it may work when the previous F changes to L or R
    int ans = L.size();   // the number with the origin commands
    for(int i=C-1; i>=0; i--){
        // update L first (pop out the commands[i])
        if(first.find(i) != first.end()) L.erase(first[i]);
        if(commands[i] == 'L'){
            pos++;
            int cnt1 = L.size() + right_valid[3].size();     // L -> F
            if(fisrt_shoot(pos) && right_valid[3].find(pos) == right_valid[3].end()) cnt1++;        // check the cur_pos exist target or not
            int cnt2 = L.size() + right_valid[4].size();     // L -> R
            ans = max(ans, max(cnt1, cnt2));
        }else if(commands[i] == 'R'){
            pos--;
            int cnt1 = L.size() + right_valid[1].size();     // R -> F
            if(fisrt_shoot(pos) && right_valid[1].find(pos) == right_valid[1].end()) cnt1++;
            int cnt2 = L.size() + right_valid[0].size();     // R -> L
            ans = max(ans, max(cnt1, cnt2));
        }else{
            int cnt1 = L.size() + right_valid[1].size();     // F -> L
            if(fisrt_shoot(pos) && already[1].find(pos) != already[1].end()) cnt1++;
            int cnt2 = L.size() + right_valid[3].size();     // F -> R
            if(fisrt_shoot(pos) && already[3].find(pos) != already[3].end()) cnt2++;
            ans = max(ans, max(cnt1, cnt2));
        }

        // after let right_valid not inlcude i
        if(commands[i] == 'F'){     
            for(int j=0; j<5; j++){
                int offset = j-2;
                if(fisrt_shoot(pos+offset)){
                    right_valid[j].insert(pos+offset);
                }else if(target.find(pos+offset) != target.end()){
                    already[j].insert(pos+offset);        // the target which is hit more than once
                }
            }
        }
    }
    cout<<ans<<endl;
}

/*
有一些情况是压根就到不了 offset[2] 的
1 5
2
FFFFF

ans是0，而不是1


2 7
-2 3
RRRLLLF
*/
