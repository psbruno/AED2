#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
int setachar(char **A, int i,int j){
    if(A[i][j]<=' ')
        return 0;
    else
        return (A[i][j]-96);
 
}
 
 
 
 
 
void CountingSort(char **A,int n, int coluna_radix){
     int x;
     char B[n][15];
     int i,k=27,j;
     int C[27],y;
 
     for(i=0;i<27;i++)
         C[i]=0;
 
    for(j=0;j<n;j++){
        C[setachar(A,j,coluna_radix)]++;
    }
 
 
    for (i = 1; i < k; i++)
        C[i] += C[i-1];
    for(i=0;i<27;i++)
        printf("%d ",C[i]);
    printf("\n");
 
    for(i=0;i<n;i++){
        for(y=0;y<15;y++)
            B[i][y]=32;
    }
 
 
    for(j = n - 1; j >= 0; j--){
            for(y=0;y<15;y++)
                B[C[setachar(A,j,coluna_radix)]-1][y] = A[j][y];
            C[setachar(A,j,coluna_radix)]--;
    }
 
 
    for (j = 0; j < n; j++) {
          for(y=0;y<15;y++)
             A[j][y] = B[j][y];
     }
 
}
 
 
 
void RadixSort(char **nomes, int n,int d){
     int i=0,j,a=d-1;
     int x;
 
 
     for (i = d-1; i >= 0; i--){//esse for funcionar de forma equivalente ao Radix Sort
         CountingSort(nomes,n,i);
     }
 }
 
 
 
int main (){
     int i,N,L=0,j,d=0,P,M;
     scanf("%d", &N);
     char **nomes;
      nomes=(char**)malloc(N*sizeof(char*));
      for(i=0;i<15;i++){
         nomes[i]=(char*)malloc(15*sizeof(char));
     }
 
 
 
    for(i=0;i<N;i++)
         for(j=0;j<15;j++)
             nomes[i][j]=' ';
 
     for(i=0;i<N;i++)
          scanf("%s", nomes[i]);
 
     for(i=0;i<N;i++){
        for(j=0;j<strlen(nomes[i]);j++){
            if(nomes[i][j]<'a')
                nomes[i][j]+=32;
 
        }
        if(strlen(nomes[i])>d) {
            d=strlen(nomes[i]);
        }
     }
 
     RadixSort(nomes,N,d);
    scanf("%d %d",&P,&M);
    for(i=P-1;M>0;i++){
            printf("%s", nomes[i]);
    M--;
        printf("\n");
    }
 
        return 0;
}
