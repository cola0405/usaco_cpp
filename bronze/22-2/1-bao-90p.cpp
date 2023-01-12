// 暴力90p
#include <iostream>
#include <vector>

using namespace std;

int main(){
    int t,n,i;
    cin>>t;
    for(int r=0; r<t; r++){
        cin>>n;
        vector<int> v(n);
        for(i=0; i<n; i++){
            cin>>v[i];
        }

        // try to find final
        // it must come from sum of the head numbers
        for(int l=1; l<=n; l++){

            int final = 0;
            for(i=0; i<l; i++){
                final += v[i];
            }

            int tmp = 0;
            int ans = 0;
            int count = 0;
            for(i=0; i<n; i++){
                tmp += v[i];
                count++;
                if(tmp == final){
                    ans += count-1;
                    tmp = 0;
                    count = 0;
                }else if(tmp > final){
                    break;
                }
            }

            if(i == n && tmp == 0){
                cout<<ans<<endl;
                break;
            }
        }

    }
}