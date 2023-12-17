#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("3.out", "r", stdin);
    int n;
    cin>>n;
    vector<int> nums(100);
    for(int i=0; i<100;i++){
        cin>>nums[i];
    }
    sort(nums.begin(), nums.end());

    for(int i=0; i<99;i++){
        if(nums[i]+1 != nums[i+1]){
            cout<<nums[i]<<" "<<nums[i+1]<<endl;
        }
    }

}