#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
long double M_PI = acos(-1.0);

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
        int nx,n;
        scanf("%d",&nx);
        n=nx*2;
        int pw2,o;
        for(o=0;;o++){
            if((n/(int)(pow(2,o)))==0 || n==(int)pow(2,o))
                break;
        }
        pw2=(int)pow(2,o);
        double complex* coff1 = (double complex*)malloc(sizeof(double complex)*pw2);
        double complex* coff2 = (double complex*)malloc(sizeof(double complex)*pw2);
        double x, y;
        for( int j=0; j<pw2; j++ ){
            if(j<nx){
                scanf("%lf",&x);
                scanf("%lf",&y);
                coff1[j] = x+I*y;    
            }
            else{
                coff1[j]= 0;
            }
        }
        for( int j=0; j<pw2; j++ ){
            if(j<nx){
                scanf("%lf",&x);
                scanf("%lf",&y);
                coff2[j] = x+I*y;    
            }
            else{
                coff2[j]= 0;
            }
        }
        double complex *f1, *f2, *cnv=(double complex*)malloc(sizeof(double complex)*pw2);
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
            printf("(%0.3lf,%0.3lf)\n", x, y);
        }
    }
    return 0;
}
