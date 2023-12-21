// faces 数量问题 -- 欧拉公式 v-e+f=2 -- f-1 = 1+e-v 该题只要求e和v即可
// 在一个平面内，face=1 (大平面也算一个face)
// 此时若只有线段，则必有 v=e+1
// 此时有 v-e+f=2

// 一旦线段闭合，则 face=2
// 此时 v=e, 则 v-e+f=2 仍然符合

// 考虑更极限的情况, 两个闭合图形有一个公共的顶点
// 此时 face=3, v-e+f=2 其实仍然成立


#include<bits/stdc++.h>
using namespace std;

unordered_map<char, pair<int,int>> d = {{'N', {-1,0}}, {'S', {1,0}}, {'W',{0,-1}}, {'E',{0,1}}};
unordered_set<string> vertices, edges;

int main(){
    freopen("gates.in", "r", stdin);
    freopen("gates.out", "w", stdout);

    int n;
    cin>>n;
    int x=0,y=0;
    int newX, newY;
    vertices.insert(to_string(x)+" "+to_string(y));
    for(int i=0; i<n; i++){
        char c;
        cin>>c;
        newX = x + d[c].first;
        newY = y + d[c].second;
        vertices.insert(to_string(newX)+" "+to_string(newY));
        if(c == 'N' || c == 'S'){   // 避免 edge 重复
            edges.insert(to_string(min(x,newX))+" "+to_string(max(x,newX))+"-"+to_string(y));
        }else{
            edges.insert(to_string(x)+"-"+to_string(min(y,newY))+" "+to_string(max(y,newY)));
        }
        x = newX;
        y = newY;
    }

    cout<<1+(edges.size()-vertices.size())<<endl;
}