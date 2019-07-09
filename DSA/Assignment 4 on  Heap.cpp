#include<iostream>
#include<cstring>
using namespace std;

#define DBG(x) cout<< #x<<" ---> "<<x<<"\n";
#define NL cout<<"\n";
#define MAX_ELEMENT 10000
template<class T >
class MaxHeap
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
    MaxHeap(T * arr=0,int n=0)
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
    void DeleteMax()
    {
        if(size>0)
            percolateDown(0,heap[--size]);
    }
    T Max()
    {
        return heap[0];
    }
    bool empty()
    {
        return size==0;
    }
};



int main()
{
    MaxHeap <string > pq;
    DBG(pq.empty())
    pq.Insert("10");
    pq.Insert("10");
    pq.Insert("10");
    pq.Insert("20");
    pq.Insert("20");
    pq.Insert("20");
    pq.Insert("20");
    while(!pq.empty())
    {
        DBG(pq.Max())
        pq.DeleteMax();
    }
}
