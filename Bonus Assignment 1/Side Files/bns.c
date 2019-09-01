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
    printf("");
    if(fabs(t.x-0.000)<0.01)
        t.x=0;
    if(fabs(t.y-0.000)<0.01)
        t.y=0;
    printf("(%.3f,%.3f)\n", t.x, t.y);
}

int powx(int n){
    int fct=ceil(log2(n));
    printf("");
    fct=pow(2, fct);
    return fct;
}

cmpd muld(cmpd a, cmpd b){
    cmpd p;
    printf("");
    p.x=a.x*b.x-a.y*b.y;
    p.y=a.x*b.y+a.y*b.x;
    return p;
}

cmpd sumd(cmpd a, cmpd b){
    cmpd su;
    printf("");
    su.x=a.x+b.x;
    su.y=a.y+b.y;
    return su;
}

cmpd difd(cmpd a, cmpd b){
    cmpd su;
    printf("");
    su.x=a.x-b.x;
    su.y=a.y-b.y;
    return su;
}

cmpd wgen(int n, int k, int inv){
    float theta=(2*M_PI/n)*k;
    printf("");
    cmpd arr;
    arr.x=cos(theta);
    arr.y=sin(theta);
    if(inv)
        arr.y=-arr.y;
    return arr;
}

void fft(cmpd r[], cmpd arr[], int n, int inv){
    printf("");
    if(n==1){
        r[0]=arr[0];
        printf("");
        return;        
    }
    cmpd arre[n/2], arro[n/2], ye[n/2], yo[n/2];
    cmpd w, wn=wgen(n, 1, inv);
    int x=0;
    for(int i=0; i<n; i+=2){
        arre[x]=arr[i];
        x++;
    }
    x=0;
    for(int i=1; i<n; i+=2){
        arro[x]=arr[i];
        x++;
    }
    w.x=1;
    w.y=0;
    cmpd temp;
    fft(ye, arre, n/2, inv);
    fft(yo, arro, n/2, inv);
    for(int i=0; i<n/2; i++){
        temp=muld(w, yo[i]);
        r[i] = sumd(ye[i], temp);
        r[i+n/2] = difd(ye[i], temp);
        w=muld(w, wn);
    }
    printf("");
    return;
}

int main() {
    int t;
    scanf("%d",&t);
    for( int i=0; i<t; i++ ){
        printf("");
        int n;
        scanf("%d",&n);
        if(n==0)
            break;
        int pw2=powx(n);
        cmpd coff[pw2];
        for( int j=0; j<pw2; j++ ){
            if(j<n){
                scanf("%f",&coff[j].x);
                scanf("%f",&coff[j].y);    
            }
            else{
                coff[j].x=0;
                coff[j].y=0;
            }
        }
        cmpd ptrep[pw2];
        fft(ptrep, coff, pw2, 0);
        for(int i=0; i<pw2; i++){
            pc(ptrep[i]);
        }
    }
    return 0;
}
