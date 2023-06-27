// 遍历所有k即可，然后就是借助什么算法提高效率
// 区间求和 - 前缀和
// 这里情况特殊，可以用前缀和变量版 hhh 用total一个个减就行

#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("homework.in", "r", stdin);
    freopen("homework.out", "w", stdout);

    int n;
    cin>>n;
    vector<int> scores;
    for(int i=1; i<=n; i++){
        int score;
        cin>>score;
        scores.push_back(score);
    }
    // 建表，k+1到末尾区间内的最小值
    vector<int> lowest(n-1);
    int min_val = scores[n-1];
    for(int i=n-1; i>=0; i--){
        min_val = min(scores[i], min_val);
        lowest[i] = min_val;
    }

    int total = accumulate(scores.begin(), scores.end(),0);
    // 循环结束条件确认
    // 一开始k<=n
    // 少两个，则-1,-2
    vector<double> final_score(1);
    for(int k=1; k<=n-2; k++){
        total -= scores[k-1];
        double res = (double)(total - lowest[k]) / (n-k-1);
        final_score.push_back(res);
    }

    double max_score = *max_element(final_score.begin(), final_score.end());
    for(int k=1; k<final_score.size(); k++){
        if(final_score[k] == max_score){
            cout<<k<<endl;
        }
    }
    return 0;
}