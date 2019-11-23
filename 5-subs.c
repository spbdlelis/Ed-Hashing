#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define True 1
#define False 0
#define SIZE 150

int collisions = 0;

typedef struct func{
    char mat[7];
    char nome[50];
    char funcao[20];
    float salario;
}funcionario;


funcionario readFunc();
int isOccupied(int *vet, int pos);
void hashFuncA(char* mat, int* ocupados, int flagFull);
void hashFuncB(char* mat, int* ocupados, int flagFull);

int main(){
    funcionario *funcList;
    funcList = (funcionario*)malloc(sizeof(funcionario)*SIZE);
    int *ocupados = calloc(sizeof(int),SIZE);
    funcionario f;
    for(int i=0;i<1000;i++){
        f = readFunc();
        if(i<SIZE)
            hashFuncA(f.mat,ocupados, 0);
        else
            hashFuncA(f.mat,ocupados, 1);
    }
    printf("%d Colisões\n\n", collisions);

    free(ocupados);
    ocupados = (int*)calloc(sizeof(int),SIZE);
    collisions = 0;

    for(int i=0;i<1000;i++){
        f = readFunc();
        if(i<SIZE)
            hashFuncB(f.mat,ocupados, 0);
        else
            hashFuncB(f.mat,ocupados, 1);
    }

    printf("%d Colisões\n\n", collisions);





}

void hashFuncB(char* mat, int* ocupados, int flagFull){
    int position = (mat[0]-48)*100+(mat[2]-48)*10+(mat[5]-48);
    position += ((mat[1]-48)*100+(mat[3]-48)*10+(mat[4]-48));
    position %= 1000;
    position %= SIZE;
    int cont = 0;
    int flag = True;
    if (!flagFull){  // se não está cheio
        while(isOccupied(ocupados, position) && position < SIZE){
            collisions++;
            position+=7;
        }
        if(position < SIZE){
            ocupados[position] = 1;
        }
    }else{
        collisions++;
    }
}

int isOccupied(int *vet, int pos){
    if(vet[pos] == 0)
        return False;
    else
        return True;
}

void hashFuncA(char* mat, int* ocupados, int flagFull){
    int firstdigit = mat[4] - 48;
    int separated = (mat[5]-48)*100+(mat[1]-48)*10+(mat[3]-48);
    separated %= SIZE;
    int cont = 0;
    int flag = 1;
    if (!flagFull){  // se não está cheio
        while(isOccupied(ocupados, separated) && separated < SIZE){
            collisions++;
            separated+=firstdigit;
            if(firstdigit == 0){
                break;
            }
        }
        if(separated < SIZE){
            ocupados[separated] = 1;
        }
    }else{
        collisions++;
    }
    
}

funcionario readFunc(){
    funcionario f;
    //printf("Digite os dados do funcionário: Matrícula, nome, função e salário, um por linha\n");
    //printf("Matrícula >> ");
    scanf("%s",f.mat);setbuf(stdin,NULL);
    //printf("Nome >> ");
    //scanf("%[^\n]",f.nome);setbuf(stdin,NULL);
    //printf("Função >> ");
    //scanf("%[^\n]",f.funcao);setbuf(stdin,NULL);
    //printf("Salário >> ");
    //scanf("%f",&f.salario);setbuf(stdin,NULL);
    return f;
}