#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>

using namespace std;

int main(){

    freopen("cowroute.in", "r", stdin);
    freopen("cowroute.out", "w", stdout);

    int A,B,n;
    cin>>A>>B>>n;

    int min_cost = INT_MAX;

    vector<vector<int>> routes;
    for(int i=0; i<n; i++){
        int cost, m;
        cin>>cost>>m;

        vector<int> route;
        route.push_back(cost);

        int A_index = -1, B_index = -1;
        for(int j=0; j<m; j++){
            int t;
            cin>>t;
            if(t == A){
                A_index = j;
            }else if (t == B){
                B_index = j;
            }
            route.push_back(t);
        }

        // one route check
        if((A_index != -1 && B_index != -1) && (A_index < B_index)){
            min_cost = min(cost, min_cost);
        }
        routes.push_back(route);
    }

    // two route check
    for(int i=0; i<n; i++){
        // find A
        int A_index = find(routes[i].begin()+1, routes[i].end(), B) - routes[i].begin();
        if(A_index == routes[i].size() || A_index+1 == routes[i].size()){
            continue;
        }
        // record cities after A
        set<int> landing_cities;
        for(int k=A_index+1; k<routes[i].size(); k++){
            landing_cities.insert(routes[i][k]);
        }

        for(int j=0; j<n; j++){
            int B_index = find(routes[j].begin()+1, routes[j].end(), B) - routes[j].begin();
            if(B_index == routes[j].size()) continue;
            // check cities before B
            for(int p=1; p<B_index; p++){
                if(landing_cities.find(routes[j][p]) != landing_cities.end()){
                    min_cost = min(routes[i][0] + routes[j][0], min_cost);
                    break;
                }
            }
        }
    }

    if(min_cost == INT_MAX){
        cout<<-1<<endl;
    }else{
        cout<<min_cost<<endl;
    }
}