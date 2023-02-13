#include <iostream>
#include <vector>

using namespace std;

int N;
vector<string> characteristics[25];
vector<string> all_characteristics;

bool crossing(int a, int b){
    int A=0, B=0, AB=0;
    for(int i=0; i<N; i++){
        vector<string> &v = characteristics[i];
        bool has_a = false, has_b = false;
        for(int j=0; j<v.size(); j++){
            // 遍历所有节点
            if(v[j] == all_characteristics[a]) has_a = true;
            if(v[j] == all_characteristics[b]) has_b = true;
        }
        if(has_a && has_b) AB++;
        else if (has_a) A++;
        else if (has_b) B++;
    }
    // 就是AB相交的情况
    return AB>0 && A>0 && B>0;
}



int main(){

    freopen("evolution.in", "r", stdin);
    freopen("evolution.out", "w", stdout);

    cin>>N;
    for(int r=0; r<N; r++){
        int k;
        cin>>k;

        for(int i=0; i<k; i++){
            string s;
            cin>>s;
            characteristics[r].push_back(s);
            bool found = false;
            for(int j=0; j<all_characteristics.size();j++){
                if(all_characteristics[j] == s){
                    found = true;
                }
            }
            if(!found){
                all_characteristics.push_back(s);
            }
        }
    }

    int M = all_characteristics.size();
    bool ok = true;
    for(int a=0; a<M; a++){
        for(int b=a+1; b<M; b++){
            // 是否有相交的集合
            if(crossing(a,b)){
                ok = false;
            }
        }
    }
    if(ok) cout<<"yes"<<endl;
    else cout<<"no"<<endl;
    return 0;
}