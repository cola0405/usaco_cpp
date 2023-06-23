#include <bits/stdc++.h>
using namespace std;

int end_time(vector<int>& duration, int k){
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0; i<k; i++){
        pq.push(duration[i]);
    }

    int t=0;
    for(int i=k; i<duration.size(); i++){
        t = pq.top();
        pq.pop();
        pq.push(t+duration[i]);
    }

    while(!pq.empty()){
        t = pq.top();
        pq.pop();
    }
    return t;
}


int main(){
    freopen("cowdance.in", "r", stdin);
    freopen("cowdance.out", "w", stdout);

    int n,t;
    cin>>n>>t;
    vector<int> duration(n);
    for(int i=0; i<n; i++){
        cin>>duration[i];
    }

    // binary search the k
    int low=1,high=n;
    while(low<high){   // lower bound, 关注左边，如果ok，则high往左边缩
        int mid = (low+high)/2;
        if(end_time(duration, mid) <= t){
            high = mid;
        }else{
            low = mid+1;
        }
    }
    cout<<low<<endl;
    return 0;
}