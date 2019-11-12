#include<stdio.h>
#include<stdlib.h>

int main(){

    for(int i=0;i<1000;i++){
        for(int j=0;j<6;j++){
            printf("%c",(rand()%10)+48);
        }
        printf("\n");
        printf("%c\n",(rand()%26)+97);
        printf("%c\n",(rand()%26)+97);
        printf("%d\n",rand()%5000);
    }

}