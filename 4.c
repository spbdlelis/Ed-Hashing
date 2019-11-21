#include<stdio.h>
#include<stdlib.h>

typedef struct g{
    float **matriz;
    int nVertices;
}grafo;

typedef struct l{
    int info;
    struct l* prox;
}lista;

int flag = 0;
float Besttrust = 0;
lista* path = NULL;

void printMatrix(grafo* g);
grafo* criaGrafo(int nVertices);
grafo* inserirAresta(grafo *g, int o , int d, float p);
void printList(lista* l);
void addList(lista **l, int info);
lista* searchList(lista *l, int info);
void removeList(lista **l, int info);
void pop(lista **l);
void deepSearch(grafo *g, lista* visitados, int partida, int destino, float trust);
int canGo(grafo *g, lista* visitados ,int cidade ,float dinheiro);
int len(lista* l);

int main(){
    grafo *g;
    int nvertices;
    int o, d;
    float menorcusto;
    float c;
    lista* l = NULL;
    int cityCount = 0;

    printf("Digite a quantidade de vértices >> "); scanf("%d",&nvertices);
    g = criaGrafo(nvertices);
    printf("Digite todas as arestas conforme o exemplo:\n 1 3 0.5\n Origem = 1, Destino = 3, Confiabilidade = 50%%\n"); 
    printf("Para finalizar digite uma confiabilidade negativa\n");
    printf("OBS: Os vértices vão de 1 a %d\n", nvertices);
    
    scanf("%d %d %f",&o,&d,&c);
    menorcusto = c;
    
    while(c>=0){
        g = inserirAresta(g,o,d,c);
        scanf("%d %d %f",&o,&d,&c);
    }
    printMatrix(g);

    int partida, destino;
    printf("Digite o ponto de partida (1 - %d) >> ", nvertices); scanf("%d",&partida);
    printf("Digite o ponto de destino (1 - %d) >> ", nvertices); scanf("%d", &destino);
    float trust = 1;
    deepSearch(g, l, partida, destino, trust);
    printf("bestTrust: %.2f%%, path: ", Besttrust*100); printList(path); printf("\n");
}


void deepSearch(grafo *g, lista* visitados, int partida, int destino, float trust){
    addList(&visitados, partida);
    if(partida == destino){
        if(trust > Besttrust){
            Besttrust = trust;
            free(path);
            path = NULL;
            lista* aux = visitados;
            while(aux){
                addList(&path, aux->info);
                aux = aux->prox;
            }
        }  
    }else{
        for(int i = 0; i < g->nVertices; i++){
            if(!searchList(visitados, i+1))
                if(g->matriz[partida-1][i] != 0){
                    //printf("eu já visitei: ");printList(visitados);
                    //printf("Estou indo para o nó: %d, tenho %.2f reais",i+1,dinheiro); setbuf(stdin,NULL); getchar();
                    deepSearch(g, visitados, i+1, destino, trust*g->matriz[partida-1][i]);
                }
        }
    }
    //printf("Estou removendo: %d\n", partida);
    removeList(&visitados, partida);
    //printf("eu já visitei: ");printList(visitados);
    //printf("Voltei do nó: %d, tenho %.2f reais",partida, dinheiro); setbuf(stdin,NULL); getchar();
}
































int len(lista* l){
    int cont = 1;
    if(l == NULL)
        return 0;
    while(l->prox!=NULL){
        l = l->prox;
        cont++;
    }
    return cont;
}

int canGo(grafo *g, lista* visitados, int cidade ,float dinheiro){
    for(int i = 0; i < g->nVertices;i++){
        if(g->matriz[cidade-1][i] != 0)
            if(!searchList(visitados, i+1))
                if(dinheiro >= g->matriz[cidade-1][i])
                    return 1;
    }
    return 0;
}


void pop(lista **l){
    if(*l == NULL)
        return;
    
    if((*l)->prox == NULL){
        (*l) = NULL;
        return;
    }

    if((*l)->prox->prox == NULL){
        (*l)->prox = NULL;
        return;
    }

    pop(&((*l)->prox));
}

void removeList(lista **l, int info){
    if(*l == NULL)
        return;
    

    if((*l)->info == info || (*l)->prox == NULL){
        *l = (*l)->prox;
        return;
    }

    if((*l)->prox->info == info){
        (*l)->prox = (*l)->prox->prox;
        return;
    } 
    removeList(&((*l)->prox), info);
}

lista* searchList(lista *l, int info){
    lista* aux = l;
    for(;aux!=NULL && aux->info!=info;aux = aux->prox);
    return aux;
}

void addList(lista **l, int info){
    if(*l == NULL){
        *l = (lista*)malloc(sizeof(lista));
        (*l)->info = info;
        (*l)->prox = NULL;
        return;
    }
    addList(&((*l)->prox),info);
}

void printList(lista* l){
    for(lista* aux = l;aux!=NULL;aux = aux->prox)
        printf("%d ", aux->info);
    printf("\n");
}



grafo* inserirAresta(grafo *g, int o , int d, float p){
    g->matriz[o-1][d-1] = p;
    return g;
}

void printMatrix(grafo* g){
    for(int i=0;i<g->nVertices;i++){
        for(int j=0;j<g->nVertices;j++)
            printf("%.2f ",g->matriz[i][j]);
        printf("\n");
    }
}

grafo* criaGrafo(int nVertices){
    grafo *g;
    g = (grafo*)malloc(sizeof(grafo));
    g->nVertices = nVertices;
    g->matriz = (float**)calloc(sizeof(float*),nVertices);
    for(int i=0;i<nVertices;i++)
        g->matriz[i] = (float*)calloc(sizeof(float),nVertices);
    return g;
}