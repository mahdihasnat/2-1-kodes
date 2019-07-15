#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3
#include<iostream>
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
    rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
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


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ; //adjacency matrix to store the graph
    int *color,*parent,*dist;//define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u,bool out = true);
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
    matrix = 0 ;
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
    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

    color = new int [n];
    parent = new int [n];
    dist = new int [n];
}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;
    this->nEdges++;
    matrix[u][v] ++;
    if(!directed)
        matrix[v][u] ++;

}

void Graph::removeEdge(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices)
        return ;
    if(matrix[u][v])
    {
        this->nEdges--;
        matrix[u][v]--;
        if(!directed)
            matrix[v][u]--;
    }
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices)
        return 0;
    return matrix[u][v];
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u,bool out)
{
    if(u<0||u>=nVertices)
        return 0;
    int deg=0;

    for(int i=0; i<nVertices; i++)
        deg+= out ? matrix[u][i] :  matrix[i][u];

    return deg;
    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    if(u<0||u>=nVertices)
        return ;
    cout<<"Adjacent vertices of "<<u<<" : ";
    for(int i=0; i<nVertices; i++)
        if(matrix[u][i])
            cout<<i<<" ";
    cout<<"\n";
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices)
        return 0;
    for(int i=0; i<nVertices; i++)
        if((isEdge(u,i))&&(isEdge(v,i)))
            return 1;
    return 0;
    //returns true if vertices u and v have common adjacent vertices
}

void Graph::bfs(int source)
{
    if(source<0||source>=nVertices)
        return ;
    //write this function
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
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[u][i] && color[i]==WHITE)
            {
                color[i]=GRAY;
                dist[i]=dist[u]+1;
                parent[i]=u;
                q.enqueue(i);
            }
        }
        color[u]=BLACK;
    }
}

int Graph::getDist(int u, int v)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices)
        return INFINITY;
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
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(color)
        delete [] color;
    if(dist)
        delete [] dist;
    if(parent)
        delete [] parent;
    for(int i=0; i<nVertices; i++)
    {
        delete [] matrix[i];
    }
    if(nVertices)
        delete [] matrix;
    nVertices=nEdges=directed=0;
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
/*
2
7

1
1 2
1
1 5
1
2 5
1
3 2
1
3 4
1
4 5
1
4 6
9

*/
