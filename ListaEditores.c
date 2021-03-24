#include "ListaEditores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celEditor CelulaEditor;

struct celEditor{
    Editor* ed;
    CelulaEditor* prox;
};

struct listaEditor{
    CelulaEditor* Prim;
    CelulaEditor* Ult;
};

// Funcao para iniciar a lista de editores
ListaEditor* InicListaEditor (){
    ListaEditor* lista = (ListaEditor*) malloc(sizeof(ListaEditor));
    lista->Prim = NULL;
    lista->Ult = NULL;

    return lista;
}

// Funcao para inserir um editor na lista de editores
void InsereListaEditor (ListaEditor* lista, Editor* ed, FILE* log){

    // Condicional para tratar caso um editor ja exista
    if(VerificaExistenciaEditor(lista, RetornaNomeEditor(ed))){
        fprintf(log, "ERRO: Editor %s ja existe!\n", RetornaNomeEditor(ed));
        DestroiEditor(ed);
        return;
    }
    CelulaEditor* nova = (CelulaEditor*) malloc (sizeof(CelulaEditor));
    nova->ed = ed;

    nova->prox = lista->Prim;

    if(lista->Prim == NULL){
        lista->Prim = nova;
        lista->Ult = nova;
    }

    lista->Ult->prox = nova;
    lista->Ult = nova;
    nova->prox = NULL;
}

// Funcao que libera a memoria da lista de editores
void DestroiListaEditor (ListaEditor* lista){
    CelulaEditor* p = lista->Prim;
    CelulaEditor* t;

    while(p != NULL){
        t = p->prox;
        DestroiEditor(p->ed);
        free(p);
        p = t;
    } 

    free(lista);
}

// Funcao que verifica se aquele editor informado existe
int VerificaExistenciaEditor (ListaEditor* ed, char* nome){
    CelulaEditor* p = ed->Prim;
    CelulaEditor* ant = NULL;
   
    while(p!=NULL && strcmp(RetornaNomeEditor(p->ed), nome)){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return 0; // Caso nao exista
    }else{
        return 1; // Caso exista
    }
}