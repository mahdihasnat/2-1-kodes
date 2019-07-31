#include<bits/stdc++.h>

using namespace std;

int merge(int  * arr, int n)
{
    int inv=0;
    int mid= n/2;
    int  * temp = new int [ mid];
    memcpy(temp,arr, mid * sizeof( int) );

    int l= 0,r= mid;
    for(int i=0; i<n; i++)
    {
        if(r<n and l<mid and arr[r] >= temp[l]) {
            arr[i]= temp[l++];
            inv+=r-mid;
        }
        else if(r<n)
            arr[i]=arr[r++];
        else {
            arr[i]= temp[l++];
            inv+=r-mid;
        }
    }
    delete [] temp;
    return inv;
}
int inversion(int *arr,int n)
{
    if(n>1){
        int inv=0;
        int mid=n/2;
        inv+=inversion(arr,mid);
        inv+=inversion(arr+mid,n-mid);
        inv+=merge(arr,n);
        return inv;
    }
    else return 0;

}
int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];

    }
    int ans=inversion(a,n);
//    for(int i=1;i<n;i++)
//        assert(a[i]>=a[i-1]);
    cout<<" inversion count = "<<ans<<"\n";
}
