// 贪心+二分

// 对 end_time 进行排序
// 有点贪心的意思，对于某一个鸡，如果有多头牛可配对，我们肯定希望让 end_time 小的牛先走
// 因为从左往右处理过来，它当前机会比其他牛少,其他的牛之后还有机会

// 可能你会考虑到，end_time 大的，有可能 start_time 也大，总的机会也不大呀
// 请考虑如下测试用例

/*

2 2
1
3
1 4
3 5

 */

// 我们按照 end_time 排序，先处理 (1,3) 然后选取 lower_bound(1)
// 取到1，然后剩下的 3 就留给(3,5) 了
// lower_bound 尽可能地往左边找，可以尽可能避免占用


#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int,int>& a, pair<int,int>& b){
    return a.second < b.second;
}

int main(){
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);
    
    int c,n;
    cin>>c>>n;
    vector<int> t(c);
    for(int i=0; i<c; i++) cin >> t[i];
    sort(t.begin(), t.end());

    vector<pair<int,int>> cows(n);
    for(int i=0; i<n; i++) cin >> cows[i].first >> cows[i].second;
    sort(cows.begin(), cows.end(), cmp);

    int ans = 0;
    for(auto &[a,b] : cows){
        if(t.size() == 0) break;
        // 找到大于等于a的最小的
        int i = lower_bound(t.begin(), t.end(), a) - t.begin();
        if(i < t.size() && t[i] <= b){      // a <= t[i] <= b
            ans++;
            t.erase(t.begin()+i);
        }
    }
    cout<<ans<<endl;
    return 0;
}