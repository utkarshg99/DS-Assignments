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
#define MAX_VERTEX 100000
#define MAX_N 100000

typedef struct node{
    int color;
    long d;
    long f;
    long val;
    long marker;
    vector<int> adjv;
} node;

long tme;

node getNode(long val, long marker){
    node nx;
    nx.color=WHITE;
    nx.d=0;
    nx.f=0;
    nx.val=val;
    vector<int> x;
    nx.adjv=x;
    nx.marker=marker;
    return nx;
}

void printGraph(node G[], long V){
    // Prints the value of all vertices of the adjacency list in order of occurence. Not DFS or BFS.
    for(int i=0; i<V; i++){
        vector<int> tmp=G[i].adjv;
        for (int i = 0; i < tmp.size(); i++) 
            cout << tmp[i] << " "; 
        printf("\n");
    }
}

void DFS_Visit(node G[], long s){
    G[s].color=GREY;
    vector<int> adjlist=G[s].adjv;
    G[s].d=tme;
    tme+=1;
    for (int i = 0; i < adjlist.size(); i++) 
        if(G[adjlist[i]].color==WHITE)
            DFS_Visit(G, adjlist[i]);
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

int bipartite=1;

void colorNode(node G[], long s, int col){
    if(G[s].color==WHITE){
        G[s].color=col;
    }
    vector<int> nd=G[s].adjv;
    for(int i=0; i<nd.size(); i++){
        if(!bipartite)
            return;
        node neigh = G[nd[i]];
        if(neigh.color==col){
            bipartite=0;
            return;
        }
        else if(neigh.color==WHITE){
            colorNode(G, nd[i], !col);
        }
    }
}

void findBipartite(node G[], int V){
    for(int i=0; i<V; i++){
        if(G[i].color==WHITE && bipartite)
            colorNode(G, i, GREY);
    }
}

int main(){
    int t;
    scanf("%d", &t);
    for(int exec=0; exec<t; exec++)
    {
        long V, E;
        bipartite=1;
        scanf("%ld", &V);
        scanf("%ld", &E);
        node G[V];
        for(long i=0; i<V; i++){
            G[i]=getNode(i, i); // the marker argument will always be the index of the array as this is how it is identified in the Adjacency Lists
        }
        long u, v;
        for(long i=0; i<E; i++){
            scanf("%ld %ld", &u, &v);
            u-=1;
            v-=1;
            G[u].adjv.push_back(v);
            G[v].adjv.push_back(u);
        }
        findBipartite(G, V);
        if(bipartite)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
