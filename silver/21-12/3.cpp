// difference

// it's impossible to try all nxn pairs
// but we notice that the M<=5000, which actually give us tips
// we can't try every pairs, but we can try every two position!

// it's easy to figure out the total pairs, but how to select the valid pairs
// for this algorithm, we can use difference algorithm, quickly modify [0,2M] -- k

// let's check out the example testcase:
// start position pairs:
// 2: (1,1)
// 3: (1,2), (2,1)

// end position pairs:
// 6: (3,3)
// 8: (3,5), (5,3)

// for 1+1 <= k <= 3+3, we need to add 1 in [2,6]
// for 1+2 <= k <= 3+5, we need to add 1 in [3,8]
// for 2+1 <= k <= 5+3, we need to add 1 in [3,8]

// all of these, can be done by following operations 
// d[i+j] += a[i]*a[j];        
// d[i+j+1] -= b[i]*b[j];
// (actually not add 1, it's multiplication by i and j)


#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
ll n,m,x,y;
int main()
{
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    cin>>n>>m;
    vector<ll> a(5001,0), b(5001,0);    // a for start position, b for end position
    vector<ll> d(2*m+10, 0);            // difference array
    for(int i=0; i<n; i++){
        cin>>x>>y;
        a[x]++, b[y]++;                 // count the number of every position
    }
    for(int i=0; i<=m; i++){
        for(int j=0; j<=m; j++){
            // for multiply, we also need to use long long
            d[i+j] += a[i]*a[j];        // i+j --> ai+aj <= k, we just add a[i]*a[j] to these k
            d[i+j+1] -= b[i]*b[j];      
        }
    }
    ll cur = 0;
    for(int i=0; i<=2*m; i++){          // resolve the difference array
        cur += d[i];
        cout<<cur<<endl;
    }
    return 0;
}
