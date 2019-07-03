#include<iostream>
#include<cstring>
#define BLOCK_SIZE 3
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
        arr_size=BLOCK_SIZE;
        arr = new T[BLOCK_SIZE];
        total=0;
    }
    T & top() /// ###  returns referance  + check empty() :: be carefull
    {
        if(total-1 >=0)
            return  arr[total-1];
        else throw "Stack is empty";
    }
    void push(T x) /// nothing to worry
    {
        if(total+1 >= arr_size)
        {
            arr_size+=BLOCK_SIZE;
            T  * newarr = new T[arr_size];
            memcpy(newarr,arr,sizeof (T) * (arr_size-BLOCK_SIZE));
            delete arr;
            arr= newarr;
        }
        arr[total++]=x;
    }
    T pop()
    {
        if(total>0)
            return arr[--total];
        else return NULL;
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


using namespace std;
template < class T >
class Queue
{

    T *arr;
    int arr_size,start,end;
public :
    Queue()
    {
        arr_size=BLOCK_SIZE;
        arr = new T[BLOCK_SIZE];
        start=end=0;
    }
    T & front() /// ###  returns referance  + check empty() before call :: be carefull
    {
        return  arr[start];
    }
    T & rear() /// ###  returns referance  + check empty() before call:: be carefull
    {
        return  arr[(end-1+arr_size)%arr_size];
    }
    void enqueue(T x)
    {
        if(size()+1 >= arr_size)
        {
//            cout<<" memory overload\n";
            T  * newarr = new T[arr_size+BLOCK_SIZE];
            if(start==0)
            {
                memcpy(newarr,arr,sizeof (T) * (arr_size));
            }
            else
            {
                for(int i=start; i<arr_size; i++)
                    newarr[i-start]=arr[i];
                for(int i=0; i<=end; i++)
                    newarr[arr_size-start + i] = arr[i];
                start=0;
                end= arr_size-1;
            }
            delete arr;
            arr= newarr;
            arr_size+=BLOCK_SIZE;
        }
        arr[end]=x;
        end= (end+1)%arr_size;
    }
    T dequeue()
    {
        if(!empty())
        {
            start=(start+1)%arr_size;
            return arr [ (start -1 +arr_size )%arr_size];
        }
        else return NULL;
    }
    bool empty()
    {
        return start==end;
    }
    int size()
    {
        return start <= end ? end - start : arr_size  - start + end;
    }
};

int main()
{
    try
    {

        int option,choice;
        Stack<int> s1;
        Queue<int> q1;

        do
        {
            cout<<"Option 1: Stack Operation"<<endl;
            cout<<"Option 2: Queue Operation"<<endl;
            cout<<"Option 3: Exit"<<endl<<endl;

            cin>>option;
            if(option==1)
            {
                int choice;
                do
                {
                    cout<<endl<<"Choice 1 : Pushing in the stack"<<endl;
                    cout<<"Choice 2 : Popping from the stack"<<endl;
                    cout<<"Choice 3 : Size of the stack"<<endl;
                    cout<<"Choice 4 : top element of the stack"<<endl;
                    cout<<"Choice 5 : Emptiness of the stack"<<endl;
                    cout<<"Choice 0 : Exit stack operation"<<endl<<endl;
                    cin>>choice;
                    switch(choice)
                    {
                    case 1:
                        int element;
                        cout<<"Enter the element you want to push in the stack : ";
                        cin>>element;
                        s1.push(element);
                        break;
                    case 2:
                        cout<<"The element you popped from the stack is "<<s1.top()<<endl;
                        s1.pop();
                        break;
                    case 3:
                        cout<<"The size of the stack is "<<s1.size()<<endl;
                        break;
                    case 4:
                        cout<<"Top element of the stack is "<<s1.top()<<endl;
                        break;
                    case 5:
                        int result=s1.empty();
                        if(result)
                        {
                            cout<<"Stack is empty"<<endl;
                        }
                        else
                        {
                            cout<<"Stack is not empty"<<endl;
                        }
                        break;
                    }

                }
                while(choice!=0);
            }
            else if(option==2)
            {
                int choice;
                do
                {
                    cout<<endl<<"Choice 1 : Enqueing in the queue"<<endl;
                    cout<<"Choice 2 :Dequeing from the queue"<<endl;
                    cout<<"Choice 3 : Size of the queue"<<endl;
                    cout<<"Choice 4 : first element of the queue"<<endl;
                    cout<<"Choice 5 : last element of the queue"<<endl;
                    cout<<"Choice 6 : Emptiness of the queue"<<endl;
                    cout<<"Choice 0 : Exit queue operation"<<endl<<endl;
                    cin>>choice;
                    switch(choice)
                    {
                    case 1:
                        int element;
                        cout<<"Enter the element you want to enqueue in the queue : ";
                        cin>>element;
                        q1.enqueue(element);
                        break;
                    case 2:
                        cout<<"The element you dequed from the queue is "<<q1.front()<<endl;
                        q1.dequeue();
                        break;
                    case 3:
                        cout<<"The size of the queue is "<<q1.size()<<endl;
                        break;
                    case 4:
                        cout<<"first element of the queue is "<<q1.front()<<endl;
                        break;
                    case 5:
                        cout<<"last element of the queue is "<<q1.rear()<<endl;
                        break;
                    case 6:
                        int result=q1.empty();
                        if(result)
                        {
                            cout<<"queue is empty"<<endl;
                        }
                        else
                        {
                            cout<<"queue is not empty"<<endl;
                        }
                        break;
                    }

                }
                while(choice!=0);
            }
        }
        while(option!=3);
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
}
