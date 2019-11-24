#include<stdio.h>
#include<stdlib.h>

int main(){

    for(int k = 0;k<10;k++){
        int num = 48;
        char filename[] = "arquivo 0.txt";
        filename[8] = num;
        num++;
        FILE *arq = fopen(filename,"w");
        fprintf(arq,"Teste %d\n\n", k+1);
        for(int i=0;i<1000;i++){
            for(int j=0;j<6;j++){
                if(j == 0 || j == 4){
                    fprintf(arq,"%c",(rand()%9)+49);
                }else{
                    fprintf(arq,"%c",(rand()%10)+48);
                }
            }
            fprintf(arq,"\n");
            /*printf("%c\n",(rand()%26)+97);
            printf("%c\n",(rand()%26)+97);
            printf("%d\n",rand()%5000); */
        }
        //printf("-------------------------------------------\n\n\n");
    }

}