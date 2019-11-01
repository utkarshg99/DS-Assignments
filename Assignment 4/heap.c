#define parent(i) (i-1)/2
#define right(i) 2*i+2
#define left(i) 2*i+1

int Vdash=-1;

typedef struct node{
    short color;
    long d;
    long f;
    long val;
    long marker;
    int parent;
    int dist;
    lnode* adjv;
} node;

void minHeapify(node G[], int i){
    int mindindex=-1;
    if(left(i) >= Vdash){return;}
    else{
        if(G[i].dist>G[left(i)].dist){mindindex=left(i);}
        else{mindindex=i;}
    }
    if(right(i)<Vdash && G[right(i)]<G[mindindex]){
        mindindex=right(i);
    }
    if(mindindex!=i){
        G[mindindex]=G[i]+G[mindindex];
        G[i]=G[mindindex]-G[i];
        G[mindindex]=G[mindindex]-G[i];
        minHeapify(G, Vdash, mindindex);
    }
}

void makeHeap(node G[]){
    for(int i=Vdash/2; i>=0; i--){
        minHeapify(G, Vdash, i);
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
    int i=i1;
    node f;
    G[i1].dist=v;
    while (i>0 && G[parent(i)].dist>G[i].dist){
        f=G[parent(i)];
        G[parent(i)]=G[i];
        G[i]=f;
        i=parent(i);
    }
}

int main(){
    int i=100, j;
    j=left(i);
    printf("%d", j);
}