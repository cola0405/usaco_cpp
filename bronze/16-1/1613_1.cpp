#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
int main(){

    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    vector<vector<int>> farm(3000, vector<int>(3000, -1));
    int x=1500, y=1500;
    int n, time=1;
    farm[x][y] = 0;
    cin>>n;

    int ans = INT_MAX;
    for(int i=0; i<n; i++){
        char direction;
        int distance;
        cin>>direction>>distance;

        if(direction == 'N'){
            while(distance>0){
                x -= 1;
                if(farm[x][y] != -1){
                    ans = min(time - farm[x][y], ans);
                }
                farm[x][y] = time;
                time++;
                distance--;
            }
        }else if(direction == 'S'){
            while(distance>0){
                x += 1;
                if(farm[x][y] != -1){
                    ans = min(time - farm[x][y], ans);
                }
                farm[x][y] = time;
                time++;
                distance--;
            }
        }else if(direction == 'W'){
            while(distance>0){
                y -= 1;
                if(farm[x][y] != -1){
                    ans = min(time - farm[x][y], ans);
                }
                farm[x][y] = time;
                time++;
                distance--;
            }
        }else if(direction == 'E'){
            while(distance>0){
                y += 1;
                if(farm[x][y] != -1){
                    ans = min(time - farm[x][y], ans);
                }
                farm[x][y] = time;
                time++;
                distance--;
            }
        }
    }
    if(ans != INT_MAX){
        cout<<ans<<endl;
    }else{
        cout<<-1<<endl;
    }



}