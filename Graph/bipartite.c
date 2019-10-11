/*
Generates G by taking |V| and |E| as input followed by edges in the format: 'u v'
Also, does a DFS on G
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define WHITE -1
#define GREY 0
#define BLACK 1
#define MAX_EDGE 1000000000
#define MAX_VERTEX 100000
#define MAX_N 100000

typedef struct lnode {
    long val;
    struct lnode* next;
} lnode;

typedef struct node{
    int color;
    long d;
    long f;
    long val;
    long marker;
    lnode *adj;
} node;

typedef struct stack {
   long stck[MAX_N];
   long top;
} stack;

long time;
stack aux_Stack; // Stack functions will use a pointer to the stack struct.

int isEmpty(stack *s){
    return s->top==-1;
}

void push(stack *s, long v){
    s->top++;
    s->stck[s->top]=v;
}

long pop(stack *s){
    s->top--;
    return s->stck[s->top+1];
}

node getNode(long val, long marker){
    node nx;
    nx.color=WHITE;
    nx.d=0;
    nx.f=0;
    nx.val=val;
    nx.adj=NULL;
    nx.marker=marker;
    return nx;
}

lnode* insertLnode(lnode* x, lnode* y){
    lnode* head=x;
    if(x==NULL){
        return y;
    }
    else
    {
        while (x->next!=NULL)
            x=x->next;
        x->next=y;
    }
    return head;
}

void printGraph(node G[], long V){
    // Prints the value of all vertices of the adjacency list in order of occurence. Not DFS or BFS.
    lnode* tmp;
    for(int i=0; i<V; i++){
        tmp=G[i].adj;
        while (tmp!=NULL)
        {
            printf("%d", tmp->val);
            tmp=tmp->next;
        }
        printf("\n");
    }
}

void DFS_Visit(node G[], long s){
    G[s].color=GREY;
    lnode* adjlist=G[s].adj;
    G[s].d=time;
    time+=1;
    while (adjlist!=NULL)
    {
        if(G[adjlist->val].color==WHITE){
            DFS_Visit(G, adjlist->val);
        }
        adjlist=adjlist->next;
    }
    G[s].color=BLACK;
    G[s].f=time;
    time+=1;
}

void DFS(node G[], long V){
    for(long i; i<V; i++){
        if(G[i].color == WHITE){
            time++;
            DFS_Visit(G, i);
        }
    }
}

int bipartite=1;

void colorNode(node G[], long s, int col){
    if(G[s].color==WHITE){
        G[s].color=col;
    }
    lnode* nd = G[s].adj;
    while (nd!=NULL)
    {
        node neigh = G[nd->val];
        if(neigh.color==col){
            bipartite=0;
            return;
        }
        else if(neigh.color==WHITE){
            colorNode(G, nd->val, !col);
        }         
        nd=nd->next;
    }
}

void findBipartite(node G[], int V){
    for(int i=0; i<V; i++){
        if(G[i].color==WHITE)
            colorNode(G, i, GREY);
    }
}

int main(){
    int t;
    scanf("%d", &t);
    for(int exec=0; exec<t; exec++)
    {
        long V, E;
        time=0;
        bipartite=1;
        aux_Stack.top=-1;
        scanf("%ld", &V);
        scanf("%ld", &E);
        node G[V];
        for(long i=0; i<V; i++){
            G[i]=getNode(i, i); // the marker argument will always be the index of the array as this is how it is identified in the Adjacency Lists
        }
        long u, v;
        lnode* tmp;
        for(long i=0; i<E; i++){
            scanf("%ld %ld", &u, &v);
            u-=1;
            v-=1;
            tmp=(lnode*)malloc(sizeof(lnode));
            tmp->val=v;
            tmp->next=NULL;
            G[u].adj=insertLnode(G[u].adj, tmp);
            tmp=(lnode*)malloc(sizeof(lnode));
            tmp->val=u;
            tmp->next=NULL;
            G[v].adj=insertLnode(G[v].adj, tmp);
        }
        findBipartite(G, V);
        if(bipartite)
            printf("Yes\n");
        else
            printf("No\n");
    }
}