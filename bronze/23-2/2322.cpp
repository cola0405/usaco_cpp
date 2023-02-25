#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

vector<string> rotate_90(vector<string> s){
    vector<string> res;
    int k = s.size();
    for(int i=0; i<k; i++){
        string t(k, ' ');
        res.push_back(t);
    }

    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            res[j][k-1-i] = s[i][j];
        }
    }

    return res;
}

int N;
int K;
void draw(vector<string>& canvas, vector<string>& stamp , int i, int j){
    bool flag;
    for(int di=0; di<K; di++){
        flag = true;
        for(int dj=0; dj<K; dj++){
            if(stamp[di][dj] == '*' && canvas[i+di][j+dj] == '.'){
                flag = false;
                break;
            }
        }
        if(!flag)break;
    }
    if(flag){
        for(int di=0; di<K; di++){
            for(int dj=0; dj<K; dj++){
                if(canvas[i+di][j+dj] == '*' && stamp[di][dj] == '*'){
                    canvas[i+di][j+dj] = '!';
                }
            }
        }
    }


}


int main(){
    int T;
    cin>>T;

    for(int r=0; r<T; r++){
        cin>>N;

        string line;
        vector<string> canvas;
        int correct_amount = 0;
        for(int i=0; i<N; i++){
            cin>>line;
            canvas.push_back(line);
            correct_amount += count(line.begin(), line.end(), '*');
        }

        cin>>K;
        vector<string> stamp;
        for(int i=0; i<K; i++){
            cin>>line;
            stamp.push_back(line);
        }

        // get all stamp
        vector<vector<string>> stamps;
        stamps.push_back(stamp);

        for(int i=0; i<3; i++){
            vector<string> res = rotate_90(stamps.at(stamps.size()-1));
            stamps.push_back(res);
        }


        // try all stamp
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(i+K>N || j+K>N) continue;

                for(auto stamp : stamps){
                    draw(canvas, stamp, i, j);
                }
            }
        }

        int amount = 0;
        for(auto line : canvas){
            amount += count(line.begin(), line.end(), '!');
        }
        if(amount == correct_amount){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
}