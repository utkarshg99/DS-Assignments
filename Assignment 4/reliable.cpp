#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define WHITE -1
#define GREY 0
#define BLACK 1
#define MAX_EDGE 6250000
#define MAX_VERTEX 2500
#define MAX_N 100000
#define MAX_W 10000
#define parent(i) (i-1)/2
#define right(i) 2*i+2
#define left(i) 2*i+1

typedef struct lnode{
    lnode* next;
    int w;
    int val;
} lnode;

typedef struct node{
    short color;
    long d;
    long f;
    long val;
    long marker;
    int parent;
    long dist;
    lnode* adjv;
} node;

long tme;
int Vdash=-1;
int Y[MAX_VERTEX];

node getNode(long val, long marker){
    node nx;
    nx.color=WHITE;
    nx.d=0;
    nx.f=0;
    nx.val=val;
    nx.adjv=NULL;
    nx.marker=marker;
    nx.parent=-1;
    nx.dist=__LONG_MAX__;
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

void minHeapify(node G[], int i){
    int minindex=-1, temp;
    node f;
    if(left(i) >= Vdash){return;}
    else{
        if(G[i].dist>G[left(i)].dist){minindex=left(i);}
        else{minindex=i;}
    }
    if(right(i)<Vdash && G[right(i)].dist<G[minindex].dist){
        minindex=right(i);
    }
    if(minindex!=i){
        temp=Y[G[i].val];
        Y[G[i].val]=Y[G[minindex].val];
        Y[G[minindex].val]=temp;
        f=G[i];
        G[i]=G[minindex];
        G[minindex]=f;
        minHeapify(G, minindex);
    }
}

void makeHeap(node G[]){
    for(int i=Vdash/2; i>=0; i--){
        minHeapify(G, i);
    }
}

int extractMin(node G[]){
    node f=G[0];
    G[0]=G[Vdash-1];
    G[Vdash-1]=f;
    Vdash--;
    minHeapify(G, 0);
    return Vdash;
}

void decreaseKey(node G[], int i1, int v){
    int i=i1, temp;
    node f;
    G[i1].dist=v;
    while (i>0 && G[parent(i)].dist>G[i].dist){
        temp=Y[G[parent(i)].val];
        Y[G[parent(i)].val]=Y[G[i].val];
        Y[G[i].val]=temp;
        f=G[parent(i)];
        G[parent(i)]=G[i];
        G[i]=f;
        i=parent(i);
    }
}

void dijkstra(node G[], int V, int src){
    int x;
    Vdash=V;
    lnode* tmp;
    node extnode;
    G[src].dist=0;
    makeHeap(G);
    for(int u=0; u<V; u++){
        x=extractMin(G);
        extnode=G[x];
        extnode.color=BLACK;
        tmp=extnode.adjv;
        while (tmp!=NULL){
            if(G[Y[tmp->val]].color!=BLACK && G[Y[tmp->val]].dist>extnode.dist+tmp->w){
                decreaseKey(G, Y[tmp->val], extnode.dist+tmp->w);
            }
            tmp=tmp->next;
        }
    }
}

int main(){
    long V, E;
    scanf("%ld", &V);
    scanf("%ld", &E);
    node G[V];
    for(long i=0; i<V; i++){
        Y[i]=i;
        G[i]=getNode(i, i); // the marker argument will always be the index of the array as this is how it is identified in the Adjacency Lists
    }
    long u, v, wt;
    lnode *tmp;
    for(long i=0; i<E; i++){
        scanf("%ld %ld %ld", &u, &v, &wt);
        // u-=1;
        // v-=1;
        tmp=(lnode*)malloc(sizeof(lnode));
        tmp->val=v;
        tmp->next=NULL;
        tmp->w=wt;
        G[u].adjv=insertLnode(G[u].adjv, tmp);
    }
    scanf("%ld %ld", &u, &v);
    dijkstra(G, V, u);
    for(int i=0; i<V; i++){
        if(G[i].val==v){
            printf("%ld\n", G[i].dist);
        }
    }
}

/*
5 14
0 1 2
1 0 2
1 2 1
2 1 1
0 2 1
2 0 1
1 4 3
4 1 3
1 3 2
3 1 2
2 4 4
4 2 4
3 4 2
4 3 2
0 1
*/