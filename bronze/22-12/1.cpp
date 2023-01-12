#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
	int n;
	cin>>n;
	vector<int> c;
	
	for(int i = 0 ; i<n ; i++){
		int temp;
		cin>>temp;
		c.push_back(temp); 
	}
	
	sort(c.begin(),c.end());
	
	long long ans = 0;
	long long price_per = 0;
	for(int i = 0 ; i < n ;i++){
		long long price;
		price = (long long)c[i]*(n-i);

		if(price > ans)
		{
			ans = price;
			price_per = c[i];
		}
	}
	
	cout<<ans<<" "<<price_per<<endl;
	return 0;
}