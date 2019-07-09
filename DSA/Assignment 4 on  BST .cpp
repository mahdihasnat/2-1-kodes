#include<iostream>
#include<algorithm>
using namespace std;

#define DBG(x) cout<< #x<<" ---> "<<x<<"\n";
#define NL cout<<"\n"
template<class T >
class Node
{
public:
    T value;
    Node *left,*right;
    Node(T value,Node *left =0,Node * right=0): value(value),left(left),right(right) {}

};
template<class T >
class BST
{
private:

    Node <T> *root;

    bool Search( T value,Node<T> * head )
    {
        if(head)
        {
            if(head->value==value)
                return true;
            else if(head->value > value )
                return Search(value,head->left);
            else
                return Search(value,head->right);
        }
        else
            return false;
    }

    Node<T> * Insert( T value,  Node<T> * head  )
    {
        if(head)
        {
            if(head->value == value)
            {
                return head;
            }
            else if(head->value > value )
            {
                head->left = Insert(value, head->left);
                return head;
            }
            else
            {
                head->right= Insert(value, head->right);
                return head;
            }
        }
        else
            return new Node<T>(value);
    }

    T getmin(Node <T> * head )
    {
        if(head->left)
            return getmin(head->left);
        else
            return head->value;
    }

    Node <T> * Delete(T value, Node <T> * head )
    {
        if(head)
        {
            if(head->value==value)
            {
                if(head->left && head->right)
                {
                    T nextmin = getmin(head->right);
                    head->value= nextmin;
                    head->right = Delete(nextmin,head->right);
                    return head;
                }
                else if(head->left)
                {
                    delete head;
                    return head->left;
                }
                else if(head->right)
                {
                    delete head;
                    return head->right;
                }
                else
                {
                    delete head;
                    return nullptr;
                }
            }
            else if(head->value > value)
            {
                head->left= Delete(value,head->left);
                return head;
            }
            else
            {
                head->right = Delete(value,head->right);
                return head;
            }
        }
        else
            return nullptr;
    }
    void Preorder(Node < T> * head)
    {
        if(head)
        {
            cout<<head->value<<" ";
            Preorder(head->left);
            Preorder(head->right);
        }
    }
    void Inorder(Node < T> * head)
    {
        if(head)
        {
            Inorder(head->left);
            cout<<head->value<<" ";
            Inorder(head->right);
        }
    }
    Node <T> * make_bst(T *arr,int n)
    {
        if(n<=0)
            return nullptr;
        else
        {
            int mid= n/2;
            DBG(arr[mid]);
            DBG(n);
            DBG(mid);
            return new Node <T> (arr[mid], make_bst(arr,mid),make_bst(arr+mid+1,n-mid-1));
        }
    }
public:
    BST():root(0) {}
    BST(T *arr,int n) /// make bst from a sorted array
    {
        /// sort the array
        sort(arr,arr+n);
        /// remove duplicate
        int i=0;
        for(int j=1; j<n; j++)
            arr[i]!=arr[j] ? arr[++i]=arr[j] : 0 ;
        n=i+1;
        /// make binary search tree
        root= make_bst(arr,n);
    }

    bool Search(T value)
    {
        return Search(value,root);
    }
    void Insert(T value)
    {
        root= Insert(value,root);
    }
    void Delete(T value)
    {
        root= Delete(value,root);
    }

    void print_preorder()
    {
        Preorder(root);
        cout<<"\n";
    }
    void print_inorder()
    {
        Inorder(root);
        cout<<"\n";
    }

};



int main()
{
    BST<int > binTree;
    int choice;
    do
    {
        cout<<" Enter 1: to Inset\n Enter 2: to traverse inorder\n Enter 3: to traverse pretorder\n Enter 4: to delete\n Enter 5: to Search\n Enter 6: exit"<<endl;
        cin>>choice;
        if(choice==1)
        {
            int x;
            cin>>x;
            binTree.Insert(x);
            cout<<" value inserted\n";
        }
        else if(choice==2)
        {
            binTree.print_inorder();

        }
        else if(choice==3)
        {
            binTree.print_preorder();

        }
        else if(choice==4)
        {
            int x;
            cin>>x;
            binTree.Delete(x);
            cout<<" value deleted\n";
        }
        else if(choice==5)
        {
            int x;
            cin>>x;
            if(binTree.Search(x))
                cout<<" Value found\n";
            else
                cout<<" value not found\n";


        }
    }
    while(choice !=6);
}
