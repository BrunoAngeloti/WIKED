#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaPaginas.h"
#include "ListaEditores.h"
#include "ListaContribuicao.h"
#include "ListaLink.h"

// Funcao para liberar memoria de vetores usados para leitura e comparacao durante o codigo
void liberaMemoriaLocal(char* a, char* b, char* c){
    if(a != NULL) free(a);
    if(b != NULL) free(b);
    if(c != NULL) free(c);
}

// Funcao para ler a entrada da funcao e alocar dinamicamente
char* leEntrada(FILE* arq){
    char funcao[50];
    //RETIRACONTRIBUICAO
    fscanf(arq, "%s", funcao);
    return strdup(funcao);
}

// Funcao que insere uma pagina em uma lista de paginas
void INSEREPAGINA(FILE* entrada, ListaPagina* paginas, FILE* log){
    char* nomePagina = leEntrada(entrada);
    char* nomeArquivo = leEntrada(entrada);
    //Inicia a pagina e ja manda de argumento para a funcao de inserir na lista
    InsereListaPagina(paginas, IniciaPagina(nomePagina, nomeArquivo), log);
}

// Funcao que retira uma pagina de uma lista de paginas
void RETIRAPAGINA(FILE* entrada, ListaPagina* paginas, FILE* log, ListaLink* links){
    char* nomeArquivo = leEntrada(entrada);
    RetiraListaPagina(paginas, nomeArquivo, log, links);
}

// Funcao que insere um editor em uma lista de editores
void INSEREEDITOR(FILE* entrada, ListaEditor* editores, FILE* log){
    char* nomeEditor = leEntrada(entrada);
    //Inicia o editor e ja manda de argumento para a funcao de inserir na lista
    InsereListaEditor(editores, IniciaEditor(nomeEditor), log);
}

// Funcao que insere uma contribuicao em uma lista de contribuicoes 
void INSERECONTRIBUICAO(FILE* entrada, ListaPagina* paginas, ListaEditor* editores, ListaContribuicao* contri, FILE* log){
    char* nomePagina = leEntrada(entrada);
    char* nomeEditor = leEntrada(entrada);
    char* nomeArquivo = leEntrada(entrada);

    // Condicionais para tratar casos em que a entrada nao bate com os dados ja existentes
    if(!VerificaExistenciaPagina(paginas, nomePagina)){
        fprintf(log, "ERRO: Pagina %s inexistente\n", nomePagina);
        liberaMemoriaLocal(nomePagina, nomeEditor, nomeArquivo);
  
    }else if(!VerificaExistenciaEditor(editores, nomeEditor)){
        fprintf(log, "ERRO: Editor %s inexistente\n", nomeEditor);
        liberaMemoriaLocal(nomePagina, nomeEditor, nomeArquivo);
 
    }else if(!VerificaExistenciaContribuicao(contri, nomeArquivo, nomePagina)){
        fprintf(log, "ERRO: Contribuicao %s ja foi adicionada na pagina %s!\n", nomeArquivo, nomePagina);
        liberaMemoriaLocal(nomePagina, nomeEditor, nomeArquivo);
    }else{
        //Inicia a contribuicao e ja manda de argumento para a funcao de inserir na lista
        InsereListaContribuicao(contri, IniciaContribuicao(nomePagina, nomeEditor, nomeArquivo));
    }
}

// Funcao que retira uma contribuicao de uma lista de contribuicoes
void RETIRACONTRIBUICAO(FILE* entrada, ListaContribuicao* contri, FILE* log){
    char* nomePagina = leEntrada(entrada);
    char* nomeEditor = leEntrada(entrada);
    char* nomeArquivo = leEntrada(entrada);
    RetiraListaContribuicao(contri, nomePagina, nomeEditor, nomeArquivo, log);
}

// Funcao que insere um link em uma lista de links
void INSERELINK(FILE* entrada, ListaPagina* paginas, ListaLink* links, FILE* log){
    char* nomeOrigem = leEntrada(entrada);
    char* nomeDestino = leEntrada(entrada);

    // Condicionais para tratar casos em que a entrada nao bate com os dados ja existentes
    if(!VerificaExistenciaPagina(paginas, nomeOrigem)){
        fprintf(log, "ERRO: Pagina de origem %s inexistente\n", nomeOrigem);
        liberaMemoriaLocal(nomeDestino, nomeOrigem, NULL);

    }else if(!VerificaExistenciaPagina(paginas, nomeDestino)){
        fprintf(log, "ERRO: Pagina de destino %s inexistente\n", nomeDestino);
        liberaMemoriaLocal(nomeDestino, nomeOrigem, NULL);

    }else{
        char* nomeArquivoOrigem = strdup(RetornaArquivoPagina(EncontraPagina (paginas, nomeOrigem)));
        char* nomeArquivoDestino = strdup(RetornaArquivoPagina(EncontraPagina (paginas, nomeDestino)));
        //Inicia o link e ja manda de argumento para a funcao de inserir na lista
        InsereListaLink(links, IniciaLink(nomeOrigem, nomeDestino, nomeArquivoOrigem, nomeArquivoDestino), log);
    }
}

// Funcao que retira um link de uma lista de links
void RETIRALINK(FILE* entrada, ListaLink* links, FILE* log){
    char* nomeOrigem = leEntrada(entrada);
    char* nomeDestino = leEntrada(entrada);
    RetiraListaLink(links, nomeOrigem, nomeDestino, log);
}

void CAMINHO(FILE* entrada, ListaLink* links, FILE* log, ListaPagina* paginas){
    char* paginaOrigem = leEntrada(entrada);
    char* paginaDestino = leEntrada(entrada);

    // Condicionais para tratar casos em que a entrada nao bate com os dados ja existentes
    if(!VerificaExistenciaPagina(paginas, paginaOrigem)){
        fprintf(log, "ERRO: Pagina de origem %s inexistente\n", paginaOrigem);
        liberaMemoriaLocal(paginaDestino, paginaOrigem, NULL);

    }else if(!VerificaExistenciaPagina(paginas, paginaDestino)){
        fprintf(log, "ERRO: Pagina de destino %s inexistente\n", paginaDestino);
        liberaMemoriaLocal(paginaDestino, paginaOrigem, NULL);

    }else{
        Caminho(links, paginaOrigem, paginaDestino, log, paginas);
    }
}

// Funcao que imprime uma pagina especifica 
void IMPRIMEPAGINA(FILE* entrada, ListaPagina* paginas, ListaContribuicao* contri, ListaLink* links, FILE* log){
    char* nomePagina = leEntrada(entrada);
    Pagina* aux = ImprimeListaPagina(paginas, nomePagina, log);
    // Condicional para verificar se a pagina que deseja imprimir realmente existe
    if(aux != NULL){
        // Funcoes para imprimir a pagina
        FILE* saida = fopen(RetornaArquivoPagina(aux), "a");
        ImprimeListaContribuicao(contri, RetornaNomePagina(aux), saida);  
        ImprimeListaLink(links, RetornaNomePagina(aux), saida);
        ImprimeListaTextosContribuicao(contri, RetornaNomePagina(aux), saida);       
        fclose(saida);
    }
}

// Funcao que trata entrada de uma funcao nao utilizada na wikED
void FUNCAONAOEXISTE(FILE* entrada, FILE* log, char* funcao){
    char lixo;
    fprintf(log, "Função %s não suportada nesta versão da WikED\n", funcao);
    while(1){
        //Joga o lixo fora caso tenha apos uma funcao que nao exista
        fscanf(entrada, "%c", &lixo); 
        if(lixo == '\n') break;
    }
}

int main(int argc, char *argv[]){

    //Verifica se o diretorio de arquivos de entrada foi informado
    if (argc <= 1) {    
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return 1;
    }

    //Cria a variavel para uso de leitura da funcao de entrada
    char* funcao;
    
    //Inicia arquivos de entrada e log
    FILE* entrada = fopen(argv[1], "r");
    FILE* log = fopen("log.txt", "a");
    
    //Inicia listas de paginas, editores, links e contribuicoes
    ListaPagina* paginas = InicListaPagina();
    ListaEditor* editores = InicListaEditor();
    ListaLink* links = InicListaLink();
    ListaContribuicao* contri = InicListaContribuicao();

    while(1){
        funcao = leEntrada(entrada); // Le a entrada e aloca dinamicamente o vetor funcao
        if(!strcmp(funcao, "INSEREPAGINA")){
            INSEREPAGINA(entrada, paginas, log); 

        }else if(!strcmp(funcao, "RETIRAPAGINA")){
            RETIRAPAGINA(entrada, paginas, log, links);

        }else if(!strcmp(funcao, "INSEREEDITOR")){
            INSEREEDITOR(entrada, editores, log);

        }else if(!strcmp(funcao, "INSERECONTRIBUICAO")){
            INSERECONTRIBUICAO(entrada, paginas, editores, contri, log);
            
        }else if(!strcmp(funcao, "RETIRACONTRIBUICAO")){
            RETIRACONTRIBUICAO(entrada, contri, log);
            
        }else if(!strcmp(funcao, "INSERELINK")){
            INSERELINK(entrada, paginas, links, log);
               
        }else if(!strcmp(funcao, "RETIRALINK")){
            RETIRALINK(entrada, links, log);
            
        }else if(!strcmp(funcao, "CAMINHO")){
            CAMINHO(entrada, links, log, paginas);
            
        }else if(!strcmp(funcao, "IMPRIMEPAGINA")){
            IMPRIMEPAGINA(entrada, paginas, contri, links, log);

        }else if(!strcmp(funcao, "IMPRIMEWIKED")){
            ImprimeWiki(paginas, contri, links);
            
        }else if(!strcmp(funcao, "FIM")){
            free(funcao);
            break;
        }else{
            // Funcao caso a entrada nao seja uma funcao existente
            FUNCAONAOEXISTE(entrada, log, funcao);
        }
        free(funcao);
    }
    
    // Libera todas as listas
    DestroiListaPagina(paginas);
    DestroiListaEditor(editores);
    DestroiListaLink(links);
    DestroiListaContribuicao(contri);

    // Fecha os arquivos abertos
    fclose(entrada);
    fclose(log);

    return 0;
}
