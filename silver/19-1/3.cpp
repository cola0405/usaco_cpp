// 贪心
// 直接研究顶点需要O(n^2)
// 注意到题目给出的45度的直角三角形 -- 转而研究左右两个端点
// 但是这题与lifeguard不一样，不是有独享就+1
// 我们需要找到ans+1的关键 —— 有新右端点比之前所有的右端点都大(突出去) —— 我们只关注右端点，理论上来说关注左端点也能做
// 这样才不会被前面的山覆盖 —— 也不会被后面的山覆盖 —— 如果后面有山能覆盖的话，肯定已经在前面就处理了 —— 有排序操作

#include <bits/stdc++.h>
using namespace std;

bool cmp(vector<int>& a, vector<int>& b){
    return a[0]<b[0] || (a[0]==b[0] && a[1]>b[1]);      // 从左到右排，然后右端点按降序排
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("mountains.in","r",stdin);
    freopen("mountains.out","w",stdout);
    
    int n,a,b,ans=1;    // ans至少有1个
    vector<vector<int>> v;
    cin>>n;
    
    for(int i=0;i<n;i++){
        cin>>a>>b;
        v.push_back({a-b, a+b});
    }
    sort(v.begin(), v.end(), cmp);
    int max_right = v[0][1];
    for(int i=1;i<n;i++){
        if(v[i][1] > max_right) {   // ans+1 的条件是有新右端点比之前所有的右端点都大 
            max_right = v[i][1];
            ans++;                  
        }
    }
    cout<<ans+1<<endl;
    return 0;
}