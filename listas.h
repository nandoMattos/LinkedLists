#ifndef LISTAS_H
#define LISTAS_H
#include<stdio.h>
#include<stdlib.h>  

// ESTRUTURAS

// Nó comum (ou célula) que aponta para o próximo Nó
typedef struct no{ 
    int chave;
    struct no *prox;
}No;

// Estrutura que aponta para o primeiro o último Nó
typedef struct circular{    
    int tam;
    struct no *inicio;
    struct no *fim;
}ListaC;

// Nó que também aponta para o antecessor
typedef struct noDuplo{     //
    int chave;
    struct noDuplo *prox;
    struct noDuplo *ant;
}NoD;

// FUNÇÕES BASE

No *alocaNo(int valor)  
{
    No *aux = (No *)malloc(sizeof(No));
    if (aux == NULL) return NULL;

    aux->chave = valor;
    aux->prox = NULL;
    return aux;
}

No *buscaNo(No *prim, int valor)
{
    if (prim == NULL) {
        printf("Lista vazia!");
        return NULL;
    }
    
    while (prim != NULL) {
        if(valor == prim->chave){
            return prim;
        }
        prim = prim->prox;
    }

    printf("Elemento nao encontrado!\n");
    return NULL;
}

NoD *alocaNoDuplo (int valor)
{
    NoD *aux = (NoD*)malloc(sizeof(NoD));
    if (aux == NULL) return NULL;
    aux->chave = valor;
    aux->prox = NULL;
    aux->ant = NULL;
    return aux;
}

NoD *buscaNoDuplo(NoD *prim, int valor)
{
    while (prim != NULL) {
        if(prim->chave == valor){
            return prim;
        }
        prim = prim->prox;
    }

    printf("Elemento nao encontrado!\n");
    return NULL;
}

// FUNÇÕES LISTA SIMPLES

void insereInicio(No **prim, int valor)
{
    No *novo = alocaNo(valor);
    if (novo == NULL) return;

    novo->prox = *prim;
    *prim = novo;
}

void insereDadoChave(No *aux, int valor)
{
    No *novo = alocaNo(valor);
    novo->prox = aux->prox;
    aux->prox = novo;
}

void insereOrdemCrescente(No **prim, int valor)
{
    // Caso esteja vazia
    if (*prim == NULL) {
        *prim = alocaNo(valor);
        return;
    }

    // Caso insere inicio
    if ((*prim)->prox == NULL || (valor < (*prim)->chave)) {
        if (valor <= (*prim)->chave) {
            insereInicio(&*prim, valor);
            return;
        }  

        No *aux = alocaNo(valor);
        (*prim)->prox = aux;
        return;
    }

    // Caso insere no meio ou no fim
    No *primeiro = *prim;
    No *segundo = (*prim)->prox;
    No *novo = alocaNo(valor);
    while (segundo != NULL) {
        if (valor <= segundo->chave) {
                primeiro->prox = novo;
                novo->prox = segundo;
                return;
            } 
        primeiro = primeiro->prox;
        segundo = segundo->prox;
    }
    primeiro->prox = novo;
}

void removeElemento(No **prim, int valor)
{   
    // Caso a Lista esteja vazia.
    if(*prim == NULL) {     
        printf("Lista vazia!");
        return;
    }

    // Caso o elemento a ser excluído seja o primeiro da Lista.
    if((*prim)->chave == valor) {       
        No *removedor = *prim;
        *prim = removedor->prox;
        free(removedor);
        printf("Elemento removido!\n");
        return;
    }

    // Caso o elemento a ser excluído não seja o primeiro da Lista.
    No *varredor = *prim;
    No *sucessor = (*prim)->prox;       
    while (sucessor != NULL) {  
        if(sucessor->chave == valor) {
            No *removedor = sucessor;
            varredor->prox = removedor->prox;
            free(removedor);
            printf("Elemento removido!\n");
            return;
        }
        sucessor = sucessor->prox;
        varredor = varredor->prox;

    }

    printf("Elemento nao encontrado!\n");    
}

void imprimeLista(No *prim)
{
    if(prim == NULL){
        printf("Lista vazia!\n");
        return;
    }

    while (prim != NULL){
        printf("%d\n", prim->chave);
        prim = prim->prox;
    }
}

void limpaLista(No **prim)
{
    if(*prim == NULL) return;

    No *varredor = *prim;
    No *removedor = NULL;
    while (varredor != NULL){
        removedor = varredor;
        varredor = varredor->prox;
        free(removedor);
    }
    *prim = NULL;
}

No *divideLista(No **prim, int valor) // Divide a lista na chave que o usuário passar
{
    // Caso seja vazia
    if (*prim == NULL) {
        printf("Lista vazia!");
        return NULL;
    }

    No *novaLista = NULL;

    // Dividir no primeiro elemento
    if ((*prim)->chave == valor) {
        novaLista = *prim;
        *prim = NULL;
        printf("Lista dividida com sucesso.\n");
        return novaLista;
    }   

    // Caso não seja o primeiro
    No *varredor = (*prim)->prox;
    No *antecessor = *prim;
    while (varredor != NULL) {
        if(varredor->chave == valor){
            antecessor->prox = NULL;
            printf("Lista dividida com sucesso.\n");
            return varredor;
        }
        antecessor = varredor;
        varredor = varredor->prox;
    }

    printf("Elemento nao encontrado!");
}

//FUNÇÕES LISTA CIRCULAR

ListaC *criaListaCircular()
{
    ListaC *aux = (ListaC *)malloc(sizeof(ListaC));
    if(aux == NULL) return NULL;

    aux->inicio = NULL;
    aux->fim = NULL;
    aux->tam = 0;
    return aux;
}

void insereInicioCircular(ListaC *lista, int valor)
{
    No *novo = alocaNo(valor);

    // Primeiro elemento?
    if(lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
        lista->tam = 1;
        return;
    }

    novo->prox = lista->inicio;
    lista->inicio = novo;
    if(valor != 999) lista->tam ++;
}

void insereDadoChaveCircular(ListaC *lista, int valor, int chaveDada)
{
    No *novo = alocaNo(valor);
    No *prim = lista->inicio;

    // Caso seja o primeiro elemento
    if (prim->chave  == chaveDada) {
        // Caso tenha apenas 1 elemento
        if (prim->prox == NULL) {
            prim->prox = novo;
            lista->fim = novo;
            lista->tam++;
            return;
        }

        novo->prox = prim->prox;       
        prim->prox = novo;
        lista->tam++;
        return;
    }

    // Caso seja o ultimo elemento
    No *ultimo = lista->fim;
    if(ultimo->chave == chaveDada) {
        ultimo->prox = novo;
        lista->fim = novo;
        lista->tam++;
        return;
    }

    // Caso seja um elemento no meio
    No *sucessor = prim->prox;
    while (prim != NULL) {
        if (prim->chave == chaveDada){
            novo->prox = sucessor;
            prim->prox = novo;
            lista->tam++;
            return;
        }
        prim = prim->prox;
        if(sucessor) sucessor = sucessor->prox;
    }
    printf("Elemento nao encontrado!");
}

void insereCrescenteCircular(ListaC *lista, int valor)
{
    // Caso insere inicio
    if ((lista->inicio == NULL) ||(valor <= lista->inicio->chave)) {
        insereInicioCircular(lista, valor);
        return;
    }

    // Caso tenha 1 elemento
    No *novo = alocaNo(valor);
    No *prim = lista->inicio;
    if (prim->prox == NULL) {
        if (valor <= prim->chave) {
            novo->prox = prim;
            lista->inicio = novo;
            lista->tam++;
            return;
        }
        prim->prox = novo;
        lista->fim = novo;
        lista->tam++;
        return;
    }

    // Caso seja o maior
    if (valor > lista->fim->chave) {
        lista->fim->prox = novo;
        lista->fim = novo;
        lista->tam++;
        return;
    }

    // Demais casos  
    No *segundo = prim->prox;
    while (segundo != NULL) {
        if (valor < segundo->chave) {
            novo->prox = prim->prox;
            prim->prox = novo;
            lista->tam++;
            return;
        }
        if(segundo)segundo = segundo->prox;
        prim = prim->prox;
    }
    printf("Elemento nao encontrado!");
}

void imprimeListaCircular(ListaC *lista)
{
    if(lista->inicio == NULL){
        printf("Lista vazia!\n");
        return;
    }

    No *prim = lista->inicio;
    while (prim != NULL) {
        printf("%d\n", prim->chave);
        prim = prim->prox;
    }
    printf("\nPrimeiro: %d\n", lista->inicio->chave);
    printf("Ultimo: %d\n", lista->fim->chave);
    printf("Tamanho da Lista: %d\n", lista->tam);
}

void removeElementoListaCircular(ListaC *lista, int valor)
{
    // Lista vazia?
    if (lista->inicio == NULL) {
        printf("Lista vazia!");
        return;
    }

    // Remover caso seja primeiro: 
    if (lista->inicio->chave == valor) {       
        No *aux = lista->inicio;
        lista->inicio = aux->prox;
        lista->tam --;
        free(aux);
        return;
    }   
    
    // Remover caso não seja o primeiro:
    No *prim = lista->inicio;
    No *suc = prim->prox;
    while (suc!= NULL) {
        if (suc->chave == valor) {
            // Caso esteja no meio
            if (suc != lista->fim) {
                No *aux = suc;
                prim->prox = aux->prox;
                free(aux); 
                printf("Elemento removido!");
                lista->tam --;
                return;
            } else {    // Caso esteja no fim
                No *aux = suc;
                prim->prox = aux->prox;
                lista->fim = prim;
                printf("Elemento removido!");
                lista->tam --;
                return;
            }
        }
        prim = prim->prox;
        suc = suc->prox;
    }
    printf("Elemento nao encontrado!");
}

void limpaListaCircular(ListaC *lista)
{
    No *prim = lista->inicio;
    if (prim = NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No *removedor = NULL;
    while (prim != NULL) {
        removedor = prim;
        prim = prim->prox;
        free (removedor);
    }
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->tam = 0;
}

ListaC *divideListaCircular(ListaC *lista, int valor)
{
    // Lista vazia?
    if (lista->inicio == NULL) {
        printf("Lista vazia!\n");
        return NULL;
    }

    ListaC *novaLista = (ListaC *)malloc(sizeof(ListaC));
    // Dividir no primeiro elemento  
    if (lista->inicio->chave == valor) {
        novaLista->inicio = lista->inicio;
        novaLista->fim = lista->fim;
        novaLista->tam = lista->tam;

        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tam = 0;
        return novaLista;
    }

    novaLista->fim = (No *)malloc(sizeof(No));
    // Dividir no meio ou fim
    No *varredor = lista->inicio;
    No *sucessor = varredor->prox;
    int cont = 1;
    while (sucessor != NULL) {
        if (sucessor->chave == valor) {
            novaLista->inicio = sucessor;
            novaLista->fim = lista->fim;
            novaLista->tam = lista->tam - cont;
            
            lista->fim = varredor;
            lista->tam = cont; 
            varredor->prox = NULL;
            printf("Lista dividida com sucesso!\n");
            return novaLista;
        }
        sucessor = sucessor->prox;
        varredor = varredor->prox;
        cont++;
    }   

    printf("Elemento nao encontrado!\n");    
}

// FUNÇÕES LISTA DUPLA

void insereInicioDupla(NoD **prim, int valor)
{
    NoD *aux = alocaNoDuplo(valor);
    if (*prim == NULL){
        *prim = aux;
        return;
    }
    
    aux->prox = *prim;
    (*prim)->ant = aux;
    *prim = aux;

}

void insereDadoChaveDupla(NoD **prim, int valor, int chaveDada)
{
    NoD *varredor = *prim;
    while (varredor != NULL) {
        if (varredor->chave == chaveDada) {
            NoD *novo = alocaNoDuplo(valor);
            novo->prox = varredor->prox;
            novo->ant = varredor;
           if(varredor->prox) varredor->prox->ant = novo;
            varredor->prox = novo;
            return;
        }
        varredor = (varredor)->prox;
    }
    printf("Elemento nao encontrado!");
}

void insereCrescenteDupla(NoD **prim, int valor)
{
    NoD *novo = alocaNoDuplo(valor);
    // Caso insere inicio
    if ( (*prim == NULL) || (valor <= (*prim)->chave) ){
        insereInicioDupla(prim, valor);
        return;
    }        

    NoD *varredor = *prim;
    while (varredor->prox != NULL) {
        if (valor < varredor->chave) {
            novo->prox = varredor;  
            novo->ant = varredor->ant;
            varredor->ant->prox = novo;
            varredor->ant = novo;
            return;
        }
        varredor = varredor->prox;
    }
    if (valor > varredor->chave){
        novo->ant = varredor;
        varredor->prox = novo;
        return;
    }
    novo->prox = varredor;
    novo->ant = varredor->ant;
    varredor->ant->prox = novo;
    varredor->ant = novo;
}

void imprimeListaDupla(NoD *prim)
{
    if (prim == NULL){
        printf("Lista vazia!\n");
        return;
    }

    while (prim != NULL) {
        printf("%d", prim->chave);
        if (prim->ant != NULL) printf("\t(Anterior: %d)", prim->ant->chave);
        if (prim->prox != NULL) printf("\t(Proximo: %d)", prim->prox->chave);
        printf("\n");
        prim = prim->prox;
    }
    
}

void removeElementoDupla(NoD **prim, int valor)
{
    if(*prim == NULL){
        printf("Lista vazia!");
        return;
    }

    // Remover o primeiro
    if((*prim)->chave == valor){   
        NoD *removedor = *prim;
        // Caso seja o único elemento da lista
        if ((*prim)->prox == NULL) {
            *prim = NULL;
            free(removedor);
            return;
        }
        // Caso não seja o único elemento da lista
        removedor->prox->ant = NULL;
        *prim = removedor->prox;
        free(removedor);
        return;
    }

    // Remover no meio ou ultimo
    NoD *varredor = *prim;
    while (varredor != NULL) {
        if(varredor->chave == valor){
            // Caso seja o último elemento
            if(varredor->prox == NULL){
                NoD *removedor = varredor;
                varredor->ant->prox = NULL;
                free(removedor);
                return;
            }
            // Caso não seja o último nem o primeiro elemento
            NoD *removedor = varredor;
            removedor->prox->ant = removedor->ant;
            removedor->ant->prox = removedor->prox;
            free(removedor);
            return;
        }
        varredor = varredor->prox;
    }
    printf("Elemento nao encontrado!\n");
}

void limpaListaDupla(NoD **prim)
{
    NoD *varredor = *prim;

    NoD *removedor = NULL;
    while (varredor != NULL) {
        removedor = varredor;
        varredor = varredor-> prox;
        free(removedor);
    }
    *prim = NULL;
}

NoD *divideListaDupla(NoD **prim, int valor)
{
    // Lista vazia?
    if (*prim == NULL) {
        printf("Lista vazia!\n");
        return NULL;
    }

    NoD *novaLista = NULL;

    // Dividir no primeiro elemento
    if ((*prim)->chave == valor) {
        novaLista = *prim;
        *prim = NULL;
        printf("Lista dividida com sucesso!\n");
        return novaLista;
    }

    // Dividir no meio ou fim
    NoD *varredor = (*prim)->prox;
    while (varredor != NULL) {
        if (varredor->chave == valor){
            novaLista = varredor;
            varredor->ant->prox = NULL;
            novaLista->ant = NULL;  
            printf("Lista dividida com sucesso!\n");
            return novaLista;
        }
        varredor = varredor->prox;
    }

    printf("Elemento nao encontrado!\n");
}

#endif