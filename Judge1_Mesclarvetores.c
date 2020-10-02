#include <stdio.h>
#include <stdlib.h>
 
void bubble(int *cc,int c){
    int i=0,j=0,aux;
    for(i=1;i<c;i++){
        for(j=0;j<c-1;j++){
            if (cc[j] > cc[j+1]){
                aux=cc[j];
                cc[j]=cc[j+1];
                cc[j+1]=aux;
            }
        }
 
    }
 
}
int main(){
    int i,aux,j,a,b,c,*cc,*bb,*aa;
    scanf("%d", &a);
    aa=(int *)malloc(a*sizeof(int));
 
    for(i=0;i<a;i++){
        scanf("%d",&aa[i]);
    }
    scanf("%d", &b);
    bb=(int *)malloc(b*sizeof(int));
 
    for(i=0;i<b;i++){
        scanf("%d",&bb[i]);
    }
    c=a+b;
    cc=(int*)malloc(c*sizeof(int));
    for(i=0;i<a;i++){
        cc[i]=aa[i];
    }
    for(i=0;i<b;i++){
        cc[i+a]=bb[i];
    }
    bubble(cc,c);
    for(i=0;i<c;i++){
        printf("%d ",cc[i]);
    }
    return 0;
}
