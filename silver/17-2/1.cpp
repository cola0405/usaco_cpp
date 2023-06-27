// 贪心+二分
// 下面讨论怎么贪心

// t、cows都排序时，贪心的问题
// 那就是以a为基准排序，
// 举反例就行：
// t: 4 6
// (a,b): (1,7) (3,5)
// 合理分配下刚好够的，但是以a为基准排序贪心不行

// 再进一步分析，先把可行的喂给b小的，问题就解决了
// 所以贪心应该以b为重，先照顾end_time靠前的

#include <bits/stdc++.h>
using namespace std;

int bis(int a, int b, vector<int>& t){
    int low=0, high=t.size()-1;
    while(low<high){
        int mid = (low+high)/2;
        if(t[mid]<a){
            low = mid+1;
        }else if(t[mid]>b){
            high = mid-1;
        }else{
            // 不直接返回，会有随机性
            // 人为往左边靠，通过(low<high)结束二分，维持有序
            // 说白了，lower_bound
            high = mid;
        }
    }
    return low;
}

bool cmp(vector<int>& a, vector<int>& b){
    return a[1]<b[1];
}

int main(){
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);
    int c,n;
    cin>>c>>n;
    vector<int> t(c);
    for(int i=0; i<c; i++){
        cin>>t[i];
    }
    sort(t.begin(), t.end());

    vector<vector<int>> cows;
    int a,b;
    for(int i=0; i<n; i++){
        cin>>a>>b;
        cows.push_back({a,b});
    }

    sort(cows.begin(), cows.end(),cmp);  // 为什么按end_time排看开头注释
    int ans=0;
    for(vector<int>& pair : cows){
        if(t.size()==0)break;
        a = pair[0];
        b = pair[1];
        int idx = bis(a,b,t);
        if(t[idx]>=a && t[idx]<=b){
            t.erase(t.begin()+idx);  // 别过于害怕，不是每一个点都被删除的
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}