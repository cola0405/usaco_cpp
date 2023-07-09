// 把每对点拆出来，按先后顺序排列
// 根据当前点是start还是end进行贪心统计sum和min_own
// python的代码可能会更容易理解
#include <bits/stdc++.h>
using namespace std;

bool cmp(vector<int>& a, vector<int>& b){
    return a[1]<b[1];  // 小于则从小到大
}

int main(){
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    int n;
    cin>>n;
    vector<vector<int>> points;
    int start, end;
    for(int i=0; i<n; i++){
        cin>>start>>end;
        points.push_back({i, start});
        points.push_back({i, end});
    }
    sort(points.begin(), points.end(),cmp);
    int sum=0;
    unordered_set<int> start_ready;  // id of the start
    vector<int> own(n);
    int last = 0;

    for(int i=0; i<2*n; i++){
        int cur_id = points[i][0];
        int cur_pos = points[i][1];

        int gap = cur_pos-last;
        if(start_ready.size()==1){  // 只有start ready为1的时候才有own
            for(int id : start_ready){
                own[id] += gap;
            }
        }
        if(start_ready.size()>0)sum += gap;  // 只要有start ready 则就可以统计sum
        if(start_ready.find(cur_id)!=start_ready.end()){
            start_ready.erase(cur_id);
        }else{
            start_ready.insert(cur_id);
        }
        last = cur_pos;
    }
    cout<<sum-(*min_element(own.begin(), own.end()))<<endl;
    return 0;
}