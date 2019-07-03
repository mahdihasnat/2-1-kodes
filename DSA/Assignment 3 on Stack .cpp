#include<iostream>
#include<cstring>

using namespace std;
template < class T >
class Stack
{
    T *arr;
    int arr_size;
    int total;
public :
    Stack()
    {
        arr_size=10;
        arr = new T[10];
        total=0;
    }
    T & top() /// ###  returns referance  + check empty() :: be carefull
    {
        return  arr[total-1];
    }
    void push(T x) /// nothing to worry
    {
        if(total+1 >= arr_size)
        {
            arr_size+=10;
            T  * newarr = new T[arr_size];
            memcpy(newarr,arr,sizeof (T) * (arr_size-10));
            delete arr;
            arr= newarr;
        }
        arr[total++]=x;
    }
    void pop()
    {
        if(total>0)
            total--;
    }
    bool empty()
    {
        return total==0;
    }
    int size()
    {
        return total;
    }
};

int main()
{
    Stack < string > st;
    st.push("456");
    while(!st.empty())
    {
        cout<<st.top()<<"\n";
        st.pop();
    }
}
