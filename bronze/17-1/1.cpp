#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    freopen("notlast.in","r",stdin);
    freopen("notlast.out","w",stdout);

    int n;
    cin>>n;

    vector<string> cows{"Bessie", "Elsie", "Daisy", "Gertie", "Annabelle", "Maggie", "Henrietta"};
    std::map<string, int> log;
    for(auto & name : cows){
        log[name] = 0;
    }
    
    // init log
    string name;
    int milk;
    for(int i=0; i<n; i++){
        cin>>name>>milk;
        log[name] += milk;
    }

    // sort the milks
    vector<int> milks;
    for(auto iter=log.begin(); iter!=log.end(); iter++){
        milks.push_back(iter->second);
    }

    sort(milks.begin(), milks.end());

    int i=1;
    while(i<7 && milks[i]==milks[i-1]){
        i++;
    }
    
    // Ps:there got 2 situation should output "Tie"
    if(i == 7){
        cout<<"Tie"<<endl;
        return 0;
    }

    // find min2, then count the min2
    int min2 = milks[i];
    int count = 0;
    string cow;
    for(auto iter=log.begin(); iter!=log.end();iter++){
        if(iter->second == min2){
            count++;
            cow = iter->first;
        }
    }

    // output the ans
    if(count > 1){
        cout<<"Tie"<<endl;
    }else{
        cout<<cow<<endl;
    }
}