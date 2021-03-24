#include "Editores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct editor{
    char* nome;
};

// Funcao que inicializa editor
Editor* IniciaEditor (char* nome){
    Editor* ed = (Editor*) malloc(sizeof(Editor));

    // Utiliza o strdup para alocacao direta da string
    ed->nome = strdup(nome);

    free(nome);
    return ed;
}

// Funcao que retorna o nome do editor
char* RetornaNomeEditor (Editor* ed){
    return ed->nome;
}

// Funcao que libera memória alocada para o editor
void DestroiEditor (Editor* ed){
    free(ed->nome);
    free(ed);
}


