// 基本过程模拟完成
// 下面解决last K 显示的问题 -- 没办法中途判定了 -- 只能走到 last k
// 如何模拟补位

#include<bits/stdc++.h>
using namespace std;

int t,n,m,k;
int folder[10001], email[100001];
unordered_map<int, int> remain;  // email 剩余数量统计
unordered_map<int, int> windowCnt;
vector<int> tmp;

void check(){
    deque<int> right;
    int j=1;

    for(int head=1; head<=n; head++){  // 每轮循环是去处理 left 的队首
        while(remain[head] > 0){    // 只要队首 folder 还没处理完，就模拟下滚
            if(right.size() < k){
                if(j <= n){     // 还没滚到底
                    if(email[j] >= head && email[j] <= head+k-1){
                        remain[email[j]]--;
                    }
                    else{
                        right.push_back(email[j]);
                        windowCnt[email[j]]++;
                    }
                    j++;
                }
                else{   // 下滚到底了，则tmp补位回right -- 模拟补位
                    while(!tmp.empty() && right.size() < k){
                        if(tmp.back() >= head && tmp.back() <= head+k-1){   // 补位过来的一旦可以放，那就放
                            remain[tmp.back()]--;   // 不会减到负数的 -- 会重复减吗
                        }else{
                            right.push_front(tmp.back());
                            windowCnt[tmp.back()]++;
                        }
                        tmp.pop_back();
                    }
                    if(windowCnt[head] > 0)

                    if(!tmp.empty()){
                        if(tmp.back() == head){
                            remain[head]--;
                            tmp.pop_back();
                        }else{          // 补位后，一有不对应就return false？
                            cout<<"NO"<<endl;
                            return;
                        }
                    }
                }
            }
            else{                       
                if(!right.empty()){     // 如果当前窗口没有可放的 email，则tmp入栈一个
                    tmp.push_back(right.front());
                    tmp[right.front()]++;
                    right.pop();
                }
            }
        }

    }
    cout<<"YES"<<endl;
}

int main(){
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    cin>>t;
    for(int r=0; r<t; r++){
        cin>>m>>n>>k;
        remain.clear();
        for(int i=1; i<=n; i++){
            cin>>email[i];
            remain[email[i]]++;
        }
        tmp.clear();
        check();
    }
}