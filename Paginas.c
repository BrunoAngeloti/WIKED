#include "Paginas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pagina{
    char* nome;
    char* arquivo;
    int passou;
};

// Funcao que ira iniciar a pagina
Pagina* IniciaPagina (char* nome, char* arquivo){ 
    Pagina* pag = (Pagina*) malloc(sizeof(Pagina));
    
    // Utiliza o strdup para alocacao direta da string
    pag->nome = strdup(nome);
    pag->arquivo = strdup(arquivo);
    pag->passou = 0;

    free(arquivo);
    free(nome);
    return pag;
}

// Funcao que ira imprimir a pagina
void ImprimePagina (Pagina* pag){   
    FILE* arq = fopen(pag->arquivo, "w");
    fprintf(arq, "%s\n\n--> Historico de contribuicoes\n", pag->nome);
    fclose(arq);
}

// Funcao que retorna o nome da pagina
char* RetornaNomePagina (Pagina* pag){
    return pag->nome;
}

// Funcao que retorna o arquivo da pagina
char* RetornaArquivoPagina (Pagina* pag){
    return pag->arquivo;
}

// Funcao que retorna se a pagina ja foi verificada no caminho
int RetornaSePassou (Pagina* pag){
    return pag->passou;
}

// Funcao que altera se a pagina ja foi verificada no caminho
void AlteraPassouPagina (Pagina* pag){
    pag->passou = 1;
}

// Funcao que define todas as paginas como nao foram passadas no caminho
void ZeraPassouPagina (Pagina* pag){
    pag->passou = 0;
}

// Funcao que libera a memoria da pagina
void DestroiPagina (Pagina* pag){
    free(pag->nome);
    free(pag->arquivo);
    free(pag);
}

