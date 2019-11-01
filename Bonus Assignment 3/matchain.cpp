#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define deffor for(long i=0; i<n; i++)


long getVal(long h[], long n){
    long vals[n][n], j, temp;
    deffor vals[i][i]=0;
    for(long len=2; len<n; len++){
        for(long i=1; i<n-len+1; i++){
            j=i+len-1;
            vals[i][j]=__LONG_MAX__;
            for(long k=i; k<j; k++){
                temp=vals[i][k]+vals[k+1][j]+h[i-1]*h[k]*h[j];
                if(temp<vals[i][j])
                    vals[i][j]=temp;
            }
        }
    }
    return vals[1][n-1];
}

int main() {
    long exec;
    scanf("%ld", &exec);
    for(long e=0; e<exec; e++){
        long n;
        scanf("%ld", &n);
        n++;
        long h[n];
        deffor scanf("%ld", &h[i]);
        long y=getVal(h, n);
        printf("%ld\n", y);
    }
    return 0;
}