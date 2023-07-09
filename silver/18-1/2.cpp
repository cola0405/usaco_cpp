// 求最大利润
// 二分不行，多半是贪心了
// 那就是对 "卖牛奶" 和 "租奶牛" 进行贪心
// 排序+比较贪心即可
// 当前牛哪一项收益更高就选哪一项 -- 独立性成立，不影响全局最优解

// python 解法更激进
// 贪心策略是 -- 肯定产奶量高的奶牛拿去卖奶，低的拿去租
// 排序，然后前n头牛拿去卖奶，后面的拿去租
// 枚举所有情况，取最大利润（可以前缀和优化效率）

#include <bits/stdc++.h>
using namespace std;

bool cmp(const vector<int>& s1, const vector<int>& s2){
    return s1[0] > s2[0];
}

int get_profit(int i, int k, vector<int>& milk, vector<vector<int>>& store){
    int available = milk[i];
    int profit=0;
    while(available>0 && k<store.size()){
        if(available>=store[k][1]){
            available -= store[k][1];
            profit += store[k][1]*store[k][0];
            k++;
        }else{
            profit += available*store[k][0];
            available = 0;
        }
    }
    return profit;
}

int update_store(int i, int k, vector<int>& milk, vector<vector<int>>& store){
    int available = milk[i];
    while(available>0 && k<store.size()){
        if(available>=store[k][1]){
            available -= store[k][1];
            store[k][1] = 0;
            k++;
        }else{
            store[k][1] -= available;
            available = 0;
        }
    }
    return k;
}

int main(){
    freopen("rental.in", "r", stdin);
    freopen("rental.out", "w", stdout);

    int n,m,r;
    cin>>n>>m>>r;
    vector<int> milk(n);
    for(int i=0; i<n; i++)cin>>milk[i];
    vector<vector<int>> store;
    for(int i=0; i<m; i++){
        int amount,price;
        cin>>amount>>price;
        store.push_back({price, amount});
    }
    vector<int> rent(r);
    for(int i=0; i<r; i++)cin>>rent[i];

    // sort for greedy
    sort(milk.begin(), milk.end(), greater<int>());
    sort(store.begin(), store.end(), cmp);
    sort(rent.begin(), rent.end(), greater<int>());

    // greedy
    int i=0, j=milk.size()-1;  // i -- high price, j -- low price
    int k=0,l=0;  // k -- store, l -- rent
    long long max_profit = 0;
    while(i<=j && k<store.size() && l<rent.size()){
        int price = store[i][0], need = store[i][1];

        int to_sell = get_profit(i,k,milk,store);
        int to_rent = rent[l];

        if(to_sell>=to_rent){
            max_profit += to_sell;
            k = update_store(i,k,milk,store);  //更新k
            i++;
        }else{
            max_profit += to_rent;
            l++;
            j--;
        }
    }
    
    // 处理store或rent提前空了
    while(i<=j && l<rent.size()){
        max_profit += rent[l];
        l++;
        i++;
    }
    while(i<=j && k<store.size()){
        int to_sell = get_profit(i,k,milk,store);
        max_profit += to_sell;
        k = update_store(i,k,milk,store);  //更新k
        i++;
    } 
    cout<<max_profit<<endl;
    return 0;
}