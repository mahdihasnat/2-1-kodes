#include<time.h>
#include<iostream>
#include<fstream>
#include<assert.h>
#include<windows.h>
using namespace std;

int search_linear(int * a, int size,int key)
{
    for(int i =0 ; i<size; i++)
        if(a[i]==key )
            return i;
    return -1;
}
int search_binary(int *a,int size, int key )
{
    int lo= 0,hi=size-1,mi;
    while(lo<=hi)
    {
        mi= (lo+hi)/2;
        if(a[mi]==key)
            return mi;
        else if(a[mi]<key)
            lo=mi+1;
        else
            hi=mi-1;
    }
    return -1;
}
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

int main()
{
    ofstream flinear;
    flinear.open("linear.txt",ios::out);

    ofstream fbinary;
    fbinary.open("binary.txt",ios::out);
    srand(time(0));
    for(int n=10; n<=10000; n++)
    {
        int *a= new int [n];
        a[0]=rand()%100000;
        for(int i=1; i<n; i++)
        {
            a[i]=a[i-1]+ rand()%100000;
        }


        int key = rand();

        double time=0;
        int totalRun=100;
        while(totalRun--)
        {
            StartCounter();

            int ans= search_linear(a,n,key);
            if(ans!=-1)
                assert(a[ans]==key);

            time+=GetCounter();
        }
        time/=100;
        flinear<<n<<" "<<time<<"\n";

        totalRun=100;
        time=0;
        while(totalRun--)
        {

            StartCounter();

            int ans= search_binary(a,n,key);
            if(ans!=-1)
                assert(a[ans]==key);

            time+=GetCounter();

        }
        time/=100;

        fbinary<<n<<" "<<time<<"\n";

        delete []a;
    }
}
