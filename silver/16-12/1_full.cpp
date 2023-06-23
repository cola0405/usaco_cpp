#include <bits/stdc++.h>
using namespace std;

int bis_lower(vector<int> &arr, int target){
    int low, high;
    low = 0;
    high = arr.size()-1;
    while(low<high){
        int mid = (low+high)/2;  // 关注左边的
        if(arr[mid]>=target){  // 如果ok，则high往左边缩
            high = mid;
        }else{
            low = mid+1;
        }
    }
    if(arr[low]<target)low++;
    return low;
}

int bis_upper(vector<int> &arr, int target){
    int low, high;
    low = 0;
    high = arr.size()-1;
    while(low<high){
        int mid = (low+high+1)/2;  // 关注右边的
        if(arr[mid]<=target){       // 如果可以则low提到high,则high做减一
            low = mid;
        }else{
            high = mid-1;
        }
    }
    return low;
}


int main(){
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);

    int n,q;
    cin>>n>>q;
    vector<int> hb(n);
    for(int i=0; i<n; i++){
        cin>>hb[i];
    }
    sort(hb.begin(), hb.end());

    // binary search to shrink
    for(int i=0; i<q; i++){
        int left, right;
        cin>>left>>right;
        int a = bis_lower(hb, left);
        int b = bis_upper(hb, right);
        cout<<b-a+1<<endl;
    }
    return 0;
}