#include<bits/stdc++.h>
using namespace std;

int t,n,m,k;
int folder[10001], email[100001];
unordered_map<int, int> remain;  // email 剩余数量统计
unordered_map<int, int> qCnt;   // 队列内 email 统计

void check(){
    queue<int> left, right;
    for(int i=1; i<=k; i++){
        // right.push(email[i]);
        left.push(i);
    }

    int j = 1;
    int rightSize = 0;
    while(j<=n || !right.empty()){
        while(!left.empty() && remain[left.front()] == 0){  // 队首 folder 对应的 email 已经处理完则pop()
            left.pop();
            int tail = left.back()+1;
            left.push(tail);
            // 检查 right 中是否存在可投递的 email
            qCnt[tail] = 0;     // 队列中已有的对应 email 可以都投过来，所以置0
        }

        bool flag = true;
        // right push()
        while(rightSize < k && j<=n){
            if(email[j] >= left.front() && email[j] <= left.back()){
                remain[email[j]]--;
                flag = false;
            }else{
                right.push(email[j]);
                qCnt[email[j]]++;
                rightSize++;
            }
            j++;
        }

        // right 更新 -- 有pop就有push
        while(!right.empty() && qCnt[right.front()] == 0){
            remain[right.front()]--;
            right.pop();
            rightSize--;
            flag = false;
        }
        if(flag && rightSize > 0){   // 非空且处理不掉
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
}

int main(){
    freopen("3.in", "r", stdin);
    freopen("3.out", "w", stdout);

    cin>>t;
    // for(int r=0; r<=10000; r++) folder[r] = r;
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