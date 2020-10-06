#include <stdio.h>
#include <stdlib.h>
 
typedef struct{ 
    int chave;
    int valor;
    int verific;
    struct Elem *prox;
}Elem;
 
int insercao(Elem *THash, int Tam, int NI){
   Elem *pAux;
    if(THash[NI%Tam].verific==0){
        THash[NI%Tam].chave=NI%Tam; 
        THash[NI%Tam].valor=NI; 
        THash[NI%Tam].verific=1; 
    }else{ 
        pAux=&THash[NI%Tam]; 
        while(pAux->prox!=NULL){ 
            pAux=pAux->prox;
        }
 
       pAux->prox=(Elem*)malloc(sizeof(Elem));
       pAux=pAux->prox;
       pAux->valor=NI;
       pAux->chave=NI%Tam; 
       pAux->prox=NULL;
 

    }
}
 
 
int remover(Elem *THash, int NB, int Tam,Elem *pRem){
 
    Elem *pAux, *pAux2=pRem;
    if(pRem->prox!=NULL){
         while(pRem->prox!=NULL){
            pAux2=pRem;
            pAux=pRem->prox;
             pRem->valor=pAux->valor;
                 pRem=pRem->prox;
 
 
        }   
 
 
    pAux2->prox=NULL;
    pAux->valor=0;
    free(pRem);
     }else{
       pAux=&THash[NB%Tam];
       if(THash[NB%Tam].prox==NULL)
 
 
 
            pAux->verific=0;
 
 
 
        else{
 
 
 
            while(pAux->prox!=pRem){
 
 
 
                pAux=pAux->prox;
 
 
 
            }
 
 
 
            pAux->prox=NULL;
 
 
 
            free(pRem);
 
 
 
        }
 
 
 
        
 
 
 
    }
 
 
 
  
 
 
 
 
 
 
 
}
 
 
 
int busca(Elem *THash, int NB, int Tam){
 
 
 
 
 
 
 
    Elem *pAux=&THash[NB%Tam];
 
 
 
    if(THash[NB%Tam].verific==0){
 
         insercao(THash,Tam,NB);
 
        return 0;
 
    }else{
 
 
 
        if(pAux->valor==NB){
 
                    remover(THash,NB, Tam,pAux);
 
 
 
                    return 0;
 
 
 
                }
 
 
 
        while(pAux!=NULL){
 
                if(pAux->valor==NB){
 
                    remover(THash,NB, Tam,pAux);
 
 
 
                    return 0;
 
 
 
                }
 
                pAux=pAux->prox;
 
 
 
        }
 
 
 
 
 
 
 
    }
 
 
 
    insercao(THash, Tam,NB);
 
 
 
}
 
 
 
 
 
 
 
int imp(Elem *THash, int Tam){
 
 
 
    int i;
 
 
 
    Elem *pAux;
 
 
 
    for(i=0;i<Tam;i++){
 
 
 
            printf("[%d]", i);
 
 
 
            if(THash[i].verific!=0)
 
 
 
                printf(" %d", THash[i].valor);
 
 
 
            pAux=&THash[i];
 
 
 
            while(pAux->prox!=NULL){
 
 
 
                pAux=pAux->prox;
 
 
 
                printf(" %d", pAux->valor);
 
 
 
            }
 
 
 
            printf("\n");
 
 
 
        }
 
 
 
}
 
 
 
int main(){
    int Tam,QNum,i;
    int NI,NB;//numero para insercao, numero a ser pesquisado
    Elem *THash,*pAux;

    scanf("%d %d", &Tam,&QNum);

    THash=(Elem*)malloc(Tam*sizeof(Elem));

    for(i=0;i<Tam;i++){
        THash[i].chave=i;
        THash[i].prox=NULL;
        THash[i].verific=0;

    }

    for(i=0;i<QNum;i++){
        scanf("%d", &NI);
       insercao(THash,Tam,NI);

    }
 
 
 
    scanf("%d", &NB); 
    busca(THash,NB,Tam);
    imp(THash, Tam);

}
