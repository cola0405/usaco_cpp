// math + 埃氏筛 + game theory

// 都采取最优策略，那总操作次数就是固定的
// 胜者想尽可能快地结束对局，而败者则是想尽可能拖着

// 遇到a=4k，要拖时间，最优策略是-2
// 然后对方也会-2 -- 为了保持4k
// 此时，turn = a/2

// 如果a!=4k，策略则是把4k留给对手，选择减去符合4k+1, 4k+2, 4k+3 的质数p
// 此时，turn = (a-p)/2 + 1
// 这里的+1就是前面提及的减法
#include <iostream>
#include <vector>
using namespace std;

const int M = 5e6;
int t,n;
vector<int> is_prime(M+1, 1), prime, m = {0,1,2,3}, p(M+1);

void build_prime(){     // p[x] 是尽可能大的与x(mod4)同余的质数 -- 不是无脑选最大质数就行
    is_prime[1] = 0;    // 减去同余的数，留下4k给对手，例如：91-83 = 8，留给对手
    for(int i=1; i<=M; i++){
        if(is_prime[i]){
            for(int j=2; i*j<=M; j++){
                is_prime[i*j] = 0;
            }
        }
    }
    p[1] = 1;
    for(int x=2; x <= M; x++){
        if(is_prime[x]) m[x%4] = x;
        p[x] = m[x%4];
    }
}

int main()
{
    // freopen("2.in", "r", stdin);
    // freopen("2.out", "w", stdout);

    cin>>t;
    build_prime();
    while(t--){
        cin>>n;
        vector<int> a(n);
        for(int i=0; i<n; i++) cin>>a[i];
        int min_turn = 1e9, min_inx = 0;
        for(int i=0; i<n; i++){
            int turn = 1e9;
            if(a[i]%4 == 0) turn = a[i]/2;
            else turn = (a[i]-p[a[i]])/2 + 1;

            if(turn/2 < min_turn/2){    // 正式结束可能要等到下轮！考虑 turn = 5,4 的情况
                min_turn = turn;        // 即使4更小，但是到 5 就结束了
                min_inx = i;
            }
        }
        if(a[min_inx]%4 != 0) cout<<"Farmer John\n";
        else cout<<"Farmer Nhoj\n";
    }
    return 0;
}

/*
1
1
91
(FJ)

*/