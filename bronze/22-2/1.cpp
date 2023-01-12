// 暴力90p
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

bool tryFinal(int final, vector<int> v, int n){
    int i,tmp,ans,count;
    i = tmp = ans = count = 0;
    while(i<n){
        tmp += v[i];
        count++;

        if(tmp == final){
            ans += count-1;
            tmp = count = 0;
        }else if(tmp > final){
            break;
        }
        i++;
    }

    // check fit or not
    if(i == n && tmp == 0){
        cout<<ans<<endl;
        return true;
    }else{
        return false;
    }
}


int main(){
    int t,n,i;
    cin>>t;
    for(int r=0; r<t; r++){
        cin>>n;
        vector<int> v(n);
        for(i=0; i<n; i++){
            cin>>v[i];
        }

        int s = accumulate(v.begin(), v.end(), 0);
        // 从组尽可能多开始枚举，使得合并操作更少
        for(int group=n; group>=1; group--){
            if(s%group != 0){
                continue;
            }

            int final = s/group;
            if(tryFinal(final, v, n)){
                break;
            }
        }

    }
}