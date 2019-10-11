#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define WHITE -1
#define GREY 0
#define BLACK 1
#define MAX_EDGE 1000000000
#define MAX_VERTEX 20000
#define MAX_N 100000
#define MAX_Q 20000

typedef struct node{
    short color;
    int d;
    // int f;
    int least;
    int parent;
    vector<int> adjv;
} node;

//At initialization, set front and rear to 0
typedef struct queue{
    int arr[MAX_VERTEX];
    int front;
    int rear;
} queue;

typedef struct edge
{
    int u;
    int v;
    short exist;
} edge;


long tme;
int xsource;
vector<edge> edge_dash;

int isEmpty(queue* q){return q->rear==q->front;}

int isFull(queue* q){return q->front==MAX_VERTEX-1;}

void push(queue* q, int n){
    q->arr[q->front]=n;
    q->front=q->front+1;
}

int pop(queue* q){
    if(isEmpty(q))
        return __INT_MAX__;
    else{
        q->rear=(q->rear)+1;
        return q->arr[(q->rear)-1];
    }
}

node getNode(long val, long marker){
    node nx;
    nx.color=WHITE;
    nx.d=0;
    // nx.f=0;
    nx.parent=-1;
    nx.least=0;
    vector<int> x;
    nx.adjv=x;
    return nx;
}

void printGraph(node G[], long V){
    // Prints the value of all vertices of the adjacency list in order of occurence. Not DFS or BFS.
    for(int i=edge_dash.size()-1; i>=0; i--){
        printf("%d %d\n",edge_dash[i].u, edge_dash[i].v);
    }
    if(edge_dash.size()==0)
        printf("No\n");
}

void DFS_Visit(node G[], long s){
    G[s].color=GREY;
    vector<int> adjlist=G[s].adjv;
    G[s].d=tme;
    G[s].least=tme;
    tme+=1;
    int child=0;
    for (int i = 0; i < adjlist.size(); i++){
        if(G[adjlist[i]].color==WHITE){
            child++;
            G[adjlist[i]].parent=s;
            DFS_Visit(G, adjlist[i]);
            G[s].least=min(G[s].least, G[adjlist[i]].least);
            if(G[adjlist[i]].least > G[s].d){
                edge ex;
                ex.exist=1;
                if(adjlist[i]<=s){
                    ex.u=adjlist[i];
                    ex.v=s;
                }
                else{
                    ex.u=s;
                    ex.v=adjlist[i];
                }
                edge_dash.push_back(ex);
            }
        }
        else if(G[s].parent!=adjlist[i]){
            G[s].least=min(G[s].least, G[adjlist[i]].d);             
        }
    }
    G[s].color=BLACK;
    // G[s].f=tme;
    tme+=1;
}

void DFS(node G[], long V){
    for(long i; i<V; i++){
        if(G[i].color == WHITE){
            tme++;
            DFS_Visit(G, i);
        }
    }
}

int main(){
    long V;
    long long E;
    scanf("%ld", &V);
    scanf("%lld", &E);
    node G[V];
    for(long i=0; i<V; i++){
        G[i]=getNode(i, i); // the marker argument will always be the index of the array as this is how it is identified in the Adjacency Lists
    }
    int u, v;
    for(long long i=0; i<E; i++){
        scanf("%d %d\n", &u, &v);
        G[u].adjv.push_back(v);
        G[v].adjv.push_back(u);
    }
    DFS(G, V);
    printGraph(G, V);
}
