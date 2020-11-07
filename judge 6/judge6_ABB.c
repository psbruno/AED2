#include <stdio.h>
#include <stdlib.h>
 
typedef struct{
    int Valor;
    int chave;
    struct No *Pai;
    struct No *esq;
    struct No *dir;
}TNo;
 
 
 
TNo *Novo(int Chave, int valor, TNo *pai){
    TNo *aux;
    aux=(TNo*)malloc(sizeof(TNo));
    aux->chave=Chave;
    aux->Valor=valor;
    aux->esq=NULL;
    aux->dir=NULL;
    aux->Pai=pai;
    return aux;
}
 
int setapai(TNo *NoPRem, TNo *NoPai){
    //printf("\n");
    //impP(NoPai);
    if(NoPai==NULL){
        NoPRem=NULL;
        return 1;
    }
    if(NoPRem == NoPai->dir){
            NoPai->dir=NoPRem->dir;
    }else{
           NoPai->esq=NoPRem->dir;
    }
    return 0;
}
void impP(TNo *No){
    if(No==NULL)
        return;
    printf("(C%d", No->Valor);
    if(No->esq!=NULL)
        impP(No->esq);
    else
        printf("()");
    if(No->dir!=NULL)
        impP(No->dir);
    else
        printf("()");
    printf(")");
}
int Remover(TNo *NoPRem){//nó para remover
    TNo *aux=NoPRem,*auxpai;
    int a;
    if(NoPRem->dir==NULL && NoPRem->esq==NULL){
        a=setapai(NoPRem, NoPRem->Pai);
        if(a==1)
            return 1;
        free(NoPRem);
        return 0;
    }
    if(aux->dir!=NULL){
        aux=NoPRem->dir;
    }
    while(aux->esq!=NULL){
        aux=aux->esq;
    }
    //impP(aux);
/*    auxpai=aux->Pai;
 
    if(aux->dir!=NULL){
        auxpai->dir=aux->dir;
    }*/
    setapai(aux,aux->Pai);
 
    NoPRem->chave=aux->chave;
    NoPRem->Valor=aux->Valor;
    //NoPRem->dir=aux->dir;
    //NoPRem->esq=aux->esq;
    //impP(NoPRem);
    free(aux);
}
 
TNo *proc(int N, TNo *NoAtual,int i){
    if(NoAtual==NULL){
        return Novo(i,N,NULL);
    }
    if(NoAtual->dir!=NULL && N>NoAtual->Valor){
        proc(N,NoAtual->dir,i);
    }else if(NoAtual->dir==NULL && N>NoAtual->Valor){//inserção
        NoAtual->dir=Novo(i,N,NoAtual);
    }else if(NoAtual->esq!=NULL && N<NoAtual->Valor){
        proc(N,NoAtual->esq,i);
    }else if(NoAtual->esq==NULL && N<NoAtual->Valor){//inserção
        NoAtual->esq=Novo(i,N,NoAtual);
    }else if(N == NoAtual->Valor){
        Remover(NoAtual);
        return NULL;
    }
    return NoAtual;
}
void imp(TNo *Raiz){
    if(Raiz->esq!=NULL)
        imp(Raiz->esq);
   printf("%d ", Raiz->Valor);
    if(Raiz->dir!=NULL)
        imp(Raiz->dir);
}
 
int Altura(TNo *Raiz, int *altura, int aux,int *tam){
    if(Raiz==NULL)
        return;
 
    if(Raiz->esq!=NULL)
        Altura(Raiz->esq,altura,aux+1,tam);
    if(Raiz->dir!=NULL)
        Altura(Raiz->dir,altura,aux+1,tam);
    if(aux>=*altura){
       *altura=aux;
    }
 
    *tam+=1;
}
int main(){
    int N,u,tam=0, i=0;
    TNo *Raiz=NULL, *NoP,*NoA;//nó raiz, nó procurado e nó Atual
    int altura=0;
    scanf("%d", &N);
    while(N!=-1){
        Raiz=proc(N,Raiz, i);
        scanf("%d", &N);
    }
 
    scanf("%d",&N);
 
    Altura(Raiz,&altura,1,&tam);
    printf("%d %d\n",tam,altura);
 
    Raiz=proc(N,Raiz, i+1);
    tam=0;
    altura=0;
 
    Altura(Raiz,&altura,1,&tam);
    printf("%d %d\n",tam,altura);
    //impP(Raiz);
    return 0;
}
