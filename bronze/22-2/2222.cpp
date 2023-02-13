#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[110000];
    int b[110000];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(int i=0; i<n; i++){
        cin>>b[i];
    }

    int ans=0;
    int i=0, j=0;

    // 不实际做insert，而是放入abandon，表示已经insert到正确位置
    set<int> abandon;

    // 对b序列进行贪心，所以以j作为循环的条件
    while(j<n){
        // 如果a[i]在abandon中，则表示a[i]在之前已经被insert提到前面，所以跳过
        if(abandon.find(a[i]) != abandon.end()){
            i++;
            continue;
        }
        // 贪心的思维是：一旦发现对应位置不相等，则直接从a队列后面把需要的cow给提过来
        // 这里要注意的是交换的规则，并不是前后两头牛交换位置哦，而是做insert操作
        if(a[i]!=b[j]){
            abandon.insert(b[j]);
            ans++;
        }else i++;
        j++;
    }
    cout<<ans<<endl;
}