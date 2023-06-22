#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    freopen("square.in","r",stdin);
    freopen("square.out","w",stdout);

    int x1,y1,x2,y2;
    int x3,y3,x4,y4;

    cin>>x1>>y1>>x2>>y2;
    cin>>x3>>y3>>x4>>y4;

    int top, bottom;
    int right,left;

    top = max(y2,y4);
    bottom = min(y1,y3);
    right = max(x2,x4);
    left = min(x1,x3);

    int xGap = right - left;
    int yGap = top - bottom;

    int edge = max(xGap,yGap);
    cout << edge*edge << endl;
}