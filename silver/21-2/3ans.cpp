#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,a[505][505],l[505][505],r[505][505],minl[505][505],minr[505][505];
ll ans;
bool v[505][505];
int main()
{
    freopen("3.in", "r", stdin);
	n=read();
	for(R int i=1;i<=n;++i)
		for(R int j=1;j<=n;++j)
		{
			a[i][j]=read();
			if(a[i][j]==100)
				a[i][j]=1;
			else if(a[i][j]<100)
				a[i][j]=0;
			else
				a[i][j]=2;
		}
	for(R int j=1;j<=n;++j)
	{
		for(R int i=1;i<=n;++i)
			for(R int k=1;k<=n;++k)
				if(a[i][k])
					l[i][k]=l[i][k-1]+1;
		for(R int i=1;i<=n;++i)
			for(R int k=n;k;--k)
				if(a[i][k])
					r[i][k]=r[i][k+1]+1;
		for(R int k=1;k<=n;++k)
		{
			minl[k][k]=l[k][j];
			minr[k][k]=r[k][j];
			for(R int u=k+1;u<=n;++u)
			{
				minl[k][u]=min(minl[k][u-1],l[u][j]);
				minr[k][u]=min(minr[k][u-1],r[u][j]);
			}
		}
		for(R int i=1;i<=n;++i)
			if(a[i][j]==1)
			{
				for(R int k=i;k&&a[k][j];--k)
					for(R int u=i;u<=n&&a[u][j];++u)
						ans+=minr[k][u]*minl[k][u];
				a[i][j]=l[i][j]=r[i][j]=0;
			}
	}	
	putll(ans);
    return 0;
}