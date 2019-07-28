#include<iostream>
#include<cstring>
using namespace std;

#define DBG(x) cout<< #x<<" ---> "<<x<<"\n";
#define NL cout<<"\n";
#define MAX_ELEMENT 10000
template<class T >
class PriorityQueue
{
private:
    T * heap; /// 0-indexed
    int size=0; /// index of free hole
    void percolateUp(int hole,T val)
    {
        while(hole>0 && heap[(hole-1)/2] < val)
        {
            heap[hole]=heap[(hole-1)/2] ;
            hole=(hole-1)/2;
        }
        heap[hole]=val;
    }
    void percolateDown(int hole, T val)
    {
        while(2*hole + 1 <size)
        {
            int l = 2*hole+1;
            int r= 2*hole+2;
            int terget=l;
            if(r<size && heap[l]<heap[r])
                terget= r;
            if(heap[terget]> val)
            {
                heap[hole]= heap[terget];
                hole= terget;
            }
            else
                break;
        }
        heap[hole]= val;
    }
public:
    PriorityQueue(T * arr=0,int n=0)
    {
        heap = new T[MAX_ELEMENT];
        if(arr)
            memcpy(heap,arr,n* sizeof(T) );
        size = n;
        for(int i=size-1; i>=0; i--)
            percolateDown(i,heap[i]);
    }

    void Insert(T val)
    {
        percolateUp(size++,val);
    }
    T FindMax()
    {
        return heap[0];
    }
    T ExtractMax()
    {
        if(size>0){
            T ret = heap[0];
            percolateDown(0,heap[--size]);
            return ret;
        }
        else return  *(new T);
    }
    void IncreaseKey(int i,T newKey)
    {
        i--;
        if(i>=0)
        {
            percolateUp(i,newKey);
        }
    }
    void DecreaseKey(int i,T newKey)
    {
        i--;
        if(i>=0)
        {
            percolateDown(i,newKey);
        }
    }
    T Max()
    {
        return heap[0];
    }
    void print()
    {
        cout<<" PriorityQueue size = "<<size<<" , data = ";
        for(int i =0;i<size;i++)
            cout<<heap[i]<<" ";
        cout<<"\n";
    }
    bool empty()
    {
        return size==0;
    }
    friend ostream &operator <<(ostream &os,const PriorityQueue &pq)
    {
        os<<" PriorityQueue size = "<<pq.size<<" , data = { ";
        for(int i =0;i<pq.size;i++)
            os<<pq.heap[i]<<" , ";
        os<<" } ";
        return os;
    }
};



int main()
{

    typedef int T;
    PriorityQueue<T> pq;
    int choice;
    do
    {
        cout<<" Enter 1: to Inset\n Enter 2: to FindMax \n Enter 3: to ExtractMax\n Enter 4: to IncreaseKey\n Enter 5: to DecreaseKey\n Enter 6: Print\n Enter 7: to exit"<<endl;
        cin>>choice;
        if(choice==1)
        {
            cout<<" enter value\n";
            T x;
            cin>>x;
            pq.Insert(x);
        }
        else if(choice==2)
        {
            cout<<" Max = "<<pq.FindMax()<<"\n";
        }
        else if(choice==3)
        {
            cout<<" extracted value "<<pq.ExtractMax()<<"\n";
        }
        else if(choice==4)
        {
            cout<<" Enter index(1-based) "<<"\n";
            int i;
            cin>>i;
            cout<<"Enter new key \n";
            T k;
            cin>>k;
            pq.IncreaseKey(i,k);
        }
        else if(choice==5)
        {
            cout<<" Enter index(1-based) "<<"\n";
            int i;
            cin>>i;
            cout<<"Enter new key \n";
            T k;
            cin>>k;
            pq.DecreaseKey(i,k);
        }
        else if(choice==6)
            cout<<pq<<"\n";
    }
    while(choice !=7);
}
