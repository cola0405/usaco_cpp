// 问题的本质在于b按照当前排列, 循环数组做循环
// 找到和 a 一致的最大数量 + 与cycle无关的标签数量 = ans
// 如果是暴力枚举的话O(N^2) 只能过8个测试用例
// 优化方法 -- 统计各标签到一致位置的 offset -- offset 的最大值就是能够一致的最大数量

#include<bits/stdc++.h>
using namespace std;

int n,k;
int flags[500001], b[500001], b1[500001];
unordered_map<int, int> ax;  // {label: index} for a

int countOffset(int* label){
    unordered_map<int, int> offset;     // 因为可能存在负数，所以map更好
    for(int i=0; i<k; i++){
        if(ax.find(label[i]) != ax.end()) {     // 让offset方向一致 -- mod保证>=0
            offset[(k + (ax[label[i]] - i))%k]++;
        }
    }
    
    int maxCount = 0;
    for(auto it: offset) maxCount = max(maxCount, it.second);
    return maxCount;
}

int main(){
    // freopen("2.in", "r", stdin);
    // freopen("2.out", "w", stdout);

    cin>>n>>k;
    for(int i=0; i<k; i++){
        int a;
        cin>>a;
        ax[a] = i;
        flags[a] = 1;
    }
    for(int i=0; i<k; i++){
        cin>>b[i];
        b1[k-i-1] = b[i];
        flags[b[i]] = 1;
    }
    
    int ans = max(countOffset(b), countOffset(b1));
    for(int i=1; i<=n; i++) if(!flags[i]) ans++;
    cout<<ans<<endl;
}
