#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e3+100;
int n,A,B,f[N][N],dp[N][N];
struct node{int val,w,x,cost;}a[N];
bool cmp(node aa,node bb){return aa.x<bb.x;}
signed main(){
    // 读取输入
    cin>>n>>A>>B;
    for(int i=1;i<=n;i++) {
        // 读取每个朋友的受欢迎度、需要的金钱和每 x 个冰淇淋可优惠 1 块钱的条件
        scanf("%lld%lld%lld",&a[i].val,&a[i].w,&a[i].x);
        // 计算用冰淇淋完全收买该朋友所需的冰淇淋数量
        a[i].cost=a[i].w*a[i].x;
    }
    // 按 x 值升序排序
    sort(a+1,a+1+n,cmp);

    // 前缀 DP：计算前 i 个人用 j 个冰淇淋完全收买的最大受欢迎度
    for(int i=1;i<=n;i++){
        // 不选第 i 个人的情况
        for(int j=0;j<=B;j++) f[i][j]=f[i-1][j];
        // 选第 i 个人的情况
        for(int j=B;j>=a[i].cost;j--) {
            f[i][j]=max(f[i][j],f[i-1][j-a[i].cost]+a[i].val);
        }
    }

    // 后缀 DP：计算后 i 个人用 j 块钱完全收买的最大受欢迎度
    for(int i=n;i>=1;i--){
        // 不选第 i 个人的情况
        for(int j=0;j<=A;j++) dp[i][j]=dp[i+1][j];
        // 选第 i 个人的情况
        for(int j=A;j>=a[i].w;j--) {
            dp[i][j]=max(dp[i][j],dp[i+1][j-a[i].w]+a[i].val);
        }
    }

    int ans=0;
    // 枚举混合收买的人
    for(int i=1;i<=n;i++){
        // 不选第 i 个人的情况
        ans=max(ans,f[i][B]+dp[i+1][A]);
        // 选第 i 个人但只用金钱或只用冰淇淋的情况
        ans=max(ans,f[i-1][B]+dp[i][A]);
        // 枚举对第 i 个人优惠的金额
        for(int j=1;j*a[i].x<=min(B,a[i].cost);j++){ 
            if(A-a[i].w+j<0) continue;
            ans=max(ans,f[i-1][B-j*a[i].x]+dp[i+1][A-a[i].w+j]+a[i].val);
        }
    }
    // 输出最大受欢迎度
    cout<<ans;
}