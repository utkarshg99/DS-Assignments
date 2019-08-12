#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

long long binsearch(long long arrayx[], long long ele, long long low, long long high) 
{ 
   long long mid=(low+high)/2;
   if (high<low) 
       return -1; 
   if (arrayx[mid]==ele) 
       return mid; 
   if (ele>arrayx[mid]) 
       return binsearch(arrayx, ele, mid+1, high); 
   return binsearch(arrayx, ele, low, mid-1); 
} 

long long fndcntr(long long arrayx[], long long low, long long high){
    long long mid=(low+high)/2;
    if(mid==low || mid==high)
        return mid;
    if(arrayx[mid]>arrayx[mid-1] && arrayx[mid]>arrayx[mid+1])
        return mid;
    if(arrayx[low]>arrayx[mid])
        return fndcntr(arrayx, low, mid);
    return fndcntr(arrayx, mid+1, high);
}

int main() {
    int ntest;
    scanf("%d", &ntest);
    for (int j=0; j<ntest; j++){
        long long flg=-1;
        long long k;
        scanf("%lld",&k);
        long long st[k];
        for(long long i=0; i<k; i++){
            scanf("%lld",&st[i]);
        }
        long long ele;
        scanf("%lld", &ele);
        for(long long i=0; i<k; i++){
            if(st[i]==ele){
                flg=i;
                break;
            }
        }
        // long long cntr=fndcntr(st, 0, k-1);
        // if(st[0]>ele)
        //     flg=binsearch(st, ele, cntr+1, k-1);
        // else
        //     flg=binsearch(st, ele, 0, cntr);
        printf("%d\n",flg);
    }  
    return 0;
}