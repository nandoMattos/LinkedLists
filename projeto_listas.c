#include<stdio.h>
#include<stdlib.h>
#include "listas.h"

// Estrutura que armazenará o primeiro elemento das outras Listas
typedef struct Lista{
    No *simples;
    No *simplesCrescente;
    No *simplesDividida;
    ListaC *circular;
    ListaC *circularCrescente;
    ListaC *circularDividida;
    NoD *dupla;
    NoD *duplaCrescente;
    NoD *duplaDividida;
}ListaEstrutuas;

// FUNÇÕES AUXILIARES

No *alocaNo(int valor);
No *buscaNo(No *prim, int valor);

ListaEstrutuas *armazenaEstruturas(No **simples,  No **simplesCrescente, No **simplesDividida, ListaC **circular, ListaC **circularCrescente, ListaC **circularDividida, NoD **dupla, NoD **duplaCrescente, NoD **duplaDividida)
{
    ListaEstrutuas *aux = NULL;
    aux = (ListaEstrutuas *)malloc(3 * sizeof(No));
    aux = (ListaEstrutuas *)malloc(3 * sizeof(ListaC));
    aux = (ListaEstrutuas *)malloc(3 * sizeof(NoD));

    aux->simples = *simples;
    aux->simplesCrescente = *simplesCrescente;
    aux->simplesDividida = *simplesDividida;

    aux->circular = *circular;
    aux->circularCrescente = *circularCrescente;
    aux->circularDividida = *circularDividida;

    aux->dupla = *dupla;
    aux->duplaCrescente = *duplaCrescente;
    aux->duplaDividida = *duplaDividida;

    return aux;
}

// INTERFACES

void interfaceInsercaoComum(ListaEstrutuas *lista, int opcao);
void interfaceInsercaoDadoChave(ListaEstrutuas *lista, int opcao);
void interfaceInsercaoCrescente(ListaEstrutuas *lista, int opcao);
void interfaceRemocao(ListaEstrutuas *lista, int opcao);
void interfaceImpressao(ListaEstrutuas *lista, int opcao);
void interfaceLimpar(ListaEstrutuas *lista, int opcao);
void interfaceDivide(ListaEstrutuas *lista, int opcao);
void liberarMemoria(ListaEstrutuas *lista);


int main() {

    // Usados para Lista Simples
    No *simples = NULL;
    No *simplesCrescente = NULL;
    No *simplesDividida = NULL;

    // Usados para Lista Circular
    ListaC *circular = criaListaCircular();
    ListaC *circularCrescente = criaListaCircular();
    ListaC *circularDividida = NULL;

    // Usados para Lista Dupla
    NoD *dupla = NULL;
    NoD *duplaCrescente = NULL;
    NoD *duplaDividida = NULL;

    // Estrutura que armazena todas as inicializações acima
    ListaEstrutuas *lista = armazenaEstruturas(&simples, &simplesCrescente, &simplesDividida, &circular, &circularCrescente, &circularDividida, &dupla, &duplaCrescente, &duplaDividida);

    int opcao;
    int opcao2;

    do{
        do{
            printf("\n\tInsira a opcao desejada:\n");
            printf("\n1-Lista Simples\n2-Lista Circular\n3-Lista Dupla\n0-Sair\n\n");
            scanf("%d", &opcao);

            // OBS.: Para cada uma das Listas, existem 3 sub-listas (Lista Comum, Lista Ordenada e Lista Dividida)
            switch (opcao) {
                case 1: printf("\n\tLISTA SIMPLES: Insira a opcao desejada:\n"); break;
                case 2: printf("\n\tLISTA CIRCULAR: Insira a opcao desejada:\n"); break;
                case 3: printf("\n\tLISTA DUPLA: Insira a opcao desejada:\n"); break;
                case 0: {
                    liberarMemoria(lista);  
                    exit(0);
                }break;
                default: printf("Opcao invalida!\n"); break;
            }
        }while (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 0);

        do{
            printf("\n1-Inserir elemento(Lista Comum)\n2-Inserir em ordem crescente(Lista Crescente)\n3-Remover elemento");
            printf("\n4-Imprimir listas\n5-Limpar Lista(s)\n6-Dividir Lista\n7-Voltar\n0-Sair\n\n");
            scanf("%d", &opcao2);
            
            switch (opcao2) {

                // Inserir Elemento (Lista Comum)
                case 1: interfaceInsercaoComum(lista, opcao); break;

                // Inserir Elemento (Lista Crescente)
                case 2: interfaceInsercaoCrescente(lista, opcao); break;

                // Remover Elemento
                case 3: interfaceRemocao(lista, opcao); break;

                // Imprimir Listas
                case 4: interfaceImpressao(lista, opcao); break;

                // Limpar Lista(s)
                case 5: interfaceLimpar(lista, opcao); break;

                // Dividir Listas
                case 6: interfaceDivide(lista, opcao); break;

                // Voltar
                case 7: break;

                // Sair
                case 0: {
                    liberarMemoria(lista);
                    exit(0);
                } 

                default: printf("Opcao invalida!"); break;
            }

        }while(opcao2 != 7);
  
    }while(opcao != 0);

    return 0;
}

void interfaceInsercaoComum(ListaEstrutuas *lista, int opcao)
{   
    int valor;
    int resposta;

    printf("Deseja inserir no inicio?\n1-Sim\n2-Nao\n");
    scanf("%d", &resposta);

    switch (resposta) {
        // Inserir no Inicio
        case 1:{
            printf("Insira uma sequencia de numeros separados por espacos (999 para sair):\n");
            scanf("%d", &valor);

            while (valor != 999){
                switch(opcao){
                    // Insere inicio Lista Simples
                    case 1: insereInicio(&lista->simples, valor); break;

                    // Insere inicio Lista Circular
                    case 2: insereInicioCircular(lista->circular, valor); break;

                    // Insere inicio Lista Dupla
                    case 3: insereInicioDupla(&lista->dupla, valor); break;
                }
                printf("Valor %d inserido.\n", valor);

                scanf("%d", &valor);
            }
        }break;

        // Inserir depois de uma chave
        case 2:{    
            int chave;
            int valor;
            No *aux = NULL;
            NoD *auxDupla = NULL;

            printf("Deseja inserir depois de qual elemento?\n");
            scanf("%d", &chave);
            
            switch (opcao) {
                // Insere dado uma chave Lista Simples
                case 1: {
                    aux = buscaNo(lista->simples, chave);
                    if (aux) {
                        printf("Insira o numero: ");
                        scanf("%d", &valor);
                        insereDadoChave(aux, valor);
                    }
                }break;

                // Insere dado uma chave Lista Circular
                case 2: {
                    aux = buscaNo(lista->circular->inicio, chave);
                    if (aux) {
                        printf("Insira o numero: ");
                        scanf("%d", &valor);
                        insereDadoChaveCircular(lista->circular, valor, chave);
                    }
                }

                // Insere dado uma chave Lista Dupla
                case 3: {
                    auxDupla = buscaNoDuplo(lista->dupla, chave);
                    if (auxDupla) {
                        printf("Insira o numero: ");
                        scanf("%d", &valor);
                        insereDadoChaveDupla(&lista->dupla, valor, chave);
                    }
                }
            }
        }break;

        default: printf("Opcao invalida"); break;
    }

    
}

void interfaceInsercaoCrescente(ListaEstrutuas *lista, int opcao)
{
    int valor;

    printf("Insira uma sequencia de numeros separados por espacos (999 para sair):\n");
    scanf("%d", &valor);
    while (valor != 999){
        switch(opcao){
            // Insere crescente Lista simples
            case 1: insereOrdemCrescente(&lista->simplesCrescente, valor); break;

            // Insere crescente Lista Circular
            case 2: insereCrescenteCircular(lista->circularCrescente, valor); break;

            // Insere crescente Lista Dupla
            case 3: insereCrescenteDupla(&lista->duplaCrescente, valor); break;
        }
        printf("Valor %d inserido.\n", valor);

        scanf("%d", &valor);
    }
}

void interfaceRemocao(ListaEstrutuas *lista, int opcao)
{
    int resposta;
    int valor;

    printf("Deseja remover de qual lista?\n1-Lista Comum\n2-Lista Crescente\n");
    switch (opcao) {
        case 1: if(lista->simplesDividida) printf("3-Lista Dividida\n"); break;
        case 2: if(lista->circularDividida) printf("3-Lista Dividida\n"); break;
        case 3: if(lista->duplaDividida) printf("3-Lista Dividida\n"); break;
    }
    scanf("%d", &resposta);

    printf("Qual elemento deseja remover?\n");
    scanf("%d", &valor);

    switch (opcao) {
        // Remover da Lista Simples
        case 1: {
            switch (resposta){
                // Remover da Lista Simples comum
                case 1: removeElemento(&lista->simples, valor); break;

                // Remover da Lista Simples crescente
                case 2: removeElemento(&lista->simplesCrescente, valor); break;

                // Remover da Lista Simples dividida
                case 3: if(lista->simplesDividida) removeElemento(&lista->simplesDividida, valor); break;

                default: printf("Opcao invalida!"); break;
            }
        }

        // Remover da Lista Circular 
        case 2: {
            switch (resposta) {
                // Remover da Lista Circular comum
                case 1: removeElementoListaCircular(lista->circular, valor); break;

                // Remover da Lista Circular crescente
                case 2: removeElementoListaCircular(lista->circularCrescente, valor); break;

                // Remover da Lista Circular dividida
                case 3: if(lista->circularDividida) removeElementoListaCircular(lista->circularDividida, valor); break;

                default: printf("Opcao invalida");break;
            }
        }

        // Remover da Lista Dupla
        case 3: {
            switch (resposta) {
                // Remover da Lista Dupla simples
                case 1: removeElementoDupla(&lista->dupla, valor); break;

                // Remover da Lista Dupla crescente
                case 2: removeElementoDupla(&lista->duplaCrescente, valor); break;

                // Remover da Lista Dupla dividida
                case 3: if(lista->duplaDividida) removeElementoDupla(&lista->duplaDividida, valor); break;

                default: printf("Opcao invalida");break;
            }
        }
    }
}

void interfaceImpressao(ListaEstrutuas *lista, int opcao)
{
    // Caso não tenha ocorrido a Divisão de Lista
    printf("==========Lista Comum:=========\n");

    switch (opcao ) {
        // Imprimir Lista Simples comum
        case 1: imprimeLista(lista->simples); break;

        // Imprimir Lista Circular comum
        case 2: imprimeListaCircular(lista->circular); break;

        //Imprimir Lista Dupla comum
        case 3: imprimeListaDupla(lista->dupla); break;
    }

    printf("==========Lista Crescente:=========\n");
    switch (opcao) {
        // Imprimir Lista Simples crescente
        case 1: imprimeLista(lista->simplesCrescente); break;

        // Imprimir Lista Circular crescente
        case 2: imprimeListaCircular(lista->circularCrescente); break;

        // Imprimir Lista Dupla crescente
        case 3: imprimeListaDupla(lista->duplaCrescente); break;
    }

    // Caso tenha ocorrido a Divisão de Lista
    switch (opcao) {
        // Imprimir Lista Simples dividida
        case 1:{
            if (lista->simplesDividida){
                printf("==========Lista Dividida:==========\n");
                imprimeLista(lista->simplesDividida);
            }
        }break;

        // Imprimir Lista Circular dividida 
        case 2:{
            if (lista->circularDividida){
                printf("==========Lista Dividida:==========\n");
                imprimeListaCircular(lista->circularDividida);
            }
        }break;

        // Imprimir Lista Dupla dividida
        case 3:{
            if (lista->duplaDividida){
                printf("==========Lista Dividida:==========\n");
                imprimeListaDupla(lista->duplaDividida);
            }
        }break;
    }
}

void interfaceLimpar(ListaEstrutuas *lista, int opcao)
{
    int resposta;
    printf("Qual lista deseja limpar?\n1-Lista Comum\n2-Lista Crescente\n");
    switch (opcao) {
        case 1: if (lista->simplesDividida) printf("3-Lista Dividida\n"); break;
        case 2: if (lista->circularDividida->inicio) printf("3-Lista Dividida\n"); break;
        case 3: if (lista->duplaDividida) printf("3-Lista Dividida\n"); break;
    }
    printf("4-Todas\n");
    scanf("%d", &resposta);


    switch (resposta){
        // Limpar Lista Comum 
        case 1:{
            switch (opcao) {

                // Limpar Lista Simples comum
                case 1: limpaLista(&lista->simples); break;

                // Limpar Lista Circular comum
                case 2: limpaListaCircular(lista->circular); break;

                // Limpar Lista Dupla comum
                case 3: limpaListaDupla(&lista->dupla); break;
            }
        } break;

        // Limpar Lista Crescente
        case 2: {
            switch (opcao) {
                // Limpar Lista Simples crescente
                case 1: limpaLista(&lista->simplesCrescente); break;

                // Limpar Lista Circular crescente
                case 2: limpaListaCircular(lista->circularCrescente); break;

                // Limpar Lista Dupla crescente
                case 3: limpaListaDupla(&lista->duplaCrescente); break;
            }
        }

        // Limpar Lista Dividida
        case 3: {
            switch (opcao) {
                // Limpar Lista Simples dividida
                case 1: limpaLista(&lista->simplesDividida); break;

                // Limpar Lista Ciruclar dividida
                case 2: limpaListaCircular(lista->circularDividida); break;

                // Limpar Lista Dupla dividida 
                case 3: limpaListaDupla(&lista->duplaDividida); break;
            }
        }
        
        // Limpar todas
        case 4: {
            switch (opcao) {
                // Limpar todas as Simples
                case 1:{
                    limpaLista(&lista->simples);
                    limpaLista(&lista->simplesCrescente);
                    limpaLista(&lista->simplesDividida);
                }break;

                // Limpar todas as Circulares
                case 2:{
                    limpaListaCircular(lista->circular);
                    limpaListaCircular(lista->circularCrescente);
                    limpaListaCircular(lista->circularDividida);
                }break;
                
                // Limpar todas as Duplas
                case 3:{
                    limpaListaDupla(&lista->dupla);
                    limpaListaDupla(&lista->duplaCrescente);
                    limpaListaDupla(&lista->duplaDividida);
                }break;
            }
        }break;
        default: printf("Opcao invalida!"); break;
    }
}

void interfaceDivide(ListaEstrutuas *lista, int opcao)
{
    int valor;
    int resposta;


    // Para evitar vazamento de memória
    if(lista->simplesDividida) free(lista->simplesDividida);
    if(lista->circularDividida) free(lista->circularDividida);
    if(lista->duplaDividida) free(lista->duplaDividida);

    printf("Qual lista deseja dividir?\n1-Lista Comum\n2-Lista Crescente\n");
    scanf("%d", &resposta);

    switch (resposta){
        // Dividir Lista Comum
        case 1:{
            printf("Em qual elemento deseja dividir a lista?\n");
            scanf("%d", &valor);

            switch (opcao ) {
                // Dividir Lista Simples comum
                case 1: lista->simplesDividida = divideLista(&lista->simples, valor); break;

                // Dividir Lista Circular comum
                case 2: lista->circularDividida = divideListaCircular(lista->circular, valor); break;

                // Dividir Lista Dupla comum
                case 3: lista->duplaDividida = divideListaDupla(&lista->dupla, valor); break;
            }

        }break;

        // Dividir Lista Crescente
        case 2:{
            printf("Em qual elemento deseja dividir a lista?\n");
            scanf("%d", &valor); 

            switch (opcao) {
                // Dividir Lista Simples crescente
                case 1: lista->simplesDividida = divideLista(&lista->simplesCrescente, valor); break;

                // Dividir Lista Circular crescente
                case 2: lista->circularDividida = divideListaCircular(lista->circularCrescente, valor); break;

                // Dividir Lista Dupla crescente
                case 3: lista->duplaDividida = divideListaDupla(&lista->duplaCrescente, valor); break;
            }

        }break;

        default: printf("Opcao invalida!");break;
    }

}

void liberarMemoria(ListaEstrutuas *lista)
{
    // Para evitar vazamento de memória
    if (lista->simples) limpaLista(&lista->simples);
    if (lista->simplesCrescente) limpaLista(&lista->simplesCrescente);
    if (lista->simplesDividida) limpaLista(&lista->simplesDividida);
    if (lista->circular) limpaListaCircular(lista->circular);
    if (lista->circularCrescente) limpaListaCircular(lista->circularCrescente);
    if (lista->circularDividida) limpaListaCircular(lista->circularDividida);
    if (lista->dupla) limpaListaDupla(&lista->dupla);
    if (lista->duplaCrescente) limpaListaDupla(&lista->duplaCrescente);
    if (lista->duplaDividida) limpaListaDupla(&lista->duplaDividida);

    free(lista);
}