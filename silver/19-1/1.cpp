#include <bits/stdc++.h>
using namespace std;

int n;
int a,b;
int main(){
    freopen("planting.in","r",stdin);
    freopen("planting.out","w",stdout);
    
    cin>>n;
    vector<int> in_degree(n, 0);
    for(int i=0; i<n; i++){
        cin>>a>>b;
        in_degree[a]++;
        in_degree[b]++;
    }
    cout << *max_element(in_degree.begin(), in_degree.end())+1 << endl;
}