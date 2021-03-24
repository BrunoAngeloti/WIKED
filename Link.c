#include "Link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct link{
    char* destino;
    char* origem;
    char* arquivoDestino;
    char* arquivoOrigem;
};

// Funcao que ira iniciar o link
Link* IniciaLink (char* origem, char* destino, char* arquivoO, char* arquivoD){
    Link* link = (Link*) malloc(sizeof(Link));

    // Utiliza o strdup para alocacao direta da string
    link->destino = strdup(destino);
    link->origem = strdup(origem);
    link->arquivoDestino = strdup(arquivoD);
    link->arquivoOrigem = strdup(arquivoO);

    free(origem);
    free(destino);
    free(arquivoO);
    free(arquivoD);

    return link;
}

// Funcao que libera a memoria do link
void DestroiLink (Link* link){
    free(link->destino);
    free(link->origem);
    free(link->arquivoDestino);
    free(link->arquivoOrigem);
    free(link);
}

// Funcao que retorna a origem da pagina
char* RetornaOrigemLink(Link* link){
    return link->origem;
}

// Funcao que retorna o destino da pagina
char* RetornaDestinoLink(Link* link){
    return link->destino;
}

// Funcao que retorna o arquivo de destino da pagina
char* RetornaArquivoDestinoLink(Link* link){
    return link->arquivoDestino;
}

// Funcao que retorna o arquivo de origem da pagina
char* RetornaArquivoOrigemLink(Link* link){
    return link->arquivoOrigem;
}
