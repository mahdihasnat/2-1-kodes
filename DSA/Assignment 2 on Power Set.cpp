#include<time.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<windows.h>
#include<assert.h>
using namespace std;


double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}
string getset(const  string &s,const long long &mask)
{
    string ret="";
    for(int i=0; i<s.size(); i++)
        if(mask&(1<<i))
            ret.push_back(s[i]);
    return ret;
}

vector<string >  power_set(const string &s)
{
    int n=s.size();
    long long  upto= 1LL<<n;
    vector<string > ret;
    for(long long  i=0; i<upto; i++)
    {
        ;
        //ret.push_back(getset(s,i));
    }
    return ret;
}
const int TOTALELEMENT=62;
char get_element(int i)
{
    if(i<10)
        return '0'+i;
    if((i-=10) < 26)
        return 'a'+i;
    else
        return 'A'+i-26;

}
int get_index(char c)
{
    if(c<='9') return c-'0';
    if(c<='Z') return 10+26+c-'A';
    return 10+c-'a';
}
string generate_set(int n)
{
    string s;
    int t=TOTALELEMENT/n;
    int now=rand()%t;
    s.push_back(get_element(now));
    for(int i=1; i<n; i++)
        s.push_back(get_element(now+=(rand()%t)+1));
    return s;
}
string generate_list(int n)
{
    string s;
    while(n--)
        s.push_back(get_element(rand()%TOTALELEMENT));
    return s;
}
string make_set(string arr)
{
    long long mask=0;
    for(char c : arr) mask^=1LL<<get_index(c);
    string s="";
    for(int i=0;i<TOTALELEMENT;i++)
        if(mask&(1LL<<i)) s.push_back(get_element(i));
    return s;
}

int main()
{
    srand(time(0));
    ofstream file;
    file.open("power.txt",ios::out);
    for(int i=0;i<TOTALELEMENT;i++) assert(get_index(get_element(i))==i);
    for(int n=1; n<=50; n++)
    {
        string s =generate_set(n);
        cout<<" list \n";
        cout<<s<<endl;
        s=make_set(s);
        cout<<s<<endl;

        StartCounter();
        power_set(s);
        double tim=GetCounter();
        file<<n<<" "<<tim<<endl;
    }
}
