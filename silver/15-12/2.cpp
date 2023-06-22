#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("highcard.in", "r", stdin);
    freopen("highcard.out", "w", stdout);

    // build elsie
    int n;
    vector<int> elsie;
    cin>>n;
    for(int i=0; i<n; i++){
        int tmp;
        cin>>tmp;
        elsie.push_back(tmp);
    }
    sort(elsie.begin(), elsie.end());

    // build bessie
    vector<int> bessie;
    int j=0;
    for(int card=1; card<=2*n; card++){
        if(elsie[j] != card){
            bessie.push_back(card);
        }else j++;
    }
    
    // greedy compare
    int ans=0, i=0;     // i poiner for elsie
    j=0;                // j pointer for bessie
    while(i<n && j<n){
        if(bessie[j]>elsie[i]){
            ans++;
            i++;
        }
        j++;
    }
    cout<<ans<<endl;
    return 0;
}