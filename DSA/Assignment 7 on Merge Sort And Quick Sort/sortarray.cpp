#include<bits/stdc++.h>
#include<windows.h>
using namespace std ;
#define NL cout<<"\n";
#define DBG(a) cout<< #a <<" --> "<<(a)<<endl;


double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        printf(  "QueryPerformanceFrequency failed!\n");

    PCFreq = double(li.QuadPart)/1.00;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

template < class T >
void merge(T  * arr, int n)
{
    T  * temp = new T [ n/2];
    memcpy(temp,arr, n/2 * sizeof( T) );
    int l= 0,r= n/2;
    for(int i=0; i<n; i++)
    {
        if(r<n and l<n/2 and arr[r] > temp[l])
            arr[i]= temp[l++];
        else if(r<n)
            arr[i]=arr[r++];
        else
            arr[i]= temp[l++];
    }
    delete [] temp;
}
template < class T >
void sort_merge(T * arr, int n)
{
    if(n>1)
    {
        sort_merge(arr,n/2);
        sort_merge(arr+n/2,n-n/2);
        merge(arr,n);
    }
}
template < class T >
int partition(T * arr,int n) /// returns  size of left partition
{
    int i= 0,j;
    for( j=0; j<n-1; j++)
    {
        if(arr[j]<=arr[n-1])
        {
            T tmp = arr[i];
            arr[i++]= arr[j];
            arr[j] = tmp;
        }

    }
    T tmp = arr[i];
    arr[i++]= arr[j];
    arr[j] = tmp;
    return i;
}
template < class T >
void sort_quick(T *arr, int n)
{
    if(n>1)
    {

        int p = partition(arr,n);

//        assert(abs(p-1-(n-p))<=1);// check if balanced

        sort_quick(arr,p-1);
        sort_quick(arr+p,n-p);
    }
}
template < class T >
void sort_quick_iterative(T *arr, int n)
{
    stack<int > st;
    st.push(0);
    st.push(n);

    while(!st.empty())
    {
        int r =st.top();
        st.pop();
        int l =st.top();
        st.pop();
        if(r-l>1)
        {
            int p = partition(arr+l,r-l);
            p+=l;
            st.push(l);
            st.push(p-1);

//            assert(abs((p-1-l)-(r-p))<=1);

            st.push(p);
            st.push(r);
        }
    }
}

int generate_best_case_quick_sort_util(int *inorder,int n,int *arr,int position)
{
    if(n<=0) return position;
    int mid= (n+1)/2-1;

    position = generate_best_case_quick_sort_util(inorder,mid,arr,position);

    int majhkhan = position;

    arr[position++]=inorder[mid];

    position = generate_best_case_quick_sort_util(inorder+mid+1,n-mid-1,arr,position);

    int sesh= position -1;

    swap(arr[majhkhan],arr[sesh]);
    return position;
}

void  generate_best_case_quick_sort(int *a ,int n) /// best case for quick sort ( last element as pivot) is  modified inorder travasral of balanced binary search tree ( all distinct number ) where in each node mid element is swaped with maximum element in right subarray
{
    int * tmp = new int [n]; /// in order travasral is saved in tmp array
    int mod = INT_MAX / (2*n);
    tmp[0]=rand()%mod;
    for(int i=1;i<n;i++)
        tmp[i]= tmp[i-1] + (rand()%mod+1);
    assert(generate_best_case_quick_sort_util(tmp,n,a,0)==n);
    delete [] tmp;
}
int main()
{
    srand(time(0));
    int choice, n=0,mod;
    int * arr=0;
    bool True= 1;
    while(True)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate best case(quick sort)\n");
        printf("4. Generate worst case\n");
        printf("5. Apply Merge sort\n");
        printf("6. Apply Quicksort\n");
        printf("7. Print array\n");
        printf("8. Exit\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            printf("Number of elements: ");
            scanf("%d", &n);
            if(arr)
                delete [] arr ;
            arr = new int [n];

            for(int i=0; i<n; i++)
            {
                arr[i]=rand();
            }

            break;

        case 2:
            printf("Number of elements: ");
            scanf("%d", &n);
            if(arr)
                delete [] arr ;
            arr = new int [n];
            mod = INT_MAX / n;

            arr[0]=rand()%mod;
            for(int i=1; i<n; i++)
            {
                arr[i]=arr[i-1]+rand()%mod;
            }

            break;

        case 3:
            printf("Number of elements: ");
            scanf("%d", &n);
            if(arr)
                delete [] arr ;
            arr= new int [n];
            generate_best_case_quick_sort(arr,n);

            break;

        case 4:
            printf("Number of elements: ");
            scanf("%d", &n);
            if(arr)
                delete [] arr ;
            arr = new int [n];
            mod = INT_MAX / n;

            arr[0]=rand()%mod;
            for(int i=1; i<n; i++)
            {
                arr[i]=arr[i-1]-rand()%mod;
            }

            break;

        case 5:
            printf("Applying merge sort\n");
            if(n)
            {
                StartCounter();
                sort_merge(arr,n);
                double time= GetCounter();
                printf("Time taken to finish: %.10f sec\n",time);
                for(int i=0;i<n-1;i++) assert(arr[i] <= arr[i+1]);
            }
            break;

        case 6:
            printf("Applying quicksort\n");
            if(n)
            {
                StartCounter();
                sort_quick(arr,n);
                double time= GetCounter();
                printf("Time taken to finish: %.10f sec\n",time);
                for(int i=0;i<n-1;i++) assert(arr[i] <= arr[i+1]);
            }
            break;

        case 7:
            printf("Array\n");
            for(int i=0; i<n; i++)
                printf("%d ",arr[i]);
            printf("\n");
            break;
        case 8 :
            True= 0;
            break;
        }
    }
}

