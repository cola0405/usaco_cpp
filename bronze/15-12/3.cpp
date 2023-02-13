


#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main(){

    freopen("badmilk.in", "r", stdin);
    freopen("badmilk.out", "w", stdout);

    int n,m,d,s;
    cin>>n>>m>>d>>s;

    vector<vector<int>> drink_record;
    vector<vector<int>> sick_record;

    for(int r=0; r<d; r++){
        vector<int> line(3);
        cin>>line[0]>>line[1]>>line[2];
        drink_record.push_back(line);
    }

    set<int> bad_milk;
    for(int i=1; i<=m; i++){
        bad_milk.insert(i);
    }

    for(int r=0; r<s; r++){
        int sick_people, sick_time;
        cin>>sick_people>>sick_time;

        // possible bad milk
        set<int> psb_set, tmp;
        for(int i=0; i<d; i++){
            int people = drink_record[i][0];
            int time = drink_record[i][2];
            if(people == sick_people && time < sick_time){
                int milk_type = drink_record[i][1];
                psb_set.insert(milk_type);
            }
        }
        set_intersection(bad_milk.begin(), bad_milk.end(), psb_set.begin(), psb_set.end(), inserter(tmp, tmp.begin()));
        bad_milk = tmp;
    }

    set<int> psb_sick_people;
    for(int i=0; i<d; i++){
        int milk_type = drink_record[i][1];
        if(bad_milk.count(milk_type)>0){
            int people = drink_record[i][0];
            psb_sick_people.insert(people);
        }
    }

    cout<<psb_sick_people.size()<<endl;
}