#include <stdio.h>
#include <stdlib.h>
#define black 0
#define red 1
 
typedef struct{
    int Valor;
    int chave;
    int cor;
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
    aux->cor=1;
    return aux;
}
/*
int setapai(TNo *NoPRem, TNo *NoPai){
   //printf("\n");
   //impP(NoPai);
    printf("PAI:%d\n",NoPai->Valor);
    if(NoPai==NULL){
        NoPRem=NULL;        return 1;
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
    if(Raiz==NULL || Raiz->Valor==-1 || Raiz->Valor==1)
        return;
    Altura(Raiz->esq,altura,aux+1,tam);
    Altura(Raiz->dir,altura,aux+1,tam);
    if(aux>=*altura){
       *altura=aux;
    }
    *tam+=1;
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
TNo *procPai(TNo *Arvore,TNo *orfao){
    if(Arvore==NULL)
        return NULL;
    TNo *Pai=NULL;
    if(Arvore->esq==orfao)
        return Arvore;
    if(Arvore->dir==orfao)
        return Arvore;
    /*if(Arvore==orfao)
        return orfao;*/
    Pai=procPai(Arvore->dir,orfao);
    if(Pai==NULL)
        Pai=procPai(Arvore->esq,orfao);
    return Pai;
}
void recolor(TNo *D,TNo *C,TNo *A){
        if(D!=NULL)
            D->cor=0;
        C->cor=1;
        if(D!=NULL)
            A->cor=0;
}
 
TNo *RD(TNo *pA){
      TNo *pB;
      pB=pA->esq;
      pA->esq=pB->dir;
      pB->dir=pA;
      return pB;
}
TNo *RE(TNo *pA){
      TNo *pB;
      pB=pA->dir;
      pA->dir=pB->esq;
      pB->esq=pA;
     return pB;
}
TNo *insertion(TNo *A,TNo *B, TNo *Raiz){
    //printf("------------------------------------no analisado: %d--------------------------\n",A->Valor);
    TNo *D, *pC,*C=procPai(Raiz,A);//procura o pai de A
    if(C==NULL || A->cor==0)
        return Raiz;
    //printf(" PAI DE %d : %d------------\n", A->Valor,C->Valor);
   //Imprime(Raiz);
    if(A==C->esq)
        D=C->dir;
    else
        D=C->esq;
  //  if(D!=NULL)
//        printf("IRMAO %d\n",D->Valor);
    pC=procPai(Raiz,C);
    if(D==NULL || D->cor==0){
        //printf("\ncaso 2 ou 3 (A %d B %d C %d )\n",A->Valor,B->Valor,C->Valor  );
        //Imprime(Raiz);
        if(A==C->esq && B==A->dir){//Caso 2a
           // printf("2a, Rotacao Esquerda\n");
            A=RE(A);
            C->esq=A;
            B=A->esq;
         //   printf("\ncaso 2a (A %d B %d C %d )\n",A->Valor,B->Valor,C->Valor  );
        }else if(A==C->dir && B==A->esq){//Caso 2b
       //     printf("2b, Rotacao Direita\n");
            A=RD(A);
            C->dir=A;
            B=A->dir;
        }
       /* printf("\npos rotacao :");
         Imprime(Raiz);
    printf("\n");*/
         if(A==C->esq && B==A->esq){//Caso 3a
            //printf("3a\n");
            if(pC!=NULL){
                if(C==pC->esq)
                    pC->esq=RD(C);
                else
                    pC->dir=RD(C);
            }else{
                Raiz=RD(C);
                //Imprime(Raiz);
             //  printf("\n");
           }
            A->cor=0;
            C->cor=1;
        }
         if(A==C->dir && B==A->dir){//Caso 3b
             //printf("3b\n");
             if(pC!=NULL){
                if(C==pC->esq)
                    pC->esq=RE(C);
                else
                    pC->dir=RE(C);
            }else{
                Raiz=RE(C);
                /*Imprime(Raiz);
                printf("\n");*/
            };
             A->cor=0;
             C->cor=1;
        }
    }else if (D->cor==1){
        //printf("RECOLORACAO\n");
        recolor(D,C,A);
        //Imprime(Raiz);
        //printf("\n");
        pC=procPai(Raiz,C);
        if(pC!=NULL && pC->cor==1){
          Raiz=insertion(pC,C,Raiz);
        }
   }
    return Raiz;
}
TNo *proc(int N, TNo *NoAtual,int i,TNo *Raiz){
    if(NoAtual==NULL){
        return Novo(i,N);
    }
    if(NoAtual->dir!=NULL && N>NoAtual->Valor){
        /*NoAtual->dir=*/Raiz=proc(N,NoAtual->dir,i,Raiz);
    }else if(NoAtual->dir==NULL && N>NoAtual->Valor){//inserção
        NoAtual->dir=Novo(i,N);
        Raiz=insertion(NoAtual,NoAtual->dir,Raiz);
    }else if(NoAtual->esq!=NULL && N<NoAtual->Valor){
        /*NoAtual->esq=*/Raiz=proc(N,NoAtual->esq,i,Raiz);
    }else if(NoAtual->esq==NULL && N<NoAtual->Valor){//inserção
        NoAtual->esq=Novo(i,N);
        Raiz=insertion(NoAtual,NoAtual->esq,Raiz);
    }else if(N == NoAtual->Valor){
        //printf("Removendo %d\n", NoAtual->Valor);
        /*NoAtual=Remover(NoAtual);
        if(NoAtual!=NULL)
            NoAtual=AVL(NoAtual);*/
        return Raiz;
    }
    /*printf("---------------------------------\n");
    Imprime(Raiz);
    printf("\n");-*/
    return Raiz;
}
TNo *left(TNo *No){
    return No->esq;
}
TNo *right(TNo *No){
    return No->dir;
}
 
void fixup(TNo* T,TNo *x){
    TNo *w,*xp,*we, *wd,*pai;
   //if(x==NULL)
       //printf("x null");
    //printf("fixup %d\n", x->Valor);
    while(x!=T && x->cor==0){
            //printf("while fixup\n");
        if(x==procPai(T,x)->esq){//esqierda
           //printf("esquerda\n");
           w=procPai(T,x)->dir;
           if(w->cor==red){//caso 1
               //printf("caso 1e\n");
                w->cor=black;
                xp=procPai(T,x);
                xp->cor=1;
                pai=procPai(T,xp);
                if(pai!=NULL){
                    if(pai->esq==xp){
                        xp=RE(xp);
                        pai->esq=xp;
                    }else{
                        xp=RE(xp);
                        pai->dir=xp;
                    }
                }else{
                    T=RE(xp);
                }
              //  printf("RE\n");
                w=xp->dir;
           }
           we=w->esq;
           wd=w->dir;
           if(we->cor==0 && wd->cor==0){//caso 2
            //printf("caso 2e\n");
            w->cor=1;
            x=procPai(T,x);
           }else{//caso 3 ou 4
             //  printf("direita");
               if(wd->cor==0){//caso 3
                 //   printf("caso 3e\n");
                    left(w)->cor=0;
                    if(procPai(T,w)!=NULL){
                        if(w==procPai(T,w)->dir)
                            procPai(T,w)->dir=RD(w);
                        else
                            procPai(T,w)->esq=RD(w);
                    }else
                        T=RD(w);
                    w->cor=1;
                    //printf("RD\n");
                    //Imprime(T);
                  //  printf("\n");
               }//caso 4
                //printf("caso 4e\n");
                w=procPai(T,x)->dir;
                w->cor=procPai(T,x)->cor;
                procPai(T,x)->cor=0;
                right(w)->cor=black;
                //printf("RE\n");
                xp=procPai(T,x);
                if(xp!=NULL){
                    if(xp==procPai(T,xp)->dir)
                        procPai(T,xp)->dir=RE(xp);
                    else
                        procPai(T,xp)->esq=RE(xp);
                }else
                    T=RE(xp);
                x=T;
            //   Imprime(T);
               // printf("\n");
           }
        }else{//direita
           w=procPai(T,x)->esq;
           if(w->cor==1){//caso 1
            //    printf("caso 1d\n");
               w->cor=0;
               xp=procPai(T,x);
                xp->cor=1;
                pai=procPai(T,xp);
                if(pai!=NULL){
                if(pai->esq==xp){
                        xp=RD(procPai(T,x));
                        pai->esq=xp;
                    }else{
                        xp=RD(procPai(T,x));
                        pai->dir=xp;
                    }
                }else{
                    T=RD(procPai(T,x));
 
                }
               // xp=RD(procPai(T,x));
                w=procPai(T,x)->esq;
           }
           we=w->esq;
           wd=w->dir;
           if(we->cor==0 && wd->cor==0){//caso 2
         //  printf("caso 2d\n");
            w->cor=1;
            x=procPai(T,x);
           }else{//caso 3 ou 4
              if(we->cor==0){//caso 3
       //            printf("caso 3d\n");
                    wd->cor=0;
                    w->cor=1;
                    if(procPai(T,w)!=NULL){
                        if(w==procPai(T,w)->dir)
                            procPai(T,w)->dir=RE(w);
                        else
                            procPai(T,w)->esq=RE(w);
                    }else
                        T=RE(w);
               }//caso 4
      //         printf("caso 4d\n");
                w=procPai(T,x)->esq;
                w->cor=procPai(T,x)->cor;
                procPai(T,x)->cor=0;
                we=w->esq;
                we->cor=0;
                xp=procPai(T,x);
                if(x!=NULL){
                    if(xp==procPai(T,xp)->esq)
                        procPai(T,xp)->esq=RD(xp);
                    else if(xp==procPai(T,xp)->dir)
                        procPai(T,xp)->dir=RD(xp);
                }else
                    T=RD(xp);
           }
        }
 
    }
    x->cor=0;
    //Imprime(x);
    //printf("----------\n");
}
 int calcalt (TNo* No) {
    if(No==NULL){
        return 0;
    }
    int alt=0;
 
    if(No->cor==0){
        alt = 1;
    }
    return alt+calcalt(No->esq);
}
 
void RB_delete(TNo *T,TNo *z){
    TNo *y,*x=NULL;
    if(right(z)->Valor==-1 || left(z)->Valor== -1){//um filho so
        y=z;
    }else{
        y=z->dir;
        while(left(y)->Valor!=-1)//sucessor de z
            y=y->esq;
    }
    //printf("y: %d\n", y->Valor);
    if(left(y)->Valor!=-1){
        x=y->esq;
 
  //      printf("y tem f esq == %d\n",x->Valor);
    }else{
        x=y->dir;
//        printf("y tem f dir == %d\n",x->Valor);
    }/*else{
        x=y;
        printf("y == x\n");
    }*/
 
//pai de x = pai de y
    if(procPai(T,y)==NULL)
        T=x;
    else if(y==procPai(T,y)->esq){//y eh filho esquerdo
        procPai(T,y)->esq=x;
    }else{
        procPai(T,y)->dir=x;
 
    }
    if(y!=z){
        z->chave=y->chave;
        z->Valor=y->Valor;
    }
 
    int altura=0,tam=0;
    //printf("\n\n\n\n");
    //Imprime(T);
    //printf("\n\n\n\n");
 
    if(y->cor==0){
        //printf("fixup %d %d\n",procPai(T,x)->Valor, x->Valor);
        fixup(T,x);
        //Altura(T,&altura,0,&tam);
        altura=calcalt(T);
        printf("%d\n", altura-1);
        Imprime(T);
    }
    else{
       //printf("n fixup %d %d \n", y->cor, y->Valor );
       // Altura(T,&altura,0,&tam);
     altura=calcalt(T);
 
        printf("%d\n", altura-1);
        Imprime(T);
    }
    return;
 }
 
TNo *procR(int N, TNo *NoAtual,int i,TNo *Raiz){
    if(NoAtual==NULL){
        return NULL;
    }
    if(NoAtual->dir!=NULL && N>NoAtual->Valor)
        NoAtual->dir=procR(N,NoAtual->dir,i,Raiz);
    else if(NoAtual->esq!=NULL && N<NoAtual->Valor)
        NoAtual->esq=procR(N,NoAtual->esq,i,Raiz);
    else if(N == NoAtual->Valor)
        RB_delete(Raiz, NoAtual);
    return NoAtual;
}
 
int EhNegro(TNo *No)
{
    return (No == NULL) || (No->cor == 0);
}
 
int EhRubro(TNo *No)
{
    return (No != NULL) && (No->cor == 1);
}
 
void Imprime(TNo *No)
{
 
if(No==NULL)
    return;
 
    if (No->Valor!=-1) {
        if (EhNegro(No))
            printf("(N%d", No->Valor);
        else if(No->Valor)
            printf("(R%d", No->Valor);
        Imprime(No->esq);
        Imprime(No->dir);
        printf(")");
    }
    else
        printf("()");
}
 TNo *setanil(TNo *No){
    if(No==NULL){
        No=Novo(0,-1);
        No->cor=black;
        return No;
    }
    No->esq=setanil(No->esq);
    No->dir=setanil(No->dir);
    return No;
}
 
void Imprime1(TNo *No)
{
    if (No != NULL) {
        if (EhNegro(No))
            printf("(N%d", No->Valor);
        else
            printf("(R%d", No->Valor);
        Imprime1(No->esq);
        Imprime1(No->dir);
        printf(")");
    }
    else
        printf("()");
}
 
int main(){
    int N,u,tam=0, i=0;
    char c;
    TNo *Raiz=NULL,*p;
    int altura=0;
    scanf("%d", &tam);
    for(i=0;i<tam;i++){
        scanf("%d", &N);
        Raiz=proc(N,Raiz,i,Raiz);
        Raiz->cor=0;//propriedade 2
        /*//printf("---\n");
        Imprime(Raiz);
        printf("---\n");*/
    }
    if(Raiz!=NULL)
        altura++;
    //Altura(Raiz,&altura,0,&tam);
 altura=calcalt(Raiz);
    printf("%d\n", altura);
    Imprime1(Raiz);
    printf("\n");
 
    Raiz=setanil(Raiz);
 
    //p=procPai(Raiz,Raiz->esq); teste
    //printf("\n %d %d", procPai(Raiz,Raiz->esq)->Valor,p->Valor);
    //impP(Raiz);
    scanf("%d", &N);
    procR(N,Raiz,i,Raiz);
 
    //Imprime(Raiz);
   // printf("\n");
    //impP(Raiz);
    return 0;
}
