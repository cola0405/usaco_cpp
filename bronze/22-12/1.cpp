#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
	int n, temp;
    vector<int> c;
	cin>>n;
	for(int i = 0 ; i<n ; i++){
		cin>>temp;
		c.push_back(temp); 
	}
	sort(c.begin(),c.end());
	
	long long ans = 0;
	long long price = 0;
	for(int i = 0 ; i < n ;i++){
		long long fee;
		fee = (long long)c[i]*(n-i);

		if(fee > ans){
			ans = fee;
			price = c[i];
		}
	}
	
	cout<<ans<<" "<<price<<endl;
	return 0;
}