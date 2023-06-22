#include <map>
#include <vector>
#include <algorithm>
#include "iostream"

using namespace std;
int main(){
    int n;
    cin>>n;
    vector<string> plus = {"NE", "ES", "SW", "WN"};
    vector<string> minus = {"NW", "WS", "SE", "EN"};

    for(int r=0; r<n; r++){
        string path;
        cin>>path;
        int angle = 0;
        for(int i=0; i+1<path.size(); i++){
            string turning = path.substr(i,2);
            if(find(plus.begin(), plus.end(), turning) != plus.end()){
                angle += 90;
            }else if(find(minus.begin(), minus.end(), turning) != minus.end()){
                angle -= 90;
            }
        }
        if(angle>0){
            cout<<"CW"<<endl;
        }else{
            cout<<"CCW"<<endl;
        }
    }
}