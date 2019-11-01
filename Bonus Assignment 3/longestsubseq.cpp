#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int getVal(char* str1, char* str2, int m, int n){
    int vals[2][n+1];
    for(int i=0; i<=1; i++)
        for(int j=0; j<=n; j++)
            vals[i][j]=0;
    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++){
            if(i==0 || j==0)
                vals[i%2][j]=0;
            else if(str1[i-1]==str2[j-1])
                vals[i%2][j]=1+vals[(i-1)%2][j-1];
            else
                vals[i%2][j]=(vals[(i-1)%2][j]>vals[i%2][j-1])?vals[(i-1)%2][j]:vals[i%2][j-1];
        }
    }
    return vals[m%2][n];
}

int main() {
    long exec;
    scanf("%ld", &exec);
    for(long e=0; e<exec; e++){
        int m, n;
        scanf("%d %d", &m, &n);
        char* str1=(char*)malloc(sizeof(char)*(m+1));
        char* str2=(char*)malloc(sizeof(char)*(n+1));
        scanf("%s", str1);
        scanf("%s", str2);
        str1[m]='\n';
        str2[n]='\n';
        int val=getVal(str1, str2, m, n);
        printf("%d\n",val);
        free(str1);
        free(str2);
    }
    return 0;
}
