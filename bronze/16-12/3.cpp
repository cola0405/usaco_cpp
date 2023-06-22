// basic string

#include <iostream>
using namespace std;
int main(){
    freopen("cowsignal.in","r",stdin);
    freopen("cowsignal.out","w",stdout);

    int m,n,k;
    cin>>m>>n>>k;

    for(int i=0; i<m; i++){
        string line;
        cin>>line;
        for(int j=0; j<k; j++){
            for(int q=0; q<n; q++){
                for(int p=0; p<k; p++){
                    cout<<line[q];
                }
            }
            cout<<endl;
        }
    }

}