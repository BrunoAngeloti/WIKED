#include "ListaContribuicao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celContribuicao CelulaContribuicao;

struct celContribuicao{
    Contribuicao* contri;
    CelulaContribuicao* prox;
};

struct listaContribuicao{
    CelulaContribuicao* Prim;
    CelulaContribuicao* Ult;
};

// Funcao para iniciar a lista de contribuicoes
ListaContribuicao* InicListaContribuicao (){
    ListaContribuicao* lista = (ListaContribuicao*) malloc(sizeof(ListaContribuicao));
    lista->Prim = NULL;
    lista->Ult = NULL;

    return lista;
}

// Funcao para inserir uma contribuicao na lista de contribuicoes
void InsereListaContribuicao (ListaContribuicao* lista, Contribuicao* contri){
    if(contri == NULL){
        return;
    }
    CelulaContribuicao* nova = (CelulaContribuicao*) malloc (sizeof(CelulaContribuicao));
    nova->contri = contri;

    nova->prox = lista->Prim;

    if(lista->Prim == NULL){
        lista->Prim = nova;
        lista->Ult = nova;
    }

    lista->Ult->prox = nova;
    lista->Ult = nova;
    nova->prox = NULL;
    
}

// Funcao que encontra as contribuicoes da pagina dada e manda imprimi-las 
void ImprimeListaContribuicao (ListaContribuicao* lista, char* pag, FILE* arq){
    CelulaContribuicao* p;

    for(p=lista->Prim; p!=NULL; p=p->prox){
        if(!(strcmp(RetornaNomeContribuicao(p->contri), pag))){
            ImprimeContribuicao(p->contri, arq);  
        }          
    }
    
}

// Funcao que encontra as contribuicoes da pagina dada e manda imprimir seus textos
void ImprimeListaTextosContribuicao (ListaContribuicao* lista, char* pag, FILE* arq){
    CelulaContribuicao* p;
    fprintf(arq, "\n--> Textos");
    for(p=lista->Prim; p!=NULL; p=p->prox){
        if(!(strcmp(RetornaNomeContribuicao(p->contri), pag))){
            ImprimeTextoContribuicao(p->contri, arq);  
        }          
    }
}

// Funcao que retira uma contribuicao da lista decontribuicoes
Contribuicao* RetiraListaContribuicao (ListaContribuicao* lista, char* nome, char* ed, char* text, FILE* log){
    CelulaContribuicao* p = lista->Prim;
    Contribuicao* contri;
    CelulaContribuicao* ant = NULL;

    while(p!=NULL && (strcmp(RetornaNomeContribuicao(p->contri), nome) || strcmp(RetornaEdContribuicao(p->contri), ed) || strcmp(RetornaTextContribuicao(p->contri), text))){
        ant = p;
        p = p->prox;
    }
    // Condicional para tratar caso a contribuicao nao exista ou o editor nao seja o mesmo
    if(p == NULL){
        fprintf(log, "ERRO: Nao existe a contribuicao %s ou você não é o editor desta contribuicao!\n", text);
        free(nome);
        free(ed);
        free(text);
        return NULL;
    }

    contri = p->contri;
    contri = AlteraEstadoContri(contri);

    free(nome);
    free(ed);
    free(text);
    return contri;
}

// Funcao que libera a memoria da lista de contribuicoes
void DestroiListaContribuicao (ListaContribuicao* lista){
    CelulaContribuicao* p = lista->Prim;
    CelulaContribuicao* t;

    while(p != NULL){
        t = p->prox;
        DestroiContribuicao(p->contri);
        free(p);
        p = t;
    } 

    free(lista);
}

// Funcao que verifica se aquela contribuicao informada existe
int VerificaExistenciaContribuicao (ListaContribuicao* contri, char* nome, char* pag){
    CelulaContribuicao* p = contri->Prim;
    CelulaContribuicao* ant = NULL;
   
    while(p!=NULL && (strcmp(RetornaTextContribuicao(p->contri), nome) || strcmp(RetornaNomeContribuicao(p->contri), pag))){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return 1; // Caso nao exista
    }else{
        return 0; // Caso exista
    }
}