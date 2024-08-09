#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--){
		int n,x;
		cin>>n;
		vector<int> p(n), ans;
		for(int i=0; i<n; i++) cin>>p[i];
		int i=0;
		while(i < n){
			if(i<n-1 && p[i] <= p[i+1]){
				while(i<n-1 && p[i] <= p[i+1]) i++;
				ans.push_back(p[i]);
			}
			else{
				while(i<n-1 && p[i] > p[i+1]) i++;
				ans.push_back(p[i]);
			}
		}
		for(auto x: ans) cout<<x<<" ";
		cout<<endl;
	}
	
	
	return 0;
}

