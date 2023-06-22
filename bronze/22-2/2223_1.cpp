#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
using namespace std;

vector<string> cubes;
bool exist(string word, string letters){
    for(auto letter : word){
        int pos = letters.find(letter);
        if( pos!= string::npos){
            letters.erase(pos, 1);
        }else{
            return false;
        }
    }
    return true;
}

vector<string> letters_set;


int main()
{
    int n;
    cin>>n;
    for(int i=0; i<4; i++){
        string cube;
        cin>>cube;
        cubes.push_back(cube);
    }

    for(int i=0; i<n; i++){
        string word;
        cin>>word;

        bool flag = false;
        for(auto a : cubes[0]){
            for(auto b : cubes[1]){
                for(auto c: cubes[2]){
                    for(auto d : cubes[3]){
                        string letters = {a,b,c,d};
                        letters_set.push_back(letters);
                        if(exist(word, letters)){
                            flag = true;
                        }
                    }
                }
            }
        }
        if(flag){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }

}