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

long timex=0;
long time=0;
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
    }
}

void DFS_Visit(node G[], long s, int x){
    // printf("%ld",s);
    G[s].color=GREY;
    lnode* adjlist=G[s].adj;
    G[s].d=time;
    time+=1;
    while (adjlist!=NULL)
    {
        if(G[adjlist->val].color==WHITE){
            DFS_Visit(G, adjlist->val, x);
        }
        adjlist=adjlist->next;
    }
    G[s].color=BLACK;
    G[s].f=time;
    time+=1;
    if(x==1)
        push(&aux_Stack, s);
}

void DFS(node G[], long V){
    for(long i; i<V; i++){
        if(G[i].color == WHITE){
            time++;
            DFS_Visit(G, i, 1);
        }
    }
}

int main(){
    int t;
    scanf("%d",&t);
    long V, E;
    for(int exec=0; exec<t; exec++){
        time=0;
        timex=0;
        aux_Stack.top=-1;
        scanf("%ld", &V);
        scanf("%ld", &E);
        node G[V], revG[V];
        for(long i=0; i<V; i++){
            G[i]=getNode(i, i); // the marker argument will always be the index of the array as this is how it is identified in the Adjacency Lists
            revG[i]=getNode(i, i);
        }
        long u, v;
        lnode* tmp;
        for(long i=0; i<E; i++){
            scanf("%ld %ld", &u, &v);
            tmp=(lnode*)malloc(sizeof(lnode));
            tmp->val=v;
            tmp->next=NULL;
            G[u].adj=insertLnode(G[u].adj, tmp);
            tmp=(lnode*)malloc(sizeof(lnode));
            tmp->val=u;
            tmp->next=NULL;
            revG[v].adj=insertLnode(revG[v].adj, tmp);
        }
        DFS(G, V);
        while(!isEmpty(&aux_Stack))
        {
            u=pop(&aux_Stack);
            if(revG[u].color==WHITE){
                time=0;
                DFS_Visit(revG, u, 0);
                timex=(time>timex)?time:timex;
            }
        }
        printf("%ld\n", timex/2);
    }
}

/*
SAMPLE INPUT:
1
12
17
0 1
1 2
2 4
4 2
1 3
3 4
3 1
3 5
3 6
4 7
7 10
10 11
11 8
8 6
6 9
9 8
6 7
ANSWER:
6
*/