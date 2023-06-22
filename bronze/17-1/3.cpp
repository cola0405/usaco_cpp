#include <iostream>
#include <vector>
using namespace std;

const bool TIPPED = true;

void use(int a, int b, vector<vector<bool>>& cows){
    for(int i=0; i<=a; i++){
        for(int j=0; j<=b; j++){
            cows[i][j] = !cows[i][j];
        }
    }
}


int main(){
    freopen("cowtip.in", "r", stdin);
    freopen("cowtip.out", "w", stdout);

    int n;
    cin>>n;

    vector<vector<bool>> cows(n, vector<bool>(n));
    for(int i=0; i<n; i++){
        string row;
        cin>>row;
        for(int j=0; j<n; j++){
            cows[i][j] = (row[j]=='1');
        }
    }

    int count = 0;
    for(int i=n-1; i>=0; i--){
        for(int j=n-1; j>=0; j--){
            if(cows[i][j] == TIPPED){
                use(i, j, cows);
                count++;
            }
        }
    }

    cout<<count<<endl;
}