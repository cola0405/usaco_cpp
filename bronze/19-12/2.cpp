#include <iostream>
#include <string>
#include <set>
using namespace std;

int n;
string mailboxs;

bool ok(int len){
    set<string> s;
    for(int i=0; i+len<=n; i++){
        string sub = mailboxs.substr(i,len);
        if(s.find(sub) != s.end()) return false;
        else s.insert(sub);
    }
    return true;        // every subsequence is unique
}

int main() {
    freopen("whereami.in","r",stdin);
    freopen("whereami.out", "w", stdout);

    int i,k=1;
    cin>>n>>mailboxs;
    for(int k=1; k<n; k++){
        if(ok(k)){          // check the current length is valid or not
            cout<<k<<endl;
            return 0;
        }
    }
    cout<<n<<endl;
}
