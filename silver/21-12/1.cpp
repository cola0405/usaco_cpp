// priority queue + greedy + sliding window

// get sum of each segment comes from Farmer Nhoj
// in the begining, FN can win all the patches
// our target is to get as more as possible patches
// we can use priority queue to help us detemine the optimal choice

// for each segment, we can put at most 2 cows to get all tastiness in this segment
// so we just need to calculate the profit of putting 1 or 2 cows 
// put them in the priority queue to find the optimal solution

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

int k,m,n;
vector<pair<int,int>> p;    // patches
vector<int> fn;             // Farmer Nonj
priority_queue<int> pq;     // pq for greedy
queue<int> window;          // sliding window for maximal tastiness of single cow
int main()
{
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);

    cin>>k>>m>>n;
    p.resize(k);
    fn.resize(m);
    for(int i=0; i<k; i++) cin>>p[i].first>>p[i].second;
    for(int i=0; i<m; i++) cin>>fn[i];
    sort(p.begin(), p.end());
    sort(fn.begin(), fn.end());

    int i=0, j=0;
    ll seg=0;           // tastiness sum of each segment
    ll win_sum;         // sum of the slding window
    ll max_win_sum;     // max tastiness when insert single cow

    // begin
    while(j<k && p[j].first <= fn[0]) seg += p[j].second, j++;
    pq.push(seg);

    // mid
    for(int i=1; i<m; i++){
        seg=0, win_sum=0, max_win_sum=0;
        while(window.size() > 0) window.pop();

        int len = (fn[i] - fn[i-1])/2;      // size of window is fixed
        while(j<k && p[j].first <= fn[i]){
            seg += p[j].second;
            if(p[j].first <= fn[i-1] + len) {   // sliding window
                win_sum += p[j].second;
                window.push(p[j].second);
            }else if(window.size() > 0){
                win_sum -= window.front();
                window.pop();
                win_sum += p[j].second;
                window.push(p[j].second);
            }
            max_win_sum = max(max_win_sum, win_sum);
            j++;
        }
        pq.push(max_win_sum);       // use pq to sovle the problem of whether 1+1>2 ?
        pq.push(seg-max_win_sum);
    }

    // end part
    seg=0;
    while(j<k) seg += p[j].second, j++;
    pq.push(seg);

    ll ans = 0;
    while(n-- && pq.size() > 0){
        ans += pq.top();
        pq.pop();
    }
    cout<<ans<<endl;
    return 0;
}
