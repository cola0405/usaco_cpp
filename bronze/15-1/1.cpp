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
    int minCost = INT_MAX;

    for(int i=0; i<N; i++){
        int cost, m;
        cin>>cost>>m;

        int A_index=-1, B_index=-1;
        int city;
        for(int k=0; k<m; k++){
            cin>>city;
            if(city == A){
                A_index = k;
            }else if(city == B){
                B_index = k;
            }
        }
        if((A_index != -1 && B_index != -1) && (A_index < B_index)){
            minCost = min(cost, minCost);
        }
    }

    if(minCost == INT_MAX){
        cout<<-1<<endl;
        return 0;
    }
    cout<<minCost<<endl;
}