// 前缀后缀问题，解析看不懂 -- 以后再研究吧

#include<bits/stdc++.h>
using namespace std;

int t,c;
string cm;
int target[100001], L[100001], R[100001];
vector<int> op = {0,1,-1,2,-2};
unordered_map<int, int> offset, tx;
unordered_map<char, int> d = {{'L',-1}, {'R',1}};
unordered_map<int, unordered_map<int, int>> repeatHit;
unordered_map<int, int> cnt;

int main(){
    freopen("3.in", "r", stdin);
    freopen("3.out", "w", stdout);

    cin>>t>>c;
    for(int i=0; i<t; i++){
        cin>>target[i];
        tx[target[i]] = i;   // the distinct target can be the key
    }
    cin>>cm;

    int cur = 0;
    vector<int> hit;
    for(int i=0; i<c; i++){     // 统计默认情况下能射击到的目标
        if(cm[i] == 'F'){
            hit.push_back(cur);
            cnt[cur]++;
        }else{
            cur += d[cm[i]];
            if(cm[i] == 'L'){
                L[i+1] = L[i]+1;    // L R 前缀和统计数量 -- 高效求区间内L和R的数量
                R[i+1] = R[i];
            }else{
                L[i+1] = L[i];
                R[i+1] = R[i]+1;
            }
        }
    }

    // 判断两F之间的L和R来看 -- 情况太复杂。。 变F的话hits也跟着变化了  -- 肯定走弯路了
    for(int i=0; i<hit.size(); i++){
        for(auto it: op){
            // op 可达才往下
            if()
            if(tx.find(hit[i]+it) != tx.end()){  // 初次击中时才更新offset
                // up to 1 -- Bessie 可以不修改 -- 要保留offset[0]
                if(repeatHit[hit[i]][hit[i]+it]==0) offset[it]++;    // 应该是hit[i]已有的才不再统计
                repeatHit[hit[i]][hit[i]+it]++;
            }
        }
    }

    int ans = 0;
    for(auto it: offset) ans = max(ans, it.second);     // 如果 Bessie 不修改

    unordered_set<int> left, right(hit.begin(), hit.end());  // right 保存了右边的初始hits
    for(int i=0; i<hit.size(); i++){    // i及左边不偏移 + 右边看哪种偏移方式拿到最多命中
        cnt[hit[i]]--;
        if(cnt[hit[i]] == 0) right.erase(hit[i]);  // 更新right
        if(tx.find(hit[i]) != tx.end()) {
            if(left.find(hit[i]) == left.end()){  // 提前命中的 target 首次出现 -- 更新一次offset即可
                // left 已经命中的话，那需要更新之后的相关的offset
                for(auto it: op){
                    if(right.find(hit[i]-it) != right.end()){
                        offset[it]--;
                    }
                }
            }
            left.insert(hit[i]);   // left 击中的目标需要去重
        }

        for(auto it: op){       // 清除hit[i] 对offset的影响
            if(tx.find(hit[i]+it) != tx.end()){
                repeatHit[hit[i]][hit[i]+it]--;     // 最后一个去了offset才-1
                if(repeatHit[hit[i]][hit[i]+it]==0) offset[it]--;    // up to 1 -- Bessie 可以不修改
            }
        }
        // 拿当前的命中情况更新ans
        for(auto it: offset) ans = max(ans, int(left.size() + it.second));
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
