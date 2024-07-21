#include <iostream>
#include <vector>
using namespace std;

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
    string row;
    cin>>n;
    vector<vector<bool>> cows(n, vector<bool>(n));
    for(int i=0; i<n; i++){
        cin>>row;
        for(int j=0; j<n; j++){
            cows[i][j] = (row[j]=='1');
        }
    }

    int cnt = 0;
    for(int i=n-1; i>=0; i--){       // from right-bottom to left-top
        for(int j=n-1; j>=0; j--){
            if(cows[i][j] == 1){    // turn all '1' to '0'
                use(i, j, cows);
                cnt++;
            }
        }
    }
    cout<<cnt<<endl;
}