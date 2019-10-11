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

// Set this to 1 to use vectors and 0 to use Linked List
short vectorize=0;
long tme;
int xsource;

int dist[MAX_VERTEX];

typedef struct lnode{
    long val;
    lnode* next;
} lnode;

typedef struct node{
    short color;
    int d;
    int f;
    int least;
    int parent;
    short articulate;
    vector<int> adjv;
    lnode* adjl;
} node;

//At initialization, set front and rear to 0
typedef struct queue{
    int arr[MAX_VERTEX];
    int front;
    int rear;
} queue;

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
    nx.f=0;
    nx.parent=-1;
    nx.least=0;
    nx.articulate=0;
    if(vectorize){
        vector<int> x;
        nx.adjv=x;
    }
    else
    {
        nx.adjl=NULL;
    }
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

void printArticulateSinglet(node G[], long V){
    // Prints the value of all vertices of the adjacency list in order of occurence. Not DFS or BFS.
    for(int i=0; i<V; i++){
        dist[i]=-1;
        if(G[i].articulate)
            xsource=i;
    }
}

void DFS_Visit(node G[], long s){
    G[s].color=GREY;
    vector<int> adjlist=G[s].adjv;
    lnode* adjli=G[s].adjl;
    G[s].d=tme;
    G[s].least=tme;
    tme+=1;
    int child=0;
    if(vectorize){
        for (int i = 0; i < adjlist.size(); i++){
            if(G[adjlist[i]].color==WHITE){
                child++;
                G[adjlist[i]].parent=s;
                DFS_Visit(G, adjlist[i]);
                G[s].least=min(G[s].least, G[adjlist[i]].least);
                /*
                // Uncomment this area to get Articulate Points
                if(child>1 && G[s].parent==-1){
                    G[s].articulate=1;
                }
                if(G[s].parent!=-1 && G[adjlist[i]].least>=G[s].d){
                    G[s].articulate=1;
                }
               */
            }
            else if(G[s].parent!=adjlist[i]){
                G[s].least=min(G[s].least, G[adjlist[i]].d);             
            }
        }
    }
    else
    {
        while(adjli!=NULL){
            if(G[adjli->val].color==WHITE){
                child++;
                G[adjli->val].parent=s;
                DFS_Visit(G, adjli->val);
                G[s].least=min(G[s].least, G[adjli->val].least);
                /*
                // Uncomment this area to get Articulate Points
                if(child>1 && G[s].parent==-1){
                    G[s].articulate=1;
                }
                if(G[s].parent!=-1 && G[adjli->val].least>=G[s].d){
                    G[s].articulate=1;
                }
               */
            }
            else if(G[s].parent!=adjli->val){
                G[s].least=min(G[s].least, G[adjli->val].d);             
            }
            adjli=adjli->next;
        }
    }
    G[s].color=BLACK;
    G[s].f=tme;
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
    lnode* xn;
    q.front=0;
    q.rear=0;
    dist[xsource]=0;
    push(&q, xsource);
    int tmp;
    while(!isEmpty(&q)){
        tmp = pop(&q);
        if(vectorize){
            for(int i=0; i<G[tmp].adjv.size(); i++){
                int y=G[tmp].adjv[i];
                if(dist[y]==-1){
                    dist[y]=dist[tmp]+1;
                    push(&q, G[tmp].adjv[i]);
                }
            }
        }
        else
        {
            xn=G[tmp].adjl;
            while (xn!=NULL)
            {
                if(dist[xn->val]==-1){
                    dist[xn->val]=dist[tmp]+1;
                    push(&q, xn->val);
                }
                xn=xn->next;
            }
            
        }
        
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
        // U-=1;
        // v-=1;
        if(vectorize){
            G[u].adjv.push_back(v);
            G[v].adjv.push_back(u);
        }
        else
        {
            tmp=(lnode*)malloc(sizeof(lnode));
            tmp->val=v;
            tmp->next=NULL;
            G[u].adjl=insertLnode(G[u].adjl, tmp);
            tmp=(lnode*)malloc(sizeof(lnode));
            tmp->val=u;
            tmp->next=NULL;
            G[v].adjl=insertLnode(G[v].adjl, tmp);
        }
        
    }
    DFS(G, V);
    printArticulateSinglet(G, V);
    bfs(G, V);
    for(int i=0; i<Q; i++){
        scanf("%d %d\n", &u, &v);
        printf("%d\n", (dist[u]+dist[v]));
    }
}
