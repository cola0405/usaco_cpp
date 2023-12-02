// 转化问题，找两个不相交且和最大的滑动窗口
// 用笨办法，双重循环+剪枝

#include<bits/stdc++.h>
using namespace std;

int n,k;
vector<int> d;
vector<vector<int>> interval;

void windowSlide(){
	int i=0, j=1;
	int left=0, right=0, amount=0;

	while(i<=j && j<d.size()){
		int diff = d[j] - d[i];
		if(diff > k){
			i++;
			continue;
		}
		interval.push_back({i,j,j-i+1});
		j++;
	}
}

bool cmp(vector<int> &v1, vector<int> &v2){
	return v1[2] > v2[2];  // 大于，从大到小
}

int main(){
	freopen("diamond.in", "r", stdin);
	freopen("diamond.out", "w", stdout);
	
	cin>>n>>k;
	for(int i=0; i<n; i++){
		int size;
		cin>>size;
		d.push_back(size);
	}
	sort(d.begin(), d.end());
	
	windowSlide();
	sort(interval.begin(), interval.end(), cmp);
	int ans = 0;
	for(int i=0; i<interval.size(); i++){
		for(int j=i+1; j<interval.size(); j++){
			int left1 = interval[i][0];
			int right1 = interval[i][1];

			int left2 = interval[j][0];
			int right2 = interval[j][1];

			if(max(left1, left2) > min(right1, right2)){
				ans = max(ans, interval[i][2] + interval[j][2]);
				break;  // 虽然是双重循环，但是可以剪枝，找到一个就不往下
			}
		}
	}

	cout<<ans<<endl;
}
