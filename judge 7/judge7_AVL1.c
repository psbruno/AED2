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
TNo *Remover(TNo *NoPRem){//nó para remover
    TNo *aux=NoPRem,*auxpai;
    int a;
    if(NoPRem->dir==NULL && NoPRem->esq==NULL){
        a=setapai(NoPRem, NoPRem->Pai);
        if(a==1)
            return NULL;
        free(NoPRem);
        return NULL;
    }
    if(aux->dir!=NULL){
        aux=NoPRem->dir;
    }
    //TNo *Pai;
 
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
    return NoPRem;
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
        NoAtual=Remover(NoAtual);
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
        printf("L");
        hD=0;
        hE=0;
        B=A->esq;
        Altura(B->esq,&hE,1,&tam);
        Altura(B->dir,&hD,1,&tam);
 
 
            if(hE-hD>0){
                printf("L\n");
                A=LL(A);
            }else{
                printf("R\n");
                A=LR(A);
            }
 
 
    }else if(hE-hD<-1){//RX
            B=A->dir;
            hD=0;
            hE=0;
            printf("R");
 
            Altura(B->esq,&hE,1,&tam);
            Altura(B->dir,&hD,1,&tam);
 
 
            if(hE-hD>0){
                printf("L\n");
                A=RL(A);
 
            }else{
                printf("R\n");
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
int main(){
    int N,u,tam=0, i=0;
    char c;
    TNo *Raiz=Carrega(), *NoP,*NoA;//nó raiz, nó procurado e nó Atual
    int altura=0;
 
    /*scanf("%c", &c);
    while(c!='\n'){
        scanf("%c", &c);
        if (c == '(') {
            scanf("%c", &c);
            if (c == 'C') {
                scanf("%d", &N);
                Raiz=proc(N,Raiz,0);
            }
        }
 
    }*/
 
 
 
    Altura(Raiz,&altura,1,&tam);
    printf("%d\n",altura-1);
    impP(Raiz);
    printf("\n");
 
    Raiz=AVL(Raiz);
    altura=0;
    Altura(Raiz,&altura,1,&tam);
    printf("%d\n",altura-1);
 
    impP(Raiz);
 
    return 0;
}
