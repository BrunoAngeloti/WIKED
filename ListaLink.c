#include "ListaLink.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celLink CelulaLink;
static int AuxDoisCaminho(ListaLink* link, char* origem, char* destino, FILE* log, ListaPagina* paginas);

struct celLink{
    Link* link;
    CelulaLink* prox;
};

struct listaLink{
    CelulaLink* Prim;
    CelulaLink* Ult;
};

// Funcao para iniciar a lista de links
ListaLink* InicListaLink (){
    ListaLink* lista = (ListaLink*) malloc(sizeof(ListaLink));
    lista->Prim = NULL;
    lista->Ult = NULL;

    return lista;
}

// Funcao para inserir umm link na lista de links
void InsereListaLink (ListaLink* lista, Link* link, FILE* log){
    if(link == NULL){
        return;
    }
    // Condicional para tratar caso o link ja exista
    if(VerificaExistenciaLink(lista, RetornaOrigemLink(link), RetornaDestinoLink(link))){
        fprintf(log, "ERRO: Link de %s para %s ja existe!\n", RetornaOrigemLink(link), RetornaDestinoLink(link));
        DestroiLink(link);
        return;
    }
    CelulaLink* nova = (CelulaLink*) malloc (sizeof(CelulaLink));
    nova->link = link;

    nova->prox = lista->Prim;

    if(lista->Prim == NULL){
        lista->Prim = nova;
        lista->Ult = nova;
    }

    lista->Ult->prox = nova;
    lista->Ult = nova;
    nova->prox = NULL;
    
}

// Funcao que encontra o link que sera impresso e manda imprimir 
void ImprimeListaLink (ListaLink* lista, char* pag, FILE* arq){
    CelulaLink* p;

    for(p=lista->Prim; p!=NULL; p=p->prox){
        if(!(strcmp(RetornaOrigemLink(p->link), pag))){
            fprintf(arq, "%s %s\n", RetornaDestinoLink(p->link), RetornaArquivoDestinoLink(p->link)); 
        }          
    }
}

// Funcao que retira links da lista de links referentes a pagina retirada
void RetiraListaLinkPaginaRetirada(char* pag, ListaLink* links){
    CelulaLink* p;
    for(p=links->Prim; p!=NULL; p=p->prox){
        if(!(strcmp(RetornaDestinoLink(p->link), pag))){
            RetiraListaLink(links, RetornaOrigemLink(p->link), RetornaDestinoLink(p->link), NULL);
            p=links->Prim;
        }          
    }
}

// Funcao que retira um link da lista de links
Link* RetiraListaLink (ListaLink* lista, char* origem, char* destino, FILE* log){
    CelulaLink* p = lista->Prim;
    Link* link;
    CelulaLink* ant = NULL;

    while(p!=NULL && (strcmp(RetornaOrigemLink(p->link), origem) || strcmp(RetornaDestinoLink(p->link), destino))){
        ant = p;
        p = p->prox;
    }
    // Condicional para tratar caso o link solicitado nao exista
    if(p == NULL){
        fprintf(log, "ERRO: Nao existe o Link de %s para %s!\n", origem, destino);
        free(origem);
        free(destino);
        return NULL;
    }

    link = p->link;
    
    DestroiLink(p->link);
    
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
    if(log == NULL){
        return link;
    }
    free(origem);
    free(destino);

    return link;
}

// Funcao que libera memória alocada para a lista de links
void DestroiListaLink (ListaLink* lista){
    CelulaLink* p = lista->Prim;
    CelulaLink* t;

    while(p != NULL){
        t = p->prox;
        DestroiLink(p->link);
        free(p);
        p = t;
    } 

    free(lista);
}

// Funcao que verifica se aquele link informado existe
int VerificaExistenciaLink (ListaLink* link, char* origem, char* destino){
    CelulaLink* p = link->Prim;
    CelulaLink* ant = NULL;
   
    while(p!=NULL && (strcmp(RetornaOrigemLink(p->link), origem) || strcmp(RetornaDestinoLink(p->link), destino))){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return 0; // Caso nao exista
    }else{
        return 1; // Caso exista
    }
}

// Funcao local de recursividade para buscar os caminhos possiveis entre paginas declaradas 
static int HaCaminho(ListaLink* link, char* origem, char* destino, FILE* log, ListaPagina* paginas){
    CelulaLink* p;
    for(p=link->Prim; p!=NULL; p=p->prox){
        if(!(strcmp(RetornaOrigemLink(p->link), origem)) && !JaPassouPorEsteCaminho(paginas, RetornaDestinoLink(p->link))){
            // Funcao para marcar as paginas que ja foram verificadas para nao entrar em loop
            AlteraEstadoCaminho(paginas, RetornaOrigemLink(p->link));
            
            if(!(strcmp(RetornaDestinoLink(p->link), destino))){
                return 1;
            }else{
                // Caso nao encontre o destino que deseja, ele chama a funcao novamente usando o destino atual como origem
                if(HaCaminho(link, RetornaDestinoLink(p->link), destino, log, paginas)){
                    return 1;
                } 
            } 
        }      
    }
    return 0;
}

// Funcao que informa se existe caminho da origem para o destino informado
void Caminho(ListaLink* link, char* origem, char* destino, FILE* log, ListaPagina* paginas){

    // Utiliza o strdup para alocacao direta da string
    char* OrigemPadrao = strdup(origem);
    char* DestinoPadrao = strdup(destino);

    if(HaCaminho(link, origem, destino, log, paginas)){
        fprintf(log, "HA CAMINHO DA PAGINA %s PARA %s\n", OrigemPadrao, DestinoPadrao);
    }else{
        fprintf(log, "NAO HA CAMINHO DA PAGINA %s PARA %s\n", OrigemPadrao, DestinoPadrao);
    }

    free(origem);
    free(destino);
    free(OrigemPadrao);
    free(DestinoPadrao);  
    ZeraEstadoCaminhos(paginas);
}

