// 需要快速知道dict中的最大值 -- set
// set 是有序的，默认从小到大
// 需要快速知道最大值的数量 -- 额外再建一个dict来记录

// 题目说了 FJ 每天只能测一次，所以不用担心一天多变的情况

// 测试用例11，只有一只牛，但仍然需要更新一次的解释如下：
// log 中只是记录了有变化的牛，并不是说 FJ 只有一头牛
// 所以当那一头牛产量升的时候，确实需要修改一次


#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("measurement.in", "r", stdin);
	freopen("measurement.out", "w", stdout);
	
	int n,g;
	cin>>n>>g;
	vector<vector<int>> log;
	unordered_map<int, int> produce;
	set<int, greater<int>> rank;
	unordered_map<int, int> count;
	for(int i=0; i<n; i++){
		int day, cow, change;
		cin>>day>>cow>>change;
		
		log.push_back({day, cow, change});
		produce[cow] = g;
	}
	for(auto it : produce) count[g]++;

	rank.insert(g);
	sort(log.begin(), log.end());
	
	int ans = 0;
	for(auto l: log){
		int day = l[0], cow = l[1], change = l[2];
		int top = *rank.begin();
		int old = produce[cow];
			count[old]--;
			if(count[old] <= 0){  
				rank.erase(old);	// 维护rank
			}
			produce[cow] += change;
			count[produce[cow]]++;
			rank.insert(produce[cow]);  // 更新最大值

		if(change > 0){
			if(produce[cow] == *rank.begin()) {
				if(old == top && count[old] <= 0);  // 自己仍然是top
				else{
					ans++;
				}
			}
			
		}else if(change < 0){
			if(old == top) {
				if(produce[cow] == *rank.begin() && count[*rank.begin()] == 1);  // 自己仍然是top
				else{
					ans++;
				}
			}
		}
	}
	
	cout<<max(ans, 1)<<endl; // 为了处理log中只有一只牛的情况
	return 0;
}
