#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxn 1000010

typedef struct stack {
   long stck[maxn];
   long top;
} stack;

int isEmpty(stack *s){
    return s->top==0;
}

void push(stack *s, long v){
    s->top++;
    s->stck[s->top]=v;
}

long pop(stack *s){
    s->top--;
    return s->stck[s->top+1];
}

void print(long arr[], long n){
    for(long i=1; i<n; i++){
        printf("%ld\n", arr[i]);
    }
}

void span(long arr[], long n){
    stack s;
    s.top=-1;
    push(&s, __LONG_MAX__);
    long h[n+1], spanx[n+1];
    for(long i=1; i<=n; i++){
        while(!isEmpty(&s) && arr[i]>=arr[s.stck[s.top]]){
            pop(&s);
        }
        if(isEmpty(&s)){
            push(&s, i);
            h[i]=i;
            spanx[i]=i;
        }
        else{
            h[i]=s.stck[s.top];
            push(&s, i);
            spanx[i]=i-h[i];
        }
    }
    print(spanx, n+1);
}

int main() {
    int ntest=0;
    scanf("%d", &ntest);
    for(int j=0; j<ntest; j++){
        long n;
        scanf("%ld", &n);
        long arr[n+1];
        for(int i=1;i<=n;i++){
            scanf("%ld", &arr[i]);
        }
        span(arr, n);
    }
    return 0;
}