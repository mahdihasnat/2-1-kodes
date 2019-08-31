#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pii;

const int N=5;
int MAX_TIME = 1000;

struct activity
{
    int start, end, id;
    activity(int start = 0, int end = 0, int id=0): start(start), end(end), id(id)
    {
        if(this->start > this->end)
            swap(this->start, this->end);
        if(this->start ==  this->end )
            this->end++;
    }
    bool operator < (const activity &x)
    {
        if(end != x.end)
            return end<x.end;
        return start <= x.start;
    }
    friend ostream & operator << ( ostream &os,const activity &x )
    {
        return os<<x.id<<" : [ "<<x.start<<" , "<<x.end<<" )";
    }
};


activity * generate(int n)
{
    activity * a = new activity[n];
    for(int i=0; i<n; i++)
    {
        a[i]= activity(rand()%MAX_TIME, rand()%MAX_TIME, i+1);
    }
    return a;
}

void Print(activity *a, int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%3d:",a[i].id);
        for(int j=0; j<=MAX_TIME; j++)
            printf("%c",j==a[i].end ? '.' : ( j>=a[i].start and j<=a[i].end ? '#' :' '));
        printf("\n");
    }
}

vector<int> Solution(activity * a,int n) /// already sorted non-decreasing by end time
{
    vector<int > ans;
    int last = -1;
    for(int i=0; i<n; i++)
        if(a[i].start >= last)
            last=a[i].end, ans.push_back(a[i].id);
    return ans;
}

pii combine(pii a, pii b)
{
    if(a.first == b.first) return { a.first, a.second + b.second};
    return a.first< b.first ? b: a;
}

void PrintSolution(activity * a,  pii table[N+2][N+1] , int n , int * ids   , int setsize  , int i, int last )
{
    if(i==n)
    {
        for(int j=0;j<setsize ; j++ )
            cout<<ids[j]<<" ";
        cout<<"\n";
        return ;
    }
    int maxsize = table[i][last].first ;
    if(a[i].start >= a[last].end   and maxsize == table[i+1][i].first + 1 )
    {
        ids[setsize-maxsize]=a[i].id;
        PrintSolution(a,table , n, ids, setsize , i+1 , i );
    }
    if(table[i+1][last].first == maxsize)
        PrintSolution(a , table , n , ids , setsize , i+1 , last );
}


void PrintAllSolution(activity *a,int n)
{
    sort(a,a+n);


    activity *b = new activity[n+1];

    memcpy(b+1 , a , n* sizeof (activity));
    b[0] = activity(-2,-1,0);
    n++;




    pii table[N+2][N+1]; /// i ,last_i
    for(int i=0; i<n; i++)
        table[n][i]= {0,1};
    for(int i=n-1; i>=0; i--)
    {
        for(int last = 0; last <i; last++)
        {
            table[i][last] = table[i+1][last];
            if(b[i].start >= b[last].end)
            {
                pii x = table[i+1][i];
                x.first++;
                table[i][last]  = combine(table[i][last]  , x);
            }
        }
    }
    pii solution = {0,0};
    for(int i=1;i<n;i++)
        solution = combine(solution , table[i][0]);
//    DBG(solution);

    cout<<"Total Different Solutions: "<<solution.second<<"\n";

    int  * ids = new int [ solution.first];
    for(int i=1;i<n;i++) {
        if(solution.first == table[i][0].first)
            PrintSolution(b ,table , n , ids , solution.first ,i , 0  );
    }
}


int32_t main()
{
    srand(time(0));


    int n= N;
    cout<<"Number of activity ? ";
    cin>>n;
    cout<<"Maximam Time ? ";
    cin>>MAX_TIME;

    activity * a = generate(n);
    for(int i=0; i<n; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    Print(a,n);
    sort(a,a+n);
    for(int i=0; i<n; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    Print( a, n );
    vector<int > ans = Solution(a,n);
    cout<<"Maximum chosen mutually compatible activities "<< ans.size()<<"\n";
    for(int i : ans)
        cout<<i<<" ";
    cout<<"\n";
    //PrintAllSolution(a,n);
}
