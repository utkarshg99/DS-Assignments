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

typedef struct lnode{
    lnode* next;
    int val;
} lnode;

typedef struct node{
    short color;
    int d;
    // int f;
    int least;
    int parent;
    // vector<int> adjv;
    lnode* adjv;
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
    edge* next;
} edge;


long tme;
int xsource;
edge* edge_dash=NULL;

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
    nx.adjv=NULL;
    return nx;
}

lnode* insertLnode(lnode* x, lnode* y){
    if(x==NULL){
        return y;
    }
    else
    {
        y->next=x;
        return y;
    }
}

void printGraph(node G[], long V){
    // Prints the value of all vertices of the adjacency list in order of occurence. Not DFS or BFS.
    if(edge_dash==NULL)
        printf("No\n");
    while (edge_dash!=NULL)
    {
        printf("%ld %ld\n", edge_dash->u, edge_dash->v);
        edge_dash=edge_dash->next;
    }
}

void DFS_Visit(node G[], long s){
    G[s].color=GREY;
    lnode* adjlist=G[s].adjv;
    G[s].d=tme;
    G[s].least=tme;
    tme+=1;
    int child=0;
    while(adjlist!=NULL){
        if(G[adjlist->val].color==WHITE){
            child++;
            G[adjlist->val].parent=s;
            DFS_Visit(G, adjlist->val);
            G[s].least=min(G[s].least, G[adjlist->val].least);
            if(G[adjlist->val].least > G[s].d){
                edge* ex=(edge*)malloc(sizeof(edge));
                if(adjlist->val<=s){
                    ex->u=adjlist->val;
                    ex->v=s;
                }
                else{
                    ex->u=s;
                    ex->v=adjlist->val;
                }
                ex->next=edge_dash;
                edge_dash=ex;
            }
        }
        else if(G[s].parent!=adjlist->val){
            G[s].least=min(G[s].least, G[adjlist->val].d);             
        }
        adjlist=adjlist->next;
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
    lnode* tmp;
    for(long long i=0; i<E; i++){
        scanf("%d %d\n", &u, &v);
        tmp=(lnode*)malloc(sizeof(lnode));
        tmp->val=v;
        tmp->next=NULL;
        G[u].adjv=insertLnode(G[u].adjv, tmp);
        tmp=(lnode*)malloc(sizeof(lnode));
        tmp->val=u;
        tmp->next=NULL;
        G[v].adjv=insertLnode(G[v].adjv, tmp);
    }
    DFS(G, V);
    printGraph(G, V);
}
