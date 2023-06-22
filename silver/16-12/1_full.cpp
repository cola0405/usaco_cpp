#include <bits/stdc++.h>
using namespace std;

int bis(vector<int> &arr, int target){
    int low, high;
    low = 0;
    high = arr.size()-1;
    while(low<high){
        int mid = (low+high+1)/2;
        if(arr[mid]>target){
            high = mid-1;
        }else{
            low = mid;
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
        int a = bis(hb, left);
        int b = bis(hb, right);
        if(hb[a] < left)a++;
        cout<<b-a+1<<endl;
    }
    return 0;
}