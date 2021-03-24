#include "ListaPaginas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celPagina CelulaPagina;

struct celPagina{
    Pagina* pag;
    CelulaPagina* prox;
};

struct listaPagina{
    CelulaPagina* Prim;
    CelulaPagina* Ult;
};

// Funcao para iniciar a lista de paginas
ListaPagina* InicListaPagina(){
    ListaPagina* lista = (ListaPagina*) malloc(sizeof(ListaPagina));
    lista->Prim = NULL;
    lista->Ult = NULL;

    return lista;
}

// Funcao para inserir uma pagina na lista de paginas
void InsereListaPagina (ListaPagina* lista, Pagina* pag, FILE* log){
    
    // Condicional para tratar caso uma pagina ja exista
    if(VerificaExistenciaPagina(lista, RetornaNomePagina(pag))){
        fprintf(log, "ERRO: Pagina %s ja existe!\n", RetornaNomePagina(pag));
        DestroiPagina(pag);
        return;
    }
    CelulaPagina* nova = (CelulaPagina*) malloc (sizeof(CelulaPagina));
    nova->pag = pag;
    nova->prox = lista->Prim;

    if(lista->Prim == NULL){
        lista->Prim = nova;
        lista->Ult = nova;
    }

    lista->Ult->prox = nova;
    lista->Ult = nova;
    nova->prox = NULL;
}

// Funcao que chama todas as funcoes necessarias para imprimir a WikiEd toda
void ImprimeWiki (ListaPagina* lista, ListaContribuicao* contri, ListaLink* link){
    CelulaPagina* p;

    for(p=lista->Prim; p!=NULL; p=p->prox){
        ImprimePagina(p->pag);
        FILE* saida = fopen(RetornaArquivoPagina(p->pag), "a");
        ImprimeListaContribuicao(contri, RetornaNomePagina(p->pag), saida);
        fprintf(saida, "\n--> Links\n");
        ImprimeListaLink(link, RetornaNomePagina(p->pag), saida);
        ImprimeListaTextosContribuicao(contri, RetornaNomePagina(p->pag), saida);
        fclose(saida);
    }
}

// Funcao que encontra a pagina que sera impressa e manda imprimir 
Pagina* ImprimeListaPagina (ListaPagina* lista, char* arquivo, FILE* log){
    CelulaPagina* p = lista->Prim;
    CelulaPagina* ant = NULL;

    while(p!=NULL && strcmp(RetornaNomePagina(p->pag), arquivo)){
        ant = p;
        p = p->prox;
    }

    // Condicional para tratar caso a pagina nao exista
    if(p == NULL){       
        fprintf(log, "ERRO: Nao existe a pagina %s\n", arquivo);
        free(arquivo);
        return NULL;
    }
    // Manda imprimir a pagina
    ImprimePagina(p->pag);
    free(arquivo);
    return p->pag;
}

// Funcao que retira uma pagina da lista de paginas
void RetiraListaPagina (ListaPagina* lista, char* arquivo, FILE* log, ListaLink* links){
    CelulaPagina* p = lista->Prim;
    Pagina* pag;
    CelulaPagina* ant = NULL;

    while(p!=NULL && strcmp(RetornaNomePagina(p->pag), arquivo)){
        ant = p;
        p = p->prox;
    }

    // Condicional para tratar caso a pagina nao exista
    if(p == NULL){
        fprintf(log, "ERRO: Nao existe a pagina %s\n", arquivo);
        free(arquivo);
        return;
    }

    pag = p->pag;
    RetiraListaLinkPaginaRetirada(RetornaNomePagina(p->pag), links);
    DestroiPagina(p->pag);
    
    if(p == lista->Prim && p == lista->Ult){
        lista->Prim = lista->Ult = NULL;
    }else if(p == lista->Prim){
        lista->Prim = p->prox;
    }else if(p == lista->Ult){
        lista->Ult = ant;
        lista->Ult->prox = NULL;
    }else{
        ant->prox = p->prox;
    }
    free(p);
    free(arquivo);
}

// Funcao que libera a memoria da lista de paginas
void DestroiListaPagina (ListaPagina* lista){
    CelulaPagina* p = lista->Prim;
    CelulaPagina* t;

    while(p != NULL){
        t = p->prox;
        DestroiPagina(p->pag);
        free(p);
        p = t;
    } 

    free(lista);
}

// Funcao que verifica se aquela pagina informada existe
int VerificaExistenciaPagina (ListaPagina* pag, char* nome){
    CelulaPagina* p = pag->Prim;
    CelulaPagina* ant = NULL;
   
    while(p!=NULL && strcmp(RetornaNomePagina(p->pag), nome)){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return 0; // Caso nao exista
    }else{
        return 1; // Caso exista
    }
}

// Funcao que encontra aquela pagina informada
Pagina* EncontraPagina (ListaPagina* pag, char* nome){
    CelulaPagina* p = pag->Prim;
    CelulaPagina* ant = NULL;
   
    while(p!=NULL && strcmp(RetornaNomePagina(p->pag), nome)){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return NULL; // Caso nao encontre
    }else{
        return p->pag; // Caso encontre
    }
}

// Funcao que mostra se ja passou por esse caminho na busca de caminho
int JaPassouPorEsteCaminho(ListaPagina* pag, char* nome){
    return RetornaSePassou(EncontraPagina(pag, nome));
}

// Funcao que altera valor do caminho em uma determinada pagina
void AlteraEstadoCaminho(ListaPagina* pag, char* nome){
    AlteraPassouPagina(EncontraPagina(pag, nome));
}

// Funcao que zera o valor do caminho em todas as paginas
void ZeraEstadoCaminhos(ListaPagina* pag){
    CelulaPagina* p;
    for(p=pag->Prim; p!=NULL; p=p->prox){
        ZeraPassouPagina (p->pag);
    }
}
