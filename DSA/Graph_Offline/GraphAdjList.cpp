#include<iostream>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3

using namespace std;

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
    ArrayList  * adjList ;
    int *color,*parent,*dist;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u,bool out =true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
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

    color = new int [n];
    parent = new int [n];
    dist = new int [n];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed)
        adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return ;

    if(isEdge(u,v))
    {
        this->nEdges--;
        adjList[u].removeItem(v);
        if(!directed)
            adjList[v].removeItem(u);

    }
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return 0;

    return adjList[u].searchItem(v) != NULL_VALUE;
    //returns true if (u,v) is an edge, otherwise should return false
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
        if(isEdge(i,u)||isEdge(u,i))
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
            if(color[v]==WHITE)
            {
                color[v]=GRAY;
                dist[v]=dist[u]+1;
                parent[v]=u;
                q.enqueue(v);
            }
        }
        color[u]=BLACK;
    }

}

int Graph::getDist(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices) return INFINITY;
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
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
            printf(" %d", adjList[i].getItem(j));
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
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
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
            cout<<"There is "<<(g.isEdge(u,v)?"a":"no")<<" edge from "<<u<<" to "<<v<<"\n";
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
