// 草稿找规律
// 总共两种情况要处理:
// 1.特殊情况: 当前i是复制出来的，则转而end往前找 -- 规律:它总会是上一个end-1
// 2.普通情况: 求上一个i，可以直接i-(end+1) -- 规律总结出来的

// end为对折的关键点

#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("cowcode.in", "r", stdin);
    freopen("cowcode.out", "w", stdout);

    string s;
    long long n;
    cin>>s>>n;

    // get closest end
    long long end = s.size();
    while(end<n){
        end *= 2;
    }
    if(end>n)end/=2;
    while(n>s.size()){
        if(n==end || n==end+1){
            if(end == s.size()){
                n = end;
                continue;
            }
            end/=2;
            n = end - 1;  // special mode
        }else{             
            n = n - (end+1);  // normal mode
        }
        while(end>n)end/=2;
    }
    cout<<s[n-1]<<endl;
    return 0;
}