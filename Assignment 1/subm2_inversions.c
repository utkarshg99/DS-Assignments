#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int merge(long long arr[], int low, int high, int mid){
    long long left[mid-low+2];
    left[mid-low+1]=__LONG_MAX__;
    long long right[high-mid+1];
    right[high-mid]=__LONG_MAX__;
    for(int i=low; i<mid+1;i++){
        left[i-low]=arr[i];
    }
    for(int j=mid+1; j<=high; j++){
        right[j-mid-1]=arr[j];
    }
    int l=0, r=0, count=0;
    for(int i=low; i<=high; i++){
        if(left[l]<=right[r]){
            arr[i]=left[l];
            l++;
        }
        else{
            arr[i]=right[r];
            r++;
            count+=(mid-low+1)-(l);
        }
    }
    return count;
}

int merge_sort(long long arr[], int low, int high){
    if(low<high){
        int mid=(low+high)/2;
        int l=merge_sort(arr, low, mid);
        int r=merge_sort(arr, mid+1, high);
        int c=merge(arr, low, high, mid);
        return l+c+r;
    }
    return 0;
}

int main() {
    int ntest;
    scanf("%d", &ntest);
    for (int j=0; j<ntest; j++){
        int k;
        scanf("%d",&k);
        long long st[k];
        for(int i=0; i<k; i++){
            scanf("%lld",&st[i]);
        }
        int invs=merge_sort(st, 0, k-1);
        printf("%d\n", invs);
    }
    return 0;
}