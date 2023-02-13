#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int a,b,n;
    cin>>n;
    bool d;
    vector<vector<int> > v;
    int m=0;
    for(int i=0;i<n;i++)
    {
        int c,s;
        cin>>c>>s;
        for(int j=0;j<s;j++)
        {
            int t;
            cin>>t;
            m=max(m,t);
            v[i].push_back(t);
        }
    }
    int cost[m][m];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m)
        {
            for(int j=0;j<c;j++)
            {
                int t;
                t=
                if (t==a)
                {
                    d=1;
                }
                else if(t==b&&d==1)
                {
                    ans=min(ans,p);
                }
            }
        }
    }
}
