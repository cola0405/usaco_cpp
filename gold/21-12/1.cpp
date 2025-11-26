// 太抽象了 不看了

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
const int inf=0x3f3f3f3f3f3f3f3f;
const int mod=1e9+7;
int T=1,op,n,k,ans;
int dp[maxn][2],x[maxn],y[maxn];
void solve()
{
	scanf("%lld%lld%lld",&op,&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x[i],&y[i]);
		if(op==2){
			y[i]=-y[i];
		}
	}
	x[0]=-inf;
	x[n+1]=inf;
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	int l=0;
	for(int i=1;i<=n;i++){
		while(x[i]-x[l+1]>k){
			l++;
		}
		int j=i&1;
		int p=j^1;
        // 我们定义 dp[i][0/1] 表示前 i 头牛中，
        // 未配对牛的数量为偶数（0）或奇数（1）时的最小重量和。
        // 如果当前牛 i 不配对，那么未配对牛的数量增加 1，奇偶性发生变化。
        // 所以这里用是[i][j] 然后从[p]来
		dp[i][j]=dp[l][p]+y[i];     // 不配对，有配对的也不配，因为可能会和后面的配，也可能需要为之后的状态提供转移
		if(x[i+1]-x[i-1]<=k){
			dp[i][p]=dp[l][j]+y[i];
		}
		if(x[i]-x[i-1]<=k){
			dp[i][j]=min(dp[i][j],dp[i-1][j]);
		}
		if(x[i+1]-x[i]<=k){
			dp[i][p]=min(dp[i][p],dp[i-1][p]);
		}
	}
	if(n&1){
		ans=dp[n][1];
	}
	else{
		ans=dp[n][0];
	}
	if(op==2){
		ans=-ans;
	}
	printf("%lld\n",ans);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	//scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}