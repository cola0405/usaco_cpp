// stack + 贪心
// 因为要回到x=0, 所以肯定得从右往左依次处理
// 然后贪心尽可能让一趟的范围更大 -- 只要 剩余次数>=3 即可贪过去

// 题目隐藏了一些内容没说，得自己推理
// Ai 其实必为偶数，如果有奇数的话，Bessie 肯定回不到 x=0
// 再者题目说所有 Ai 的和小于等于10^6，其实是在说答案的字符串长度不会超过10^6
// 也就是说一步步模拟是可行的


#include <bits/stdc++.h>
using namespace std;

int n,a;
vector<int> st;
vector<string> op = {"L", "R"};

int main(){
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    cin>>n;
    for(int i=0; i<n; i++){
        cin>>a;
        st.push_back(a-1);
    }
    string ans(n, 'R');   // 一定是要到最右的，然后从后往前处理
    while(!st.empty()){
        int top = st.size()-1;
        if(st.size() == 1){
            for(int i=0; i<st.front(); i++) ans.append(op[i%2]);
            st.pop_back();
        }else{
            while(st[top]>=3){  // 贪心的基准 -- 因为是一来一回，所以 3 才够
                int cnt = 0;
                int cur = top;
                while(cur>=0 && st[cur] >= 3){
                    st[cur] -= 2;
                    cnt++;
                    cur--;
                }
                string cmd1(cnt,'L'), cmd2(cnt,'R');    // 一来一回
                ans.append(cmd1);
                ans.append(cmd2);
            }
            
            // 贪完了，就以一个 "L" 完结
            ans.append("L");
            st.pop_back();
        }
    }
    cout<<ans<<endl;
}