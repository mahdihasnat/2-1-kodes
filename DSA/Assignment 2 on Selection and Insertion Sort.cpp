#include<time.h>
#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;

void sort_selection(int *a,int n)
{
    for(int i=0; i<n; i++)
    {
        int s=i;
        for(int j=i+1; j<n; j++)
            if(a[j]<a[s])
                s=j;
        swap(a[s],a[i]);
    }
}
void sort_insertion(int *a,int n)
{
    for(int i=1; i<n; i++)
    {
        int now=i-1;
        while(now>=0 && a[now] > a[now+1])
        {
            swap(a[now],a[now+1]);
            now--;
        }
    }
}

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

void generate_best(int *a,int n)
{
    a[0]=rand()%100000;
    for(int i=1; i<n; i++)
    {
        a[i]=a[i-1]+rand()%100000;
    }
}
void generate_worst(int *a,int n)
{

    a[0]=rand()%100000;
    for(int i=1; i<n; i++)
    {
        a[i]=a[i-1]-rand()%100000;
    }
}
void generate_average(int *a,int n)
{
    for(int i=0; i<n; i++)
        a[i]=rand();

}
void print(int *a,int n)
{
    for(int i =0; i<n; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
int main()
{
    srand(time(0));
    ofstream file;
    file.open("selection.txt",ios::out);
    const int total_run=10;
    int *a=new int [10004];
    for(int n=10; n<=10000; n+=50)
    {
        double best=0,worst=0,average=0;

        generate_best(a,n);

        for(int j=0;j<total_run;j++)
        {
            StartCounter();
            sort_selection(a,n);
            best+=GetCounter();
        }
        best/=total_run;


        generate_average(a,n);
        for(int j=0;j<total_run;j++)
        {
            StartCounter();
            sort_selection(a,n);
            average+=GetCounter();
        }
        average/=total_run;


        generate_worst(a,n);
        for(int j=0;j<total_run;j++)
        {
            StartCounter();
            sort_selection(a,n);
            worst+=GetCounter();
        }
        worst/=total_run;

        file<<n<<" "<<best<<" "<<average<<" "<<worst<<"\n";

    }
}
