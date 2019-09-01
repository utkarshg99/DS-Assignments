#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.141592

typedef struct cmpd {
   float x;
   float y;
} cmpd;

void pc(cmpd t){
    if(fabs(t.x-0.000)<0.01)
        t.x=0;
    if(fabs(t.y-0.000)<0.01)
        t.y=0;
    printf("(%.3f,%.3f)\n", t.x, t.y);
}

int powx(int n){
    int fct=ceil(log2(n));
    fct=pow(2, fct);
    return fct;
}

cmpd muld(cmpd a, cmpd b){
    cmpd p;
    p.x=a.x*b.x-a.y*b.y;
    p.y=a.x*b.y+a.y*b.x;
    return p;
}

cmpd sumd(cmpd a, cmpd b){
    cmpd su;
    su.x=a.x+b.x;
    su.y=a.y+b.y;
    return su;
}

cmpd difd(cmpd a, cmpd b){
    cmpd su;
    su.x=a.x-b.x;
    su.y=a.y-b.y;
    return su;
}

cmpd wgen(int n, int k){
    float theta=(2*M_PI/n)*k;
    cmpd arr;
    arr.x=cos(theta);
    arr.y=sin(theta);
    return arr;
}

void evalpoly(cmpd coff[], cmpd w[], int n, cmpd arr[]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            arr[i]=sumd(arr[i], muld(coff[j], w[j]));
        }
    }
}

int main() {
    int t;
    scanf("%d",&t);
    cmpd zero;
    zero.x=0;
    zero.y=0;
    for( int i=0; i<t; i++ ){
        int n;
        scanf("%d",&n);
        if(n==0)
            break;
        int pw2=powx(n);
        // printf("%d",pw2);
        cmpd coff[pw2];
        cmpd ptrep[pw2];
        cmpd w[pw2];
        for( int j=0; j<pw2; j++ ){
            if(j<n){
                scanf("%f",&coff[j].x);
                scanf("%f",&coff[j].y);    
            }
            else{
                coff[j].x=0;
                coff[j].y=0;
            }
            ptrep[j]=zero;
            w[j]=wgen(pw2, j);
        }
        evalpoly(ptrep, coff, pw2);
        for(int i=0; i<pw2; i++){
            pc(ptrep[i]);
        }
    }
    return 0;
}
