#include<iostream>
using namespace std;

class DisjSet
{
    int *Rank, *Parent,n;
public:
    DisjSet(int n):n(n)
    {
        Rank = new int [n+1];
        Parent = new int [n+1];
        for(int i=0; i<=n; i++) Parent[i]=-1 ;
    }
    void MakeSet(int x)
    {
        if(x>n)
        {
            cout<<x <<" out of range\n";
            return ;
        }
        Parent[x]=x;

        Rank[x]=0;
    }
    inline int FindSet(int x)
    {
        if(x>n) return -1;
        if(Parent[x]==-1 or Parent[x]==x) return Parent[x];
        else return Parent[x]=FindSet(Parent[x]);
    }
    void Union(int u,int v)
    {
        int x = u , y = v ;
        u=FindSet(u);
        v=FindSet(v);

        if(u==-1)
        {
            cout<<x<<" does not belong to any set\n";
            return ;
        }
        if(v==-1)
        {
            cout<<y<<" does not belong to any set\n";
            return ;
        }
        if(u!=v)
        {
            if(Rank[u] < Rank[v])
            {
                Parent[u] = v;
            }
            else if(Rank[v] < Rank[u])
            {
                Parent[v] = u;
            }
            else
            {
                Parent[u]=v;
                Rank[v]++;
            }
        }
    }
    void Print(int u)
    {
        if(FindSet(u)==-1)
        {
            cout<<u<<" does not belong to any set\n";
            return ;
        }
        for(int i=0; i<=n; i++)
            if(FindSet(u)==FindSet(i))
                cout<<" "<<i;
        cout<<"\n";
    }
};

int main()
{
    cout<<"Enter Maximum Number of Nodes\n";
    int n;
    cin>>n;
    DisjSet ds(n);
    while(1)
    {
        cout<<"1. MakeSet\n\
2. FindSet\n\
3. UnionSets\n\
4. PrintSets\n\
5. Quit\n";
        int cmd;
        cin>>cmd;

        if(cmd==1)
        {
            cout<<"Enter set number :>";
            int x;
            cin>>x;
            ds.MakeSet(x);
        }
        else if(cmd==2)
        {
            cout<<"Enter element number :>";
            int x;
            cin>>x;
            cout<<"Set "<<ds.FindSet(x) <<" have element "<<x<<endl;
        }
        else if(cmd==3)
        {
            cout<<"Enter two set number x,y :>";
            int x,y;
            cin>>x>>y;
            ds.Union(x,y);
        }
        else if(cmd==4)
        {
            cout<<"Enter element number :>";
            int x;
            cin>>x;
            ds.Print(x);
        }
        else if(cmd==5)
            break;
        else
            cout<<"Undefined Command\n";
    }
}
