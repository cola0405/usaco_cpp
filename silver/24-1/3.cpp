// congruence + math
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll max_L;
unordered_set<ll> s;

bool valid(ll l){       // O(n)
    if(l > max_L) return false;
    unordered_set<ll> t;
    for(auto x : s){
        t.insert(x%l);
        if(t.size() > 3) return false;
    }
    return true;
}

int main(){
    // freopen("3.in", "r", stdin);
    // freopen("3.out", "w", stdout);

    ll n,d;
    cin>>n;
    for(int u=0; u<n; u++) {
        cin>>d;
        s.insert(d);
    }
    max_L = *min_element(s.begin(), s.end()) / 4;       // at least 4 weeks
    if(s.size() <= 3) {
        cout<<(1+max_L)*max_L/2<<endl;
        return 0;       // if s.size() > 3, the program will keep going
    }
    vector<ll> a;
    for(auto x : s) {               
        a.push_back(x);                 
        if(a.size() == 4) break;        // correct L must be in the possible L from the first 4 elements
    }
    unordered_set<ll> L;                           // time complexity here is O(24 * sqrt(1e9))
    for(int i=0; i<4; i++){                        
        for(int j=i+1; j<4; j++){                  
            ll diff = abs(a[i]-a[j]);              // if (ai - aj) % k == 0, then ai%k == aj%k (congruence)
            for(ll k=1; k<=sqrt(diff); k++){       // which means k is a possible L
                if(diff%k == 0){
                    L.insert(k);
                    L.insert(diff/k);
                }
            }
        }
    }
    ll ans = 0;
    for(auto l : L) if(valid(l)) ans += l;      // at most push 16*v elements into L 
    cout<<ans<<endl;                            // v is the number of factors, it's really small
}                                               // you can try to calculate the factors of 1e9  -- 100