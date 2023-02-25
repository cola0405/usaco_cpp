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

bool is_possible(string word){
    for(auto letters : letters_set){
        if(exist(word, letters)){
            return true;
        }
    }
    return false;
}


int main()
{
    vector<string> s{".*", "**"};
    s[0][0] = '+';
    for(auto line : s){
        cout<<line<<endl;
    }

}