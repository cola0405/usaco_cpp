// 抽象hash滑动窗口懒更新 + 双端队列 + 栈

// 题目的 folders 和 emails 是在两个不同的窗口 -- 分别独立下滑的
// 要解决的问题就是: 如何高效把当前窗口下能够处理的 email 找出来并且进行处理
// 滑动窗口不行 -- 查找效率低
// 优先级队列不行 -- 涉及到区间内的修改
// 这里使用hash -- 每次left窗口下移，只要一出现新的folder, 就检查对应的count(只统计窗口内的email数量)
// 检查是否有 email 可以处理 -- 处理就是把count[email] 置0 -- 表示把 email 都放入了新文件夹
// PS: 这里要注意的一个是抽象滑动窗口需要 -- count + deque + 额外一个变量表示窗口实际所含元素 -- 与懒更新有关
// 上述的 deque 则是与题目描述的 last K 元素有关
// 唯一等同于上滑的情况 -- 如果当时没办法处理的email 可以暂时先划过
// 如果最后的窗口有空余，之前划过的还未处理的email会填补下来 -- 没办法在遍历中途提前判断 "NO"
// 则需要有一个tmp来保存这些暂时划过的email -- 使用抽象hash滑动窗口 + deque来把队首的email 压入tmp栈(后入先出)

#include<bits/stdc++.h>
using namespace std;

int t,n,m,k;
int email[100001];
unordered_map<int, int> remain;  // email 剩余数量统计

void check(){
    int j=1, rightSize = 0;     // 右窗口能够显示的实际数量
    deque<int> right;   // 用于计算应该压入 tmp 的 email    
    vector<int> tmp;    // 保存暂时划过未处理的 email
    unordered_map<int, int> cnt;    // 统计当前队列内 email 的数量
    
    for(int head=1; head<=m; head++){  // 循环主题放在folder -- 当前folder相关的没放完不下滑 -- folder完全没有上滑的机会
        // 下移一次有新的folder, 就需要做一次检查
        if(cnt[head+k-1] > 0){
            rightSize -= cnt[head+k-1];
            remain[head+k-1] -= cnt[head+k-1];
            cnt[head+k-1] = 0;
        }
        // 只要队首 folder 还没处理完，右窗口就模拟下滚
        while(remain[head] > 0){    
            if(rightSize < k){
                if(j <= n){     // 还没滚到底
                    if(email[j] >= head && email[j] <= head+k-1) remain[email[j]]--;    // 如果刚好有folder可以放, 那就都没必要进滑动窗口了
                    else{
                        cnt[email[j]]++;
                        right.push_back(email[j]);
                        rightSize++;
                    }
                    j++;
                }
                else{   // 下滚到底了, tmp补位
                    while(rightSize < k && !tmp.empty()){
                        if(tmp.back() >= head && tmp.back() <= head+k-1){
                            remain[tmp.back()]--;
                            if(remain[head] == 0) {
                                tmp.pop_back();
                                break;    // 一旦remain[head]清0, 马上将左窗口,右边窗口先暂停更新
                            }
                        }
                        else{
                            rightSize++;
                            cnt[tmp.back()]++;
                        }
                        tmp.pop_back();
                    }

                    // 表示还有该放的email在最后的窗口之外
                    if(remain[head] != cnt[head]){   
                        cout<<"NO"<<endl;
                        return;
                    }else{
                        rightSize -= cnt[head];
                        remain[head] = 0;
                        cnt[head] = 0;
                    }
                }
            }
            else{       
                // 处理懒更新
                while(!right.empty() && cnt[right.front()] == 0) right.pop_front();    

                // 当前窗口已经没有能够处理的email -- 应该暂时先下滑一格了
                if(!right.empty()){     
                    tmp.push_back(right.front());
                    cnt[right.front()]--;
                    right.pop_front();
                    rightSize--;
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
        check();
    }
}