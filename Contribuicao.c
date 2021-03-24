#include "Contribuicao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contribuicao{
    char* pag;
    char* ed;
    int deletado;
    char* texto;
};

// Funcao que ira iniciar a contribuicao
Contribuicao* IniciaContribuicao (char* pagina, char* ed, char* text){
    Contribuicao* contri = (Contribuicao*) malloc(sizeof(Contribuicao));

    // Utiliza o strdup para alocacao direta da string
    contri->pag = strdup(pagina);
    contri->ed = strdup(ed);
    contri->texto = strdup(text);
    contri->deletado = 0;

    free(pagina);
    free(ed);
    free(text);

    return contri;
}

// Funcao que ira imprimir a contribuicao
void ImprimeContribuicao (Contribuicao* contri, FILE* arq){
    
    // Condicao para tratar quando a contribuicao ja foi retirada
    if(contri->deletado == 1){
        fprintf(arq, "%s ", contri->ed);
        fprintf(arq, "%s <<retirada>>\n", contri->texto);
        return;
    }
    fprintf(arq, "%s ", contri->ed);
    fprintf(arq, "%s\n", contri->texto);
}

// Funcao que ira imprimir os textos da contribuicao
void ImprimeTextoContribuicao (Contribuicao* contri, FILE* arq){
    char c;
    // Condicao para tratar quando a contribuicao ja foi retirada
    if(contri->deletado == 1){
        return;
    }
    fprintf(arq, "\n\n-------- %s (%s) --------\n\n", contri->texto, contri->ed);
    FILE* texto = fopen(contri->texto, "r");

    // Loop que ira ler o arquivo ate o caracter EOF de final de texto
    while(1){
        c = getc(texto);
        if(c == EOF) break;
        fprintf(arq, "%c" , c); 
    }
    
    fclose(texto);
}

// Funcao que retorna o nome da contribuicao
char* RetornaNomeContribuicao(Contribuicao* contri){
    return contri->pag;
}

// Funcao que retorna o nome do texto da contribuicao
char* RetornaTextContribuicao(Contribuicao* contri){
    return contri->texto;
}

// Funcao que retorna o nome do editor da contribuicao
char* RetornaEdContribuicao(Contribuicao* contri){
    return contri->ed;
}

// Funcao que retorna o estado atual da contribuicao
int RetornaEstadoContribuicao(Contribuicao* contri){
    return contri->deletado;
}

// Funcao que retorna a contribuicao com o estado (deletado ou nao) atualizado
Contribuicao* AlteraEstadoContri(Contribuicao* contri){
    contri->deletado = 1;
    return contri;
}

// Funcao que libera a memoria da contribuicao
void DestroiContribuicao (Contribuicao* contri){
    free(contri->pag);
    free(contri->ed);
    free(contri->texto);
    free(contri);
}
