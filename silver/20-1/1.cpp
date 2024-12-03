// priority queue + greedy

// if we want bessie get berryies as more as possible
// we have to make it as more average as possible (don't let Elise get more berries)
// because the N and Bi is just 1000, so we can try all avg number
// to find out the suitable one

#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
int n,k,ans=0;
int b[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);

    cin>>n>>k;
    for(int i=0; i<n; i++) cin>>b[i];
    sort(b, b+n, greater<int>());
    for(int x=b[0]; x>=1; x--){    // try all possible avg number
        priority_queue<int> pq;
        vector<int> v;              // record the number of berries in order to calculate the Bessie's score
        for(int i=0; i<n; i++){
            int berry = b[i];
            while(berry >= x && v.size() < k){   // take avg number as more as possible
                v.push_back(x);
                berry -= x;
            }
            pq.push(berry);
        }
        while(v.size() < k){                    // fill the empty basket with remaining berries
            v.push_back(pq.top()); pq.pop();
        }
        int bessie = 0;
        for(int i=k/2; i<k; i++) bessie += v[i];
        ans = max(ans, bessie);
    }
    cout<<ans<<endl;
    return 0;
}