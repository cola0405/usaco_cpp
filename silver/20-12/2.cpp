// 2D-array + lr-optimization

// ---> (y)
// |
// v (x)

// we select every two poionts as a pair of parallel lines (all x and y is distinct)
// (xi,yi) (xj,yj), assuming yi < yj
// in the range of (xi, xj), it's look liks this:
//        --------- xi
//      ·                ·
//   ·                      ·
//        --------- xj
// so we can calculate the number of points on the left of i and the points on the right of j
// then the valid subsets is l[i] * r[j]
// ps: we only concern the points between xi and xj

// avoid we miss some pairs, we can't do this
// for(int i=0; i<n; i++){
//     for(int j=i+1; j<n; j++){
//         ...
//     }
// }

// in that way, the previous points will not contribute to the future in l[j] or r[j]
// (just draw a testcase and you will understand)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 2500;
int n;
vector<pair<int,int>> c;
vector<int> l(N, 1), r(N, 1);       // record the number of points on the left and right ("1" means including itself)
int main()
{
    // freopen("2.in", "r", stdin);

    cin>>n;
    for(int i=0; i<n; i++){
        int a,b;
        cin>>a>>b;
        c.push_back(make_pair(a,b));
    }
    sort(c.begin(), c.end());
    
    long long ans = n;      // record the number of valid subset, n points is also the valid subset
    for(int i=0; i<n; i++){
        ll left=1, right=1;     // i itself
        for(int j=i-1; j>=0; j--){              // we have to loop in this way to do the valid record for l[] and r[]
            if(c[i].second < c[j].second){      // if j is on the right of i
                ans += left * r[j];
                l[j]++;
                right++;
            }
            else{
                ans += right * l[j];
                r[j]++;
                left++;
            }
        }
    }   
    cout<<ans + 1<<endl;    // empty subset + 1
    return 0;
}
