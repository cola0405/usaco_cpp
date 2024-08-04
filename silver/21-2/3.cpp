// 规范化矩阵统计

// it's a really classic problem of 2D array 
// the most important and difficult part is do the calculation correctly and avoid repeat calculation
// the key thought is following:
// for each cell, we only need to search going down!

// take this example:
// 200 100 150 300
// for "100", l=2, r=3
// so the total grid number of "100" is l*r=2*3=6

// for multirows, we just need to going down
// do the calculation when we got to a new row (of course, we need 100 included)
// 100 120 87 200
// 200 100 150 300
// 2 141 135 400
// 2 141 135 400

// for g[0][1] = 120, l=2, r=1
// but we can't add l*r to ans now, because we didn't find the "100" in current column
// going down...
// g[1][1] = 100, update l and r, l=2, r=1
// now we can add l*r to ans, ans += 2
// it's actually represent this two grids:
// ①
// | 120 |
// | 100 |

// ②
// | 100 120 |
// | 200 100 |

// (there got 2 possible choice of left)



#include <iostream>
using namespace std;

const int N = 500;
int n;
int g[N][N], l[N][N], r[N][N];      

void build_lr(){            // record max choice to left and right of each cell
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(g[i][j] < 100){
                l[i][j] = 0;
                r[i][j] = 0;
            }
            else{
                l[i][j] = 1;        // left = "0" is also a choice
                // keep this "="
                for(int k=j-1; k>=0 && g[i][k]>=100; k--) l[i][j]++;

                r[i][j] = 1;
                // delete "=" to avoid repeat calculation, only l[][] got "=" is enough
                for(int k=j+1; k<n && g[i][k]>100; k++) r[i][j]++;
           }
        }
    }
}
int main()
{
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);
    
    cin>>n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>g[i][j];
        }
    }

    build_lr();
    long long ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // going down to check valid muiltiplication
            int flag = 0;                                // flag = 0 means not meet with g[i][j] == 100 
            int l_min = l[i][j], r_min = r[i][j];       // update l_min and r_min
            for(int k=i; k<n && g[k][j] >= 100; k++){
                l_min = min(l_min, l[k][j]);
                r_min = min(r_min, r[k][j]);
                if(g[k][j] == 100) flag = 1;

                // add up only meet with g[i][j] == 100
                if(flag){                       
                    ans += l_min * r_min;
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}


/*
4
100 120 87 200
200 100 150 300
2 141 135 400
2 141 135 400
(19)

 */