#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#define M_PI acos(-1)

int powx(int n){
    int fct=ceil(log2(n));
    fct=(int)pow(2, fct);
    return fct;
}

double complex* fft(double complex* arr, int n, int inv){
    if(n<=1){
        return arr;   
    }
    double complex *arre, *arro, *ye, *yo, *y;
    y = (double complex*)malloc(sizeof(double complex)*n);
    arre = (double complex*)malloc(sizeof(double complex)*(n/2));
    arro = (double complex*)malloc(sizeof(double complex)*(n/2));
    double complex w;
    double complex wn;
    if(inv == 1)
        wn = cexp(-1*I*2*M_PI/n);
    else
        wn = cexp(I*2*M_PI/n);
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
        int n;
        scanf("%d",&n);
        // int pw2=powx(n);
        int pw2,o;
        for(o=0;;o++){
            if((n/(int)(pow(2,o)))==0 || n==(int)pow(2,o))
                break;
        }
        pw2=(int)pow(2,o);
        double complex* coff = (double complex*)malloc(sizeof(double complex)*pw2);
        double x, y;
        for( int j=0; j<pw2; j++ ){
            if(j<n){
                scanf("%lf",&x);
                scanf("%lf",&y);
                coff[j] = x+I*y;    
            }
            else{
                coff[j]= 0;
            }
        }
        double complex* ptrep;
        ptrep = fft(coff, pw2, 0);
        for(int i=0; i<pw2; i++){
            printf("(%0.3lf,%0.3lf)\n",creal(ptrep[i]), cimag(ptrep[i]));
        }
    }
    return 0;
}
