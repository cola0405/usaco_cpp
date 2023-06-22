// xGap和yGap都为负数时，会负负得正的

#include<iostream>
using namespace std;

int tx1,ty1,tx2,ty2;
int getArea(int px1, int py1, int px2, int py2){
    int minTop,maxBtm;
    int minRight,maxLeft;
    int xGap,yGap;
    int area = (py2-py1)*(px2-px1);

    minTop = min(ty2, py2);
    maxBtm = max(ty1, py1);
    minRight = min(tx2, px2);
    maxLeft = max(tx1, px1);

    yGap = minTop-maxBtm;
    xGap = minRight-maxLeft;

    if(yGap>0 && xGap>0){
        area -= yGap*xGap;
    }
    return area;
}

int main(){
    freopen("billboard.in","r",stdin);
    freopen("billboard.out","w",stdout);

    int px1,py1,px2,py2;
    int px3,py3,px4,py4;
    
    cin>>px1>>py1>>px2>>py2;
    cin>>px3>>py3>>px4>>py4;
    cin>>tx1>>ty1>>tx2>>ty2;

    int area1 = getArea(px1,py1,px2,py2);
    int area2 = getArea(px3,py3,px4,py4);
    cout<<area1+area2<<endl;
}