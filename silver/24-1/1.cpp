// greedy + prefix + compression
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int t,a,j;
    vector<int> seq = {-1};     // -1 used for offset
    vector<int> h;
    int n,q,c;
    cin>>n>>q>>c;
    for(int u=1; u<=n; u++){
        cin>>t;
        seq.push_back(t);
    }
    h.resize(n+1);
    for(int u=0; u<q; u++){
        cin>>a>>j;
        h[a] = j;   // only a is distinct, j could be repeated
    }
    vector<int> origin(seq);    // copy the origin seq
    for(int u=1; u<=n; u++){
        if(seq[u] == 0) seq[u] = 1;
    }
    // optimize the interval to reduce the time complexity
    for(int a=1; a<=n; a++){
        for(int j=a+1; j<h[a]; j++){   // the interval between a and h[a]
            if(h[j] != 0 && h[j] != h[a]){      
                cout<<-1<<endl;     // the restrictions are in conflict
                return;
            }
            h[j] = h[a];
        }
    }

    // loop through the sequence 
    int pre_max = 0, after_max = 0;
    int i = 1;
    while(i<=n){
        pre_max = max(pre_max, seq[i]);     // update before the "continue"
        after_max = max(after_max, seq[i]);
        if(h[i] == 0){
            i++;
            continue;
        }
        for(int j=i+1; j<h[i]; j++){    // the time complexiy is still O(n) -- this while loop is jumping
            after_max = max(after_max, seq[j]);
        }
        if(after_max > pre_max){    // try to find a slot to assign after_max
            bool flag = true;
            for(int j=i; j>=1; j--){
                if(h[j] != 0 && h[j] < h[i]){
                    // if j comes to here (before a) which means no available slot
                    // because we can't use the slot in the previous block
                    cout<<-1<<endl;
                    return;
                }
                if(origin[j] == 0){
                    seq[j] = after_max;
                    pre_max = after_max;
                    flag = false;
                    break;
                }
            }
            if(flag){   // can't find a slot to assign after_max
                cout<<-1<<endl;
                return;
            }
        }
        if(origin[h[i]] == 0){      // if h[i] is a slot, it can't be 1
            seq[h[i]] = pre_max+1;
        }
        if(seq[h[i]] > c || pre_max >= seq[h[i]]){
            cout<<-1<<endl;     
            return;
        }
        // time complexity O(n)
        // the overlap intervals could be merged to one block
        i = h[i];     
    }

    for(int i=1; i<n; i++) cout<<seq[i]<<' ';
    cout<<seq[n]<<endl;
}

int main(){
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);

    int T;
    cin>>T;
    while(T){
        solve();
        T--;
    }
}