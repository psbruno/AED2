#include <stdio.h>
#include <stdlib.h>
 
typedef struct{
    int Valor;
    int chave;
 
    struct No *esq;
    struct No *dir;
}TNo;
 
 
 
TNo *Novo(int Chave, int valor){
    TNo *aux;
    aux=(TNo*)malloc(sizeof(TNo));
    aux->chave=Chave;
    aux->Valor=valor;
    aux->esq=NULL;
    aux->dir=NULL;
 
    return aux;
}
/*
int setapai(TNo *NoPRem, TNo *NoPai){
    //printf("\n");
    //impP(NoPai);
    printf("PAI:%d\n",NoPai->Valor);
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
 */
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
TNo *Remover(TNo *NoPRem){//nó para remover
    TNo *aux=NoPRem,*aux2;
    int a;
    //printf("removendo %d\n", NoPRem->Valor);
   if(NoPRem->esq==NULL && NoPRem->dir==NULL){
        NoPRem=NULL;
        free(NoPRem);
        return NULL;
   }
   TNo *PaiS=aux;//pai do sucessor
 
   if(aux->dir!=NULL)
        aux=aux->dir;
 
 
 
   while(aux->esq!=NULL){
        PaiS=aux;
        aux=aux->esq;
   }
    //printf("PaiS:%d ", PaiS->Valor);
    //printf("sucessor: %d\n", aux->Valor);
 
    if(PaiS->Valor>aux->Valor)
        PaiS->esq=aux->dir;
    else
        PaiS->dir=aux->dir;
 
 
    //setapai(aux,aux->Pai);
    NoPRem->Valor=aux->Valor;
    NoPRem->chave=aux->chave;
 
    aux=NULL;
    free(aux);
 
 
   /* impP(NoPRem);
    printf("\n");*/
    return NoPRem;
 
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
TNo *LL(TNo *pA) {
 
    TNo *pB = pA->esq;
 
    pA->esq = pB->dir;
    pB->dir = pA;
 
 
    return pB;
}
TNo * RR(TNo *pA) {
 
    TNo *pB  =pA->dir;
 
    pA->dir = pB->esq;
    pB->esq = pA;
 
    return pB;
 
}
TNo *LR(TNo *pA) {
 
    TNo *pB = pA->esq;
    TNo *pC = pB->dir;
 
    pB->dir = pC->esq;
    pC->esq = pB;
    pA->esq = pC->dir;
 
    pC->dir = pA;
 
 
    return  pC;
}
 
TNo *RL(TNo *pA) {
 
    TNo *pB=pA->dir;
    TNo *pC=pB->esq;
 
    pB->esq = pC->dir;
    pC->dir = pB;
 
    pA->dir=pC->esq;
    pC->esq = pA;
 
    return pC;
 
}
TNo *AVL(TNo *A){
    TNo *B;
    int hD=0,hE=0,tam=0;
 
    Altura(A->esq,&hE,1,&tam);
    Altura(A->dir,&hD,1,&tam);
 
    //printf("hE %d hD %d %d \n", hE,hD,hE-hD);
 
    if(hE-hD>1){//LX
        //printf("L");
        hD=0;
        hE=0;
        B=A->esq;
        Altura(B->esq,&hE,1,&tam);
        Altura(B->dir,&hD,1,&tam);
 
 
            if(hE-hD>0){
                //printf("L\n");
                A=LL(A);
            }else{
              //  printf("R\n");
                A=LR(A);
            }
 
 
    }else if(hE-hD<-1){//RX
            B=A->dir;
            hD=0;
            hE=0;
            //printf("R");
 
            Altura(B->esq,&hE,1,&tam);
            Altura(B->dir,&hD,1,&tam);
 
 
            if(hE-hD>0){
            //    printf("L\n");
                A=RL(A);
 
            }else{
          //      printf("R\n");
                A=RR(A);
 
            }
 
 
    }
    int h=0;
 
    /*Altura(A,&h,1,&tam);
    printf("%d\n",h-1);
    //impP(A);
*/
    return A;
}
TNo *Carrega() {
 
    char c;
 
    TNo* No;
 
    scanf("%c", &c);
 
    if (c == '(') {
 
        scanf("%c", &c);
 
        if (c == 'C') {
 
            No = (TNo*) malloc(sizeof(TNo));
 
            scanf("%d", &No->Valor);
 
            No->esq = Carrega();
 
            No->dir = Carrega();
 
            scanf("%c", &c);
 
        }
 
        else if (c == ')')
 
            No = NULL;
 
    }
 
    return No;
 
}
TNo *proc(int N, TNo *NoAtual,int i){
    if(NoAtual==NULL){
        return Novo(i,N);
    }
    if(NoAtual->dir!=NULL && N>NoAtual->Valor){
        NoAtual->dir=proc(N,NoAtual->dir,i);
    }else if(NoAtual->dir==NULL && N>NoAtual->Valor){//inserção
        NoAtual->dir=Novo(i,N);
    }else if(NoAtual->esq!=NULL && N<NoAtual->Valor){
        NoAtual->esq=proc(N,NoAtual->esq,i);
    }else if(NoAtual->esq==NULL && N<NoAtual->Valor){//inserção
        NoAtual->esq=Novo(i,N);
    }else if(N == NoAtual->Valor){
        //printf("Removendo %d\n", NoAtual->Valor);
        /*NoAtual=Remover(NoAtual);
        if(NoAtual!=NULL)
            NoAtual=AVL(NoAtual);*/
        return NoAtual;
    }
 
    NoAtual=AVL(NoAtual);
 
    return NoAtual;
}
TNo* procAVL(TNo *No){
 
    if(No==NULL)
        return;
 
    //printf("%d\n", No->Valor);
    if(No->esq!=NULL)
        No->esq=procAVL(No->esq);
 
    if(No->dir!=NULL)
        No->dir=procAVL(No->dir);
 
    No=AVL(No);
 
    return No;
 
 
}
TNo *procR(int N, TNo *NoAtual,int i){
    if(NoAtual==NULL){
        return Novo(i,N);
    }
    if(NoAtual->dir!=NULL && N>NoAtual->Valor){
        NoAtual->dir=procR(N,NoAtual->dir,i);
    }else if(NoAtual->dir==NULL && N>NoAtual->Valor){//inserção
        NoAtual->dir=Novo(i,N);
    }else if(NoAtual->esq!=NULL && N<NoAtual->Valor){
        NoAtual->esq=procR(N,NoAtual->esq,i);
    }else if(NoAtual->esq==NULL && N<NoAtual->Valor){//inserção
        NoAtual->esq=Novo(i,N);
    }else if(N == NoAtual->Valor)
        NoAtual=Remover(NoAtual);
 
 
    NoAtual=procAVL(NoAtual);
 
    return NoAtual;
}
 
int main(){
    int N,u,tam=0, i=0;
    char c;
    TNo *Raiz=NULL;
    int altura=0;
 
    scanf("%d", &tam);
    for(i=0;i<tam;i++){
        scanf("%d", &N);
 
        Raiz=proc(N,Raiz,i);
        procAVL(Raiz);
    }
 
    //impP(Raiz);
    scanf("%d", &N);
    Raiz=procR(N,Raiz,i);
 
    impP(Raiz);
    return 0;
}
