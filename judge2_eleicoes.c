#include <stdio.h>
 
 
 
#include <stdlib.h>
 
 
 
void imp(int **votos,int v){
 
 
 
    int j,i=0;
 
 
 
    for(i=0;i<v;i++){
 
 
 
            printf("%d %d %d\n",votos[i][0],votos[i][1], votos[i][2]);
 
 
 
    }
 
 
 
}
 
 
 
int *turno1(int **votos, int c,int v){
 
 
 
    int *VdC,i;
 
 
 
    VdC=(int *)malloc(c*sizeof(int));
 
 
 
 
 
 
 
    for(i=0;i<c;i++)
 
 
 
        VdC[i]=0;
 
 
 
 
 
 
 
    for(i=0;i<v;i++){
 
 
 
        if(votos[i][0]<=c)
 
 
 
            VdC[votos[i][0]-1]+=1;
 
 
 
    }
 
 
 
    //printf("\n");
 
 
 
 
 
 
 
 
 
 
 
    return VdC;
 
 
 
 
 
 
 
}
 
 
 
void turno2(int **votos, int v,int c, int *VdC, int Iprim){
 
 
 
    int i, j,Iseg=0;
 
 
 
    float vv=0,n1=0,n2=0;//numero de votos do candidato 1, numero de votos do candidato 2
 
 
 
    VdC[Iprim]=-1;
 
 
 
 
 
 
 
    for(i=0;i<c;i++){
 
 
 
      if(VdC[Iseg]<VdC[i]){
 
 
 
        Iseg=i;
 
 
 
      }
 
 
 
    }
 
 
 
 
 
 
 
    //printf("%d %d\n", Iseg+1, VdC[Iseg]);
 
 
 
    for(i=0;i<v;i++){
 
 
 
        for(j=0;j<3;j++){
 
 
 
            if(votos[i][j]==Iprim+1){
 
 
 
                n1++;
 
 
 
                j=3;
 
 
 
                vv++;
 
 
 
            }else if(votos[i][j]==Iseg+1){
 
 
 
                n2++;
 
 
 
                j=3;
 
 
 
                vv++;
 
 
 
            }
 
 
 
        }
 
 
 
 
 
 
 
    }
 
 
 
    
 
 
 
    if(n2>n1){
 
 
 
        printf("%d %.2f\n",Iseg+1, (n2*100)/vv);
 
 
 
    }else if(n1>n2){
 
 
 
        printf("%d %.2f\n",Iprim+1, (n1*100)/vv);
 
 
 
    }else{
 
        if(Iseg>Iprim){
 
            printf("%d 50.00\n",Iprim+1);
 
        }else{
 
            printf("%d 50.00\n",Iseg+1);
 
        }
 
        
 
    }
 
    
 
    //printf("candidato %d: %.2f\ncandidato %d : %.2f \n", Iprim+1, Iseg+1,(n1*100)/vv, (n2*100)/vv);
 
 
 
 
 
 
 
 
 
 
 
}
 
 
 
int main(){
 
 
 
    int c,v,i,j;
 
 
 
    int Iganhador=0;
 
 
 
    float vv=0;//votos validos
 
 
 
    scanf("%d %d",&v,&c);
 
 
 
    int **votos,*VdC;//VdC = votos dos candidatos
 
 
 
 
 
 
 
    votos=(int **)malloc(v*sizeof(int*));
 
 
 
    for(i=0;i<v;i++)
 
 
 
        votos[i]=(int *)malloc(3*sizeof(int));
 
 
 
 
 
 
 
    for(i=0;i<v;i++){
 
 
 
        scanf("%d %d %d", &votos[i][0], &votos[i][1], &votos[i][2]);
 
 
 
    }
 
 
 
    //printf("\n");
 
 
 
    //imp(votos,v);
 
 
 
    VdC=turno1(votos,c,v);
 
 
 
    for(i=0;i<c;i++){
 
 
 
     //   printf("%d %d\n", i+1, VdC[i]);
 
 
 
        vv+=VdC[i];
 
 
 
    }
 
 
 
    if(vv==0){
 
 
 
        printf("0");
 
 
 
        return 0;
 
 
 
    }
 
 
 
    for(i=0;i<c;i++){
 
 
 
        if(VdC[i]>VdC[Iganhador])
 
 
 
            Iganhador=i;
 
 
 
    }
 
 
 
    if(VdC[Iganhador]*100/vv>50){
 
 
 
        printf("%d %.2f", Iganhador+1, VdC[Iganhador]*100/vv);
 
 
 
    }else{
 
 
 
        printf("%d %.2f\n", Iganhador+1, VdC[Iganhador]*100/vv);
 
 
 
        turno2(votos, v,c,VdC,Iganhador);
 
 
 
    }
 
 
 
    return 0;
 
 
 
}
