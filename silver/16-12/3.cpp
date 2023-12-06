// 单向图

#include <bits/stdc++.h>
using namespace std;

unordered_map<int, unordered_set<int>> reach;
int bfs(int start){
    unordered_set<int> already;
    vector<int> stack {start};
    while(!stack.empty()){
        int top = stack.back();
        stack.pop_back();
        already.insert(top);
        for(int dst : reach[top]){
            if(already.find(dst) == already.end()){
                stack.push_back(dst);
            }
        }
    }
    return already.size();
}

int main(){

    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    int n;
    vector<vector<int>> record;
    cin>>n;
    for(int i=0; i<n; i++){
        int x,y,r;
        cin>>x>>y>>r;
        record.push_back({x,y,r});
    }

    // 检查可达性O(n2)
    for(int i=0; i<n; i++){
        int x1 = record[i][0], y1 = record[i][1], r1 = record[i][2];
        for(int j=0; j<n; j++){   // j必须从0开始，重复没关系
            int x2 = record[j][0], y2 = record[j][1];
            if(pow(x2-x1, 2) + pow(y2-y1, 2) <= pow(r1, 2)){    // 单向图
                reach[i].insert(j);
            }
        }
    }

    int ans = 1;
    for(int i=0; i<n; i++){
        ans = max(ans, bfs(i));
    }

    cout<<ans<<endl;
}