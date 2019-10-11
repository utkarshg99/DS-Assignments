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
    int least;
    int parent;
    short articulate;
    // vector<int> adjv;
    lnode* adjv;
} node;

//At initialization, set front and rear to 0
typedef struct queue{
    int arr[MAX_VERTEX];
    int front;
    int rear;
} queue;

long tme;
int dist[MAX_VERTEX];
int xsource;

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
    nx.parent=-1;
    nx.least=0;
    nx.articulate=0;
    // vector<int> x;
    // nx.adjv=x;
    nx.adjv=NULL;
    return nx;
}

lnode* insertLnode(lnode* x, lnode* y){
    lnode* head=x;
    if(x==NULL){
        return y;
    }
    else
    {
        y->next=head;
        return y;
    }
}

void printGraph(node G[], long V){
    // Prints the value of all vertices of the adjacency list in order of occurence. Not DFS or BFS.
    for(int i=0; i<V; i++){
        dist[i]=-1;
        if(G[i].articulate)
            xsource=i;
    }
}

void DFS_Visit(node G[], long s){
    G[s].color=GREY;
    // vector<int> adjlist=G[s].adjv;
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
            if(child>1 && G[s].parent==-1){
                G[s].articulate=1;
            }
            if(G[s].parent!=-1 && G[adjlist->val].least>=G[s].d){
                G[s].articulate=1;
            }
        }
        else if(G[s].parent!=adjlist->val){
            G[s].least=min(G[s].least, G[adjlist->val].d);             
        }
        adjlist=adjlist->next;
    }
    G[s].color=BLACK;
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

void bfs(node G[], long V){
    queue q;
    q.front=0;
    q.rear=0;
    dist[xsource]=0;
    push(&q, xsource);
    int tmp;
    lnode* temp;
    while(!isEmpty(&q)){
        tmp = pop(&q);
        temp=G[tmp].adjv;
        while (temp!=NULL)
        {
            int y=G[tmp].adjv->val;
            if(dist[y]==-1){
                dist[y]=dist[tmp]+1;
                push(&q, G[tmp].adjv->val);
            }
            temp=temp->next;
        }
        
        // for(int i=0; i<G[tmp].adjv.size(); i++){
        //     int y=G[tmp].adjv[i];
        //     if(dist[y]==-1){
        //         dist[y]=dist[tmp]+1;
        //         push(&q, G[tmp].adjv[i]);
        //     }
        // }
    }
}

int main(){
    long V, Q;
    long long E;
    scanf("%ld", &V);
    scanf("%lld", &E);
    scanf("%ld", &Q);
    node G[V];
    for(long i=0; i<V; i++){
        G[i]=getNode(i, i); // the marker argument will always be the index of the array as this is how it is identified in the Adjacency Lists
    }
    int u, v;
    lnode* tmp;
    for(long long i=0; i<E; i++){
        scanf("%d %d\n", &u, &v);
        // G[u].adjv.push_back(v);
        // G[v].adjv.push_back(u);
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
    bfs(G, V);
    for(int i=0; i<Q; i++){
        scanf("%d %d\n", &u, &v);
        printf("%d\n", (dist[u]+dist[v]));
    }
}
