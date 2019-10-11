#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


/*
Generates G by taking |V| and |E| as input followed by edges in the format: 'u v'
Also, does a DFS on G
*/

#define WHITE -1
#define GREY 0
#define BLACK 1
#define MAX_EDGE 1000000000
#define MAX_VERTEX 10000
#define MAX_N 100000
#define MAX_Q 20000

typedef struct node{
    // int color;
    // long d;
    // long f;
    // long val;
    // long marker;
    // int dist;
    vector<int> adjv;
} node;

//At initialization, set front and rear to 0
typedef struct queue{
    int arr[MAX_VERTEX];
    int front;
    int rear;
} queue;

long tme;

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
    // nx.color=WHITE;
    // nx.d=0;
    // nx.f=0;
    // nx.val=val;
    vector<int> x;
    nx.adjv=x;
    // nx.dist=-1;
    // nx.marker=marker;
    return nx;
}

int dist[MAX_VERTEX];

void printGraph(node G[], long V){
    // Prints the value of all vertices of the adjacency list in order of occurence. Not DFS or BFS.
    for(int i=0; i<V; i++){
        // vector<int> tmp=G[i].adjv;
        // for (int i = 0; i < tmp.size(); i++) 
        //     cout << tmp[i] << " "; 
        // printf("\n");
        printf("%d\n", dist[i]);
    }
}

// void DFS_Visit(node G[], long s){
//     G[s].color=GREY;
//     vector<int> adjlist=G[s].adjv;
//     G[s].d=tme;
//     tme+=1;
//     for (int i = 0; i < adjlist.size(); i++) 
//         if(G[adjlist[i]].color==WHITE)
//             DFS_Visit(G, adjlist[i]);
//     G[s].color=BLACK;
//     G[s].f=tme;
//     tme+=1;
// }

// void DFS(node G[], long V){
//     for(long i; i<V; i++){
//         if(G[i].color == WHITE){
//             tme++;
//             DFS_Visit(G, i);
//         }
//     }
// }

void bfs(node G[], long V){
    queue q;
    q.front=0;
    q.rear=0;
    int dx=0;
    dist[2]=dx;
    push(&q, 2);
    int tmp;
    while(!isEmpty(&q)){
        // dx++;
        tmp = pop(&q);
        for(int i=0; i<G[tmp].adjv.size(); i++){
            int y=G[tmp].adjv[i];
            if(dist[y]==-1){
                dist[y]=dist[tmp]+1;
                push(&q, G[tmp].adjv[i]);
            }
        }
    }
}

int main(){
    // int t;
    // scanf("%d", &t);
    // for(int exec=0; exec<t; exec++)
    // {
    long V, E, Q;
    scanf("%ld", &V);
    scanf("%ld", &E);
    scanf("%ld", &Q);
    node G[V];
    for(long i=0; i<V; i++){
        dist[i]=-1;
        G[i]=getNode(i, i); // the marker argument will always be the index of the array as this is how it is identified in the Adjacency Lists
    }
    int u, v;
    for(long i=0; i<E; i++){
        scanf("%d %d\n", &u, &v);
        // u-=1;
        // v-=1;
        G[u].adjv.push_back(v);
        G[v].adjv.push_back(u);
    }
    bfs(G, V);
    // printGraph(G, V);
    for(int i=0; i<Q; i++){
        scanf("%d %d\n", &u, &v);
        printf("%d\n", dist[u]+dist[v]);
    }
    // }
}
