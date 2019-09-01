#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#define M_PI 4*atan(1)

int powx(int n){
    int fct=ceil(log2(n));
    fct=pow(2, fct);
    return fct;
}

void pc(double complex x){
    printf("(%.3lf,%.3lf)\n",creal(x), cimag(x));
}

double complex wgen(int n, int k, int inv){
    double theta=(I*2*M_PI/n)*k;
    double complex arr=cexp(theta);
    if(inv)
        arr=cexp(-theta);
    return arr;
}

void fft(double complex r[], double complex arr[], int n, int inv){
    if(n==1){
        r[0]=arr[0];
        return;   
    }
    double complex arre[n/2], arro[n/2], ye[n/2], yo[n/2];
    double complex w, wn=cexp(I*2*M_PI/n);
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
    w = 1;
    double complex temp;
    fft(ye, arre, n/2, inv);
    fft(yo, arro, n/2, inv);
    for(int i=0; i<n/2; i++){
        temp=w * yo[i];
        r[i] = ye[i] + temp;
        r[i+n/2] = ye[i] - temp;
        w *= wn;
    }
}

int main() {
    int t;
    scanf("%d",&t);
    for( int i=0; i<t; i++ ){
        int n;
        scanf("%d",&n);
        if(n==0)
            break;
        int pw2=powx(n);
        double complex coff[pw2];
        int x, y;
        for( int j=0; j<pw2; j++ ){
            if(j<n){
                scanf("%d",&x);
                scanf("%d",&y);
                coff[j] = x + y * I;    
            }
            else{
                coff[j]= 0 + 0 * I;
            }
        }
        double complex ptrep[pw2];
        fft(ptrep, coff, pw2, 0);
        for(int i=0; i<pw2; i++){
            pc(ptrep[i]);
        }
    }
    return 0;
}
