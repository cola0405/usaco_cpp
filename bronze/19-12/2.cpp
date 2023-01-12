#include <iostream>
#include <string>
#include <set>

using namespace std;
int main() {
    freopen("whereami.in","r",stdin);
    freopen("whereami.out", "w", stdout);

    int n;
    cin>>n;
    string mailboxs;
    cin>>mailboxs;

    int i, l=1;
    while(l<=n){
        set<string> s;
        for(i=0; i+l<=n; i++){
            string tmp = mailboxs.substr(i,l);
            if(s.find(tmp) != s.end()){
                break;
            }else{
                s.insert(tmp);
            }
        }
        if(i+l > n){
            cout<<l<<endl;
            return 0;
        }
        l++;
    }
}
