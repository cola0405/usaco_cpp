// 初步分析是贪心问题
// 又题目要求最大值，故不是任一rest都吃
// 而是可以积累起来，到收益最大的地方吃 -- 单调栈


#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("reststops.in", "r", stdin);
	freopen("reststops.out", "w", stdout);
	
	int l,n,f,b;
	cin>>l>>n>>f>>b;
	int pos, t;
	vector<vector<int>> rest;
	vector<vector<int>> stack;
	for(int i=0; i<n; i++){
		cin>>pos>>t;
		rest.push_back({pos, t});
		
		while(stack.size()>0 && t > stack[stack.size()-1][1]){
			stack.pop_back();
		}
		stack.push_back({pos, t});
	}
	sort(rest.begin(), rest.end());
	
	int speedGap = f-b;
	int timeGap = 0;
	int cur = 0;
	int ans = 0;
	int top = 0;
	
	for(auto it: rest){
		pos = it[0];
		t = it[1];
		
		timeGap += (pos-cur) * speedGap;
		if(pos == stack[top][0]){
			ans += timeGap*t;
			timeGap = 0;
			top += 1;
		}
		cur = pos;
	}
	
	cout<<ans<<endl;
	
}
