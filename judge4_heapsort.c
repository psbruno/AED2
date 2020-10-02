#include <stdio.h>
 
#include <stdlib.h>
 
 
 
 
 
int swap(int a,int b, int *A){
 
    int aux;
 
    aux=A[b];
 
    A[b]=A[a];
 
    A[a]=aux;
 
 
 
}
 
 
 
 
 
 
 
int MaxHeapify(int *A, int i,int n){
 
    int l, r,max;
 
    l =2*i;
 
    r =2*i+1;
 
    if((l<=n) && (A[l]>A[i]))
 
       max = l;
 
     else max = i;
 
     if ((r<=n) && (A[r]>A[max]))
 
         max= r;
 
    if (max!=i){
 
        swap(i,max,A);
 
        MaxHeapify(A, max,n);
 
    }
 
 
 
}
 
 
 
int BuildMaxHeap(int *A,int n ){
 
    int i;
 
    for (i=n/2; i>=1;i--) {
 
        MaxHeapify(A, i,n);
 
    }
 
}
 
 
 
int HeapExtractMax(int *A, int n){
 
    int max=A[1];
 
    A[1]=A[n];
 
    n--;
 
    MaxHeapify(A,1, n);
 
    return max;
 
}
 
 
 
int HeapSort(int *A,int n){
 
    int i,*V, aux=n;
 
    V=(int*)malloc(n*sizeof(int));
 
    BuildMaxHeap(A,n);
 
    for(i=1;i<=n;i++){
 
        printf("%d ", A[i]);
 
    }
 
    printf("\n");
 
 
 
    while( n>0){
 
        V[n-1]=HeapExtractMax(A, n);
 
        n--;
 
    }
 
    for(i=0;i<aux;i++){
 
        printf("%d ", V[i]);
 
    }
 
    
 
    free(V);
 
}
 
 
 
int main() {
 
 
 
    int n, *A,i;
 
    scanf("%d", &n);
 
    A=(int *)malloc((n+1)*sizeof(int));
 
 
 
    for(i=1;i<=n;i++){
 
 
 
        scanf("%d", &A[i]);
 
 
 
    }
 
 
 
    HeapSort(A,n);
 
 
 
    free(A);
 
    return 0;
 
 
 
}
