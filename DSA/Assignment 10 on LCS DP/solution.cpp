#include<bits/stdc++.h>
using namespace std;

string lcs(string const&a, string const&b)
{
    int dp[a.size()+1][b.size()+1];
    memset(dp, 0 , sizeof dp);

    for(int i=1;i<=a.size();i++)
    {
        for(int j=1;j<=b.size();j++)
            dp[i][j] = (a[i-1]==b[j-1] ? dp[i-1][j-1]+1 : max(dp[i][j-1] , dp[i-1][j]));
    }

    string ans="";
    int x= a.size() , y =b.size();
    while(x>0 and y>0)
    {
        if(a[x-1] == b[y-1])
            ans+=a[x-1] , x--,y-- ;
        else dp[x][y]==dp[x-1][y] ? x-- : y-- ;
    }

    assert(ans.size()==dp[a.size()][b.size()]);

    reverse(ans.begin(),ans.end());

    return ans;
}



int main()
{
    string a, b;
    cin>>a>>b;
    cout<<lcs(a,b)<<"\n";
}
