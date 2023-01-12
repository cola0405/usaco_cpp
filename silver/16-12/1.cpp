#include<bits/stdc++.h>
using namespace std;

int main() {
	freopen("haybales.in", "r", stdin);
	
	int bale_num;
	int query_num;
	cin >> bale_num >> query_num;
	vector<int> haybales(bale_num);
	for (int i = 0; i < bale_num; i++) {
		cin >> haybales[i];
	}
	
	sort(haybales.begin(), haybales.end());

	freopen("haybales.out", "w", stdout);
	for (int i = 0; i < query_num; i++) {
		int start, end;
		cin >> start >> end;

		auto left = lower_bound(haybales.begin(), haybales.end(), start);
		auto right = upper_bound(haybales.begin(), haybales.end(), end);
		
		cout << right - left << '\n';
	}
}