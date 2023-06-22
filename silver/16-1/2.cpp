#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    int n,id;
    cin>>n;

    // (p[j]-p[i-1])%7==0
    // p[j]%7 == p[i-1]%7
    // 问题转换为找%7余数相等的最大gap
    // 所以建立长度为7的两个数组，分别存储对应余数的最边缘index
    vector<int> left(7,INT_MAX);
    vector<int> right(7);
    long long cur;
    for(int i=0; i<n; i++){
        cin>>id;
        cur = (cur+id)%7;
        left[cur] = min(i, left[cur]);
        right[cur] = i;
    }

    int max_gap = 0;
    for(int i=0; i<7; i++){
        max_gap = max(right[i]-left[i], max_gap);
    }
    cout<<max_gap<<endl;
    return 0;
}