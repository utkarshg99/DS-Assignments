#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
long double M_PI = 3.141592653589789;

long double complex* fft(long double complex* arr, int n, int inv){
    if(n<=1){
        return arr;   
    }
    long double complex *arre, *arro, *ye, *yo, *y;
    y = (long double complex*)malloc(sizeof(long double complex)*n);
    arre = (long double complex*)malloc(sizeof(long double complex)*(n/2));
    arro = (long double complex*)malloc(sizeof(long double complex)*(n/2));
    long double complex w;
    long double complex wn;
    if(inv == 1){
        long double complex theta = -1*I*2*M_PI/n;
        wn = cexp(theta);
    }
    else{
        long double complex theta = I*2*M_PI/n;
        wn = cexp(theta);        
    }
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
    long double complex temp;
    ye = fft(arre, n/2, inv);
    yo = fft(arro, n/2, inv);
    for(int i=0; i<n/2; i++){
        temp=w * yo[i];
        y[i] = ye[i] + temp;
        y[i+n/2] = ye[i] - temp;
        w *= wn;
    }
    free(ye);
    free(yo);
    return y;
}

int main() {
    int t;
    scanf("%d",&t);
    for(int i=0; i<t; i++){
        int nx,n;
        scanf("%d",&nx);
        n=nx*2;
        int pw2,o;
        for(o=0;;o++){
            if((n/(int)(pow(2,o)))==0 || n==(int)pow(2,o))
                break;
        }
        pw2=(int)pow(2,o);
        long double complex* coff1 = (long double complex*)malloc(sizeof(long double complex)*pw2);
        long double complex* coff2 = (long double complex*)malloc(sizeof(long double complex)*pw2);
        long double x, y;
        for( int j=0; j<pw2; j++ ){
            if(j<nx){
                scanf("%llf",&x);
                scanf("%llf",&y);
                coff1[j] = x+I*y;    
            }
            else{
                coff1[j]= 0;
            }
        }
        for( int j=0; j<pw2; j++ ){
            if(j<nx){
                scanf("%llf",&x);
                scanf("%llf",&y);
                coff2[j] = x+I*y;    
            }
            else{
                coff2[j]= 0;
            }
        }
        long double complex *f1, *f2, *cnv=(long double complex*)malloc(sizeof(long double complex)*pw2);
        f1 = fft(coff1, pw2, 0);
        f2 = fft(coff2, pw2, 0);
        for(int o=0; o<pw2; o++){
            cnv[o]=f1[o]*f2[o];
        }
        cnv = fft(cnv, pw2, 1);
        // inv fft with coffs pw2 times
        for(int i=0; i<pw2; i++){
            x=creal(cnv[i])/pw2;
            y=cimag(cnv[i])/pw2;
            if(fabs(x)<0.01)
                x=0;
            if(fabs(y)<0.01)
                y=0;
            printf("(%0.3llf,%0.3llf)\n", x, y);
        }
    }
    return 0;
}
