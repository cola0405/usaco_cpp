// ans = diff + 整环数量
// 大小写一共52个字母

// 如果回到开头，而且遍历途中不存在入度为2的节点
// 则一定是整环


#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	for(int r=0; r<n; r++){
		string src,dst;
		cin>>src>>dst;
		unordered_map<char, char> map;
		unordered_map<char, int> inDegree;
		
		int ans = 0;
		bool flag = false;
		for(int i=0; i<src.size(); i++){
			if(map.find(src[i]) != map.end() && map[src[i]] != dst[i]){
				cout<<-1<<endl;  // 检查一对多
				flag = true;
				break;
			}
			map.insert({src[i], dst[i]});  // 相等的也要插入!! 因为下面有在map.find()
		}
		
		if(flag) continue;
		unordered_set<char> after(dst.begin(), dst.end());
		if(after.size() == 52 && src != dst){  // 如果52个占满，则不可能完成replace
			cout<<-1<<endl;
			continue;
		}
		
		unordered_set<char> already;
		for(auto it: map){
			if (it.first == it.second) continue;
			// src[i] != dst[i]
			ans++;
			inDegree[it.second]++;
			
			if (already.find(it.first) != already.end()) continue;
			
			char cur = it.first;
			int cycle = 1;  // 一条线状态, 单纯的true false 已经不够表达状态量
			while (map.find(cur) != map.end()){
				if (inDegree[cur]>=2){
					cycle = -1; // 必不是环
				}
				if(already.find(cur) != already.end()) break;
				already.insert(cur);
				cur = map[cur];
				
				if (cur == it.first){  // 整环肯定会进入这，但是进入这的不一定是整环
					if (cycle != -1) cycle = 2;  // 如果途中没有入度为2的节点，则必定是环
					break;
				}
			}
			
			if(cycle == 2){
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
