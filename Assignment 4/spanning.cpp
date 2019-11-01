#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define WHITE -1
#define GREY 0
#define BLACK 1
#define MAX_EDGE 10e8
#define MAX_VERTEX 10000
#define MAX_N 100000
#define parent(i) (i-1)/2
#define right(i) 2*i+2
#define left(i) 2*i+1

typedef struct node{
    int parent;
    int marker;
    int rank;
} node;

typedef struct edge{
    long wt;
    int u;
    int v;
    long mark;
} edge;

int Vdash=-1;
long highedge=0;
edge* Edsh;

node getNode(int marker){
    node nx;
    nx.rank=0;
    nx.parent=-1;
    nx.marker=marker;
    return nx;
}

void minHeapify(edge G[], int i){
    int minindex=-1, temp;
    edge f;
    if(left(i) >= Vdash){return;}
    else{
        if(G[i].wt>G[left(i)].wt){minindex=left(i);}
        else{minindex=i;}
    }
    if(right(i)<Vdash && G[right(i)].wt<G[minindex].wt){
        minindex=right(i);
    }
    if(minindex!=i){
        f=G[i];
        G[i]=G[minindex];
        G[minindex]=f;
        minHeapify(G, minindex);
    }
}

void makeHeap(edge G[]){
    for(int i=Vdash/2; i>=0; i--){
        minHeapify(G, i);
    }
}

int extractMin(edge G[]){
    edge f=G[0];
    G[0]=G[Vdash-1];
    G[Vdash-1]=f;
    Vdash--;
    minHeapify(G, 0);
    return Vdash;
}

void decreaseKey(edge G[], int i1, int v){
    int i=i1, temp;
    edge f;
    G[i1].wt=v;
    while (i>0 && G[parent(i)].wt>G[i].wt){
        f=G[parent(i)];
        G[parent(i)]=G[i];
        G[i]=f;
        i=parent(i);
    }
}

void addElement(int u, int v, long wt, int nE){
    edge x;
    x.u=u;
    x.v=v;
    x.wt=wt;
    edge* Edsh2 = (edge*)malloc(sizeof(edge)*nE);
    long i, index=0;
    for(i=0; i<nE-1; i++){
        if(Edsh[i].wt>=wt)
            Edsh2[index++]=Edsh[i];
        else
            break;
    }
    x.mark=index;
    Edsh2[index++]=x;
    for(; i<nE-1; i++){
        Edsh2[index++]=Edsh[i];
    }
    free(Edsh);
    Edsh=Edsh2;
}

void clearnode(node G[], int V){
    for(int i=0; i<V; i++){
        G[i].rank=0;
        G[i].parent=-1;
    }
}

int find(node G[], int x){
    int mrk, x1;
    node tmp;
    tmp=G[x];
    while (tmp.parent!=-1){
        tmp=G[tmp.parent];
    }
    mrk=tmp.marker;
    tmp=G[x];
    while (tmp.parent!=-1){
        x1=tmp.parent;
        tmp=G[x1];
        G[x].parent=mrk;
        x=x1;
    }
    return mrk;
}

void union_set(node* x, node* y){
    if(x->marker==y->marker) return;
    if(x->rank<y->rank){
        x->parent=y->marker;
    }
    else if(x->rank>y->rank){
        y->parent=x->marker;
    }
    else{
        y->parent=x->marker;
        x->rank=(x->rank)++;
    }
}

short checkCycle(node G[], int u, int v, int V){
    int gu = find(G, u);
    int gv = find(G, v);
    if(gu!=gv || (gu==-1)){
        union_set(&G[gu], &G[gv]);
        return 0;
    }
    return 1;
}

long minSpan(edge Edash[], node G[], long E, long lowlim, int V){
    edge temp;
    long wnet=0;
    for(long i=E-1; i>=lowlim; i--){
        temp=Edash[i];
        if(!checkCycle(G, temp.u, temp.v, V)){
            wnet+=temp.wt;
            highedge=i;
        }
    }
    return wnet;
}

int main(){
    long V, E, Q;
    scanf("%ld", &V);
    scanf("%ld", &E);
    scanf("%ld", &Q);
    node G[V];
    edge* Edash=(edge*)malloc(sizeof(edge)*E);
    Edsh=Edash;
    for(long i=0; i<V; i++){
        G[i]=getNode(i);
    }
    long u, v, wt;
    for(long i=0; i<E; i++){
        scanf("%ld %ld %ld", &u, &v, &wt);
        Edash[i].u=u;
        Edash[i].v=v;
        Edash[i].mark=i;
        Edash[i].wt=wt;
    }
    long tmpwt;
    Vdash=E;
    makeHeap(Edsh);
    while(Vdash>0){
        Vdash=extractMin(Edsh);
    }
    tmpwt=minSpan(Edash, G, E, highedge, V);
    printf("%ld\n", tmpwt);
    Vdash=E;
    for(int i=0; i<Q; i++){
        scanf("%ld %ld %ld", &u, &v, &wt);
        if(wt>=Edsh[highedge].wt){
            printf("%ld\n",tmpwt);
            continue;
        }
        addElement(u, v, wt, ++Vdash);
        clearnode(G, V);
        tmpwt=minSpan(Edsh, G, Vdash, highedge, V);
        printf("%ld\n",tmpwt);
    }
}