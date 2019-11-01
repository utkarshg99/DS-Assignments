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

typedef struct lnode{
    lnode* next;
    long w;
    int val;
} lnode;
typedef struct node{
    short color;
    int parent;
    int pi;
    int marker;
    int rank;
    long wt;
    lnode* adjv;
} node;
typedef struct edge{
    long wt;
    int u;
    int v;
    short exist;
    long mark;
} edge;

int Vdash=-1;
long* Emark;
long highedge=0;
node* grph;
int bigV;
int xyz;

node getNode(int marker){
    node nx;
    nx.color=WHITE;
    nx.adjv=NULL;
    nx.rank=0;
    nx.parent=-1;
    nx.pi=-1;
    nx.wt=-1;
    nx.marker=marker;
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
        long lo=Emark[G[i].mark];
        Emark[G[i].mark]=Emark[G[minindex].mark];
        Emark[G[minindex].mark]=lo;
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
    long lo=Emark[G[0].mark];
    Emark[G[0].mark]=Emark[G[Vdash-1].mark];
    Emark[G[Vdash-1].mark]=lo;
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
        long lo=Emark[G[i].mark];
        Emark[G[i].mark]=Emark[G[parent(i)].mark];
        Emark[G[parent(i)].mark]=lo;
        f=G[parent(i)];
        G[parent(i)]=G[i];
        G[i]=f;
        i=parent(i);
    }
}
void clearnode(node G[], int V){
    for(int i=0; i<V; i++){
        G[i].rank=0;
        G[i].parent=-1;
        G[i].pi=-1;
        G[i].color=WHITE;
        G[i].wt=0;
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
        x->parent=y->marker;
        y->rank=(y->rank)++;
    }
}

void DFS_Visit(node G[], long s){
    G[s].color=GREY;
    lnode* adjlist=G[s].adjv;
    while(adjlist!=NULL){
        if(G[adjlist->val].color==WHITE){
            G[adjlist->val].pi=s;
            G[adjlist->val].wt=adjlist->w;
            DFS_Visit(G, adjlist->val);
            if(adjlist->val == xyz || xyz==-1){
                xyz=-1;
                return;
            }
        }
        adjlist=adjlist->next;
    }
    G[s].color=BLACK;
}

void removeEdge(node G[], int u, int v){
    lnode* temp;
    temp=G[u].adjv;
    while (temp!=NULL){
        if(temp->next!=NULL && temp->next->val==v){
            temp->next=temp->next->next;
        }
        temp=temp->next;
    }
    if(G[u].adjv->val==v){
        G[u].adjv=G[u].adjv->next;
    }
    temp=G[v].adjv;
    while (temp!=NULL){
        if(temp->next!=NULL && temp->next->val==u){
            temp->next=temp->next->next;
        }
        temp=temp->next;
    }
    if(G[v].adjv->val==u){
        G[v].adjv=G[v].adjv->next;
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
    lnode* tmp=NULL;
    long wnet=0;
    int o=0;
    for(long i=E-1; i>=lowlim; i--){
        temp=Edash[i];
        if(!checkCycle(G, temp.u, temp.v, V)){
            tmp=(lnode*)malloc(sizeof(lnode));
            tmp->val=temp.v;
            tmp->next=NULL;
            tmp->w=temp.wt;
            G[temp.u].adjv=insertLnode(G[temp.u].adjv, tmp);
            tmp=(lnode*)malloc(sizeof(lnode));
            tmp->val=temp.u;
            tmp->next=NULL;
            tmp->w=temp.wt;
            G[temp.v].adjv=insertLnode(G[temp.v].adjv, tmp);
            wnet+=temp.wt;
            highedge=i;
            o++;
        }
    }
    return wnet;
}

long getMaxWt(node G[], int u, int v, long wt){
    xyz=v;
    DFS_Visit(G, u);
    int m, n;
    int rv;
    rv=v;
    int maxwt=wt;
    while (rv!=-1){
        if (G[rv].wt>maxwt){
            maxwt=G[rv].wt;
            n=rv;
        }
        rv=G[rv].pi;
    }
    if(maxwt==wt)
        return maxwt;
    lnode* tmp;
    removeEdge(G, n, G[n].pi);
    tmp=(lnode*)malloc(sizeof(lnode));
    tmp->val=v;
    tmp->next=NULL;
    tmp->w=wt;
    G[u].adjv=insertLnode(G[u].adjv, tmp);
    tmp=(lnode*)malloc(sizeof(lnode));
    tmp->val=u;
    tmp->next=NULL;
    tmp->w=wt;
    G[v].adjv=insertLnode(G[v].adjv, tmp);
    return maxwt;
    
}

int main(){
    long V, E, Q;
    scanf("%ld", &V);
    scanf("%ld", &E);
    scanf("%ld", &Q);
    node G[V];
    edge Edash[E];
    grph=G;
    bigV=V;
    long Emr[E];
    Emark=Emr;
    for(long i=0; i<V; i++){
        G[i]=getNode(i);
    }
    long u, v, wt;
    lnode *tmp;
    for(long i=0; i<E; i++){
        scanf("%ld %ld %ld", &u, &v, &wt);
        Emark[i]=i;
        Edash[i].u=u;
        Edash[i].v=v;
        Edash[i].mark=i;
        Edash[i].wt=wt;
        Edash[i].exist=1;
    }
    long wnet, tmpwt=0;
    Vdash=E;
    makeHeap(Edash);
    while(Vdash>0){
        Vdash=extractMin(Edash);
    }
    wnet=minSpan(Edash, G, E, highedge, V);
    printf("%ld\n", wnet);
    for(int i=0; i<Q; i++){
        scanf("%ld %ld %ld", &u, &v, &wt);
        if(wt<Edash[highedge].wt){
            clearnode(G, V);
            tmpwt=getMaxWt(G, u, v, wt);
            wnet=wnet-tmpwt+wt;
        }
        printf("%ld\n", wnet);
    }
}