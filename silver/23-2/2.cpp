// 数学题

// 要注意的是，题目用的是欧几里得距离 -- 可斜着走（题目没说曼哈顿距离，那默认就是欧几里得距离）
// (t1-t2)^2 < (x1-x2)^2 + (y1-y2)^2 则表示羊无辜

// 还有一个点 —— It will always be possible for a single cow to travel between all grazings.
// 以羊的速度移动，各个被吃的草坪之间是全连接的关系

// 有了上面的规律，就不用想尽办法求 "距离最近的现场" 了
// 只要找


#include <bits/stdc++.h>
using namespace std;

bool cmp(vector<long long> &s1, vector<long long> &s2){
	return s1[2] < s2[2];
}

int main(){
	// freopen("t.in", "r", stdin);
	
	int G,N;
	cin>>G>>N;
	
	long long x,y,t;
	vector<vector<long long>> grazings;
	for(int i=0; i<G; i++){
		cin>>x>>y>>t;
		grazings.push_back({x,y,t});
	}
	sort(grazings.begin(), grazings.end(), cmp);
	
	int ans = 0;
	for(int i=0; i<N; i++){
		long long cow_x,cow_y,cow_t;
		cin>>cow_x>>cow_y>>cow_t;
		int low = 0;
		int high = G-1;
		
		while (low<high){
			int mid = (low+high)/2;
			if (grazings[mid][2] >= cow_t) high = mid;
			else low = mid+1;
		}
		
		for(int j=low-1; j<=low; j++){
			if (j<0) continue;
			long long g_x = grazings[j][0];
			long long g_y = grazings[j][1];
			long long g_t = grazings[j][2];
			
			// 为什么用pow会有问题 -- pow返回double，表示大数时有误差
			// 1.52416e+16
			// 解决办法 -- long long乘法
			if ((cow_t-g_t)*(cow_t-g_t) < (cow_x-g_x)*(cow_x-g_x) + (cow_y-g_y)*(cow_y-g_y)){
				ans++;
				break;
			}
		}

	}
	cout<<ans<<endl;
	return 0;
}