#include<iostream>
#include<cstring>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define MAX_ELEMENT 10000
using namespace std;


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

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}


int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item )
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length )
        return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE )
        return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length)
        return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)
        return true;
    else
        return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list)
        delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList , * weightList ;
    int *color,*parent,*dist;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getWeight(int u,int v);
    int getDegree(int u,bool out =true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dijkstra(int source);  //will run dijkstra in the graph
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    weightList  = 0 ;
    directed = dir ; //set direction of the graph
    color= 0;
    parent= 0;
    dist= 0;
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    this->nEdges=0;
    if(adjList!=0)
        delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    weightList  = new ArrayList[nVertices];

    color = new int [n];
    parent = new int [n];
    dist = new int [n];
}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    weightList [u].insertItem(w);
    if(!directed)
        adjList[v].insertItem(u) , weightList[v].insertItem(w);
}

void Graph::removeEdge(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return ;

    if(isEdge(u,v))
    {
        this->nEdges--;
        int w = weightList [u].getItem(adjList[u].searchItem(v));
        adjList[u].removeItem(v);
        weightList[u].removeItem(w);
        if(!directed)
            adjList[v].removeItem(u), weightList[v].removeItem(w);

    }
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return 0;

    return adjList[u].searchItem(v) != NULL_VALUE;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph:: getWeight(int u,int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return INFINITY;
    int i=adjList[u].searchItem(v);
    if(i==NULL_VALUE ) return INFINITY;
    return weightList[u].getItem(i);
}

int Graph::getDegree(int u,bool out)
{
    if(u<0||u>=nVertices) return 0;

    if(out)
        return adjList[u].getLength();
    else
    {
        int deg=0;

        for(int i=0; i<nVertices; i++)
            deg+=isEdge(i,u);

        return deg;
    }
    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    if(u<0||u>=nVertices) return ;
    cout<<"Adjacent vertices of "<<u<<" : ";
    for(int i=0; i<nVertices; i++)
        if(isEdge(u,i))
            cout<<i<<" ";
    cout<<"\n";
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return 0;

    for(int i=0;i<nVertices;i++)
        if((isEdge(u,i))&&(isEdge(v,i))) return 1;
    return 0;
    //returns true if vertices u and v have common adjacent vertices
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    if(source<0||source>=nVertices) return ;

    for(int i=0; i<nVertices; i++)
    {
        color[i]=WHITE;
        dist[i]=INFINITY;
        parent[i]= NULL_VALUE;
    }

    color[source]=GRAY;
    dist[source]=0;

    Queue q;
    q.enqueue(source);

    while(!q.empty())
    {
        int u= q.dequeue();

        for(int i=0; i<adjList[u].getLength(); i++)
        {
            int v =adjList[u].getItem(i);
            int w= weightList[u].getItem(i);
            if(color[v]==WHITE)
            {
                color[v]=GRAY;
                dist[v]=dist[u]+ 1;
                parent[v]=u;
                q.enqueue(v);
            }
        }

        color[u]=BLACK;
    }

}
void Graph::dijkstra(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    if(source<0||source>=nVertices) return ;

    for(int i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
        parent[i]= NULL_VALUE;
    }

    dist[source]=0;

    MaxHeap<pair < int , int > > pq;
    pq.Insert({0,source});

    while(!pq.empty())
    {
        int dw= - pq.Max().first;
        int u = pq.Max().second;
        pq.DeleteMax();
        if(dist[u] != dw ) continue;

        for(int i=0; i<adjList[u].getLength(); i++)
        {
            int v =adjList[u].getItem(i);
            int w= weightList[u].getItem(i);
            if(dist[v] > dist[u] + w)
            {
                dist[v]=dist[u]+ w;
                parent[v]=u;
                pq.Insert({-dist[v],v});
            }
        }

    }

}

int Graph::getDist(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return INFINITY;
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    dijkstra(u);
    return dist[v];
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" { %d, %d}", adjList[i].getItem(j),weightList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    nVertices=nEdges=directed=0;
    if(color) delete [] color;
    if(dist) delete[] dist;
    if(parent) delete[] parent;
    if(adjList) delete[] adjList;
    if(weightList) delete []weightList;
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir=false;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)
        dir = true;
    else if(choice == 2)
        dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n\
               2. Remove edge\n\
               3. Check edge\n\
               4. Count In Degree\n\
               5. Count Out Degree\n\
               6. Print Adjacent Vertices \n\
               7. Check Common Adjacency \n\
               8. Get Distance from u to v\n\
               9. Print Graph \n\
               10. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v,w;
            scanf("%d%d %d", &u, &v,&w);
            g.addEdge(u, v,w);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u,v))
                cout<<"weight of edge between "<<u<<" to "<<v<<" : "<<g.getWeight(u,v)<<"\n";
            else
                cout<<"There is no edge from "<<u<<" to "<<v<<"\n";
        }
        else if(ch==4)
        {
            int u;
            cin>>u;
            cout<<"in degree of "<<u<<" is : "<<g.getDegree(u,false)<<"\n";
        }
        else if(ch==5)
        {
            int u;
            cin>>u;
            cout<<"out degree of "<<u<<" is : "<<g.getDegree(u,true)<<"\n";
        }
        else if(ch==6)
        {
            int u;
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            cout<<u<<" "<<v<<(g.hasCommonAdjacent(u,v)? "": " don't")<<" have common adjacent vertices\n";
        }
        else if(ch==8)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            cout<<"Distance between "<<u<<" and "<<v<<" : "<<g.getDist(u,v)<<"\n";
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            break;
        }
    }

}
/*
2
7
1
1 5 1
1
1 2 3
1
2 5 4
1
3 5 20
1
2 4 30
1
5 6 -10
9
*/
