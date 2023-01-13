#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main(){

    freopen("cowroute.in", "r", stdin);
    freopen("cowroute.out", "w", stdout);

    int A,B,N;
    cin>>A>>B>>N;

    // find best way
    int minCost = INT_MAX;

    for(int r=0; r<N; r++){
        int cost, num;
        cin>>cost>>num;
        vector<int> cities(num);
        for(int w=0; w<num; w++){
            cin>>cities[w];
        }

        // find A_inx and B_inx
        int A_inx = find(cities.begin(), cities.end(), A) - cities.begin();
        int B_inx = find(cities.begin(), cities.end(), B) - cities.begin();
        if(A_inx == num or B_inx == num){
            continue;
        }

        if(A_inx < B_inx){
            minCost = min(cost, minCost);
        }
    }

    if(minCost == INT_MAX){
        cout<<-1<<endl;
        return 0;
    }
    cout<<minCost<<endl;
}