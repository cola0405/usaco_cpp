#include<bits/stdc++.h>
#define rotate(x) (((x&1)<<(n-1))|(x>>1)) //获取 x 的循环右移 1 位的值
using namespace std;
int t,n,k;
bitset<1050000> dp[62];
inline int get(int x,int l,int s){//复杂的处理逻辑，给循环意义下长度为l的区间按位异或，左端点为第s位
	l%=(n*2);//2n的长度会让每个位被翻转两次，直接取模
	if(l>=n){
		l-=n;
		x^=((1<<n)-1);
	}
	if(l==0)return x;
	int r=s+l-1;
	x^=(((1<<(min(r,n-1)-s+1))-1)<<s);
	if(r>=n){
		x^=((1<<(r-n+1))-1);
	}
	return x;
}
void init(){
	dp[0][0]=1;
	for(k=0;k<=n;k++){
//		cerr<<k<<'\n';
//		total|=dp[k];
//		if(total.count()==(1<<n))break;
		for(int i=0;i<(1<<n);i++)if(dp[k][i]){
//			cerr<<k<<' '<<i<<'\n';
			for(int j=0;j<n;j++){
				dp[k+1][get(i,k+1,j)]=1;
			}
		}
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
//	freopen("data.txt","r",stdin);
//	freopen("ans.txt","w",stdout);
	cin>>t>>n;
	init();
	while(t--){
		string s1,s2;
		cin>>s1>>s2;
		int x=0,y=0;
		for(char i:s1)x=(x<<1)|(i&1);
		for(char i:s2)y=(y<<1)|(i&1);
//		cout<<x<<' '<<y<<'\n';
		int ans=-1;
		for(int i=0;i<=k;i++){
//			cout<<i<<' '<<x<<' '<<y<<'\n';
			if(dp[i][x]){
				ans=i;
				break;
			}
			x^=y;
			y=rotate(y);
		}
		cout<<ans<<'\n';
	}

	return 0;
}
