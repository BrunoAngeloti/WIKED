#ifndef ListaContribuicao_h
#define ListaContribuicao_h

typedef struct listaContribuicao ListaContribuicao;

#include <stdio.h>
#include "Contribuicao.h"

/*Inicializa lista de contribuicoes
 * inputs: -
 * output: ponteiro para a lista de contribuicoes inicializada
 * pre-condicao: -
 * pos-condicao: lista de contribuicoes de retorno existe
 */
ListaContribuicao* InicListaContribuicao ();

/*Insere uma contribuicao em uma lista de contribuicoes
 * inputs: lista de contribuicao e a contribuicao
 * output: -
 * pre-condicao: lista de contribuicao existe e contribuicao existe
 * pos-condicao: contribuicao inserida na lista com sucesso
 */
void InsereListaContribuicao (ListaContribuicao* lista, Contribuicao* contri);

/*Encontra a pagina dada e manda imprimir as suas contribuicoes
 * inputs: lista de contribuicoes, nome da pagina e o arquivo de log
 * output: -
 * pre-condicao: lista de contribuicoes exite e arquivo de log ja aberto
 * pos-condicao: -
 */
void ImprimeListaContribuicao (ListaContribuicao* lista, char* pag, FILE* arq);

/*Encontra a pagina dada e manda imprimir os textos de suas contribuicoes
 * inputs: lista de contribuicoes, nome da pagina e o arquivo de log
 * output: -
 * pre-condicao: lista de contribuicoes exite e arquivo de log ja aberto
 * pos-condicao: -
 */
void ImprimeListaTextosContribuicao (ListaContribuicao* lista, char* pag, FILE* arq);

/*Retira uma contribuicao da lista de contribuicoes
 * inputs: lista de contribuicoes, nome da pagina, nome do editor, nome da contribuicao e o arquivo de log
 * output: ponteiro para uma contribuicao
 * pre-condicao: lista de contribuicoes existe e arquivo de log ja aberto
 * pos-condicao: contribuicao retirada da lista com sucesso
 */
Contribuicao* RetiraListaContribuicao (ListaContribuicao* lista, char* nome, char* ed, char* text, FILE* log);

/*Libera memória alocada para a lista de contribuicoes
 * inputs: lista de contribuicoes
 * output: -
 * pre-condicao: lista de contribuicoes existe
 * pos-condicao: toda a memória alocada para lista de contribuicoes foi liberada
 */
void DestroiListaContribuicao (ListaContribuicao* lista);

/*Verifica se aquela contribuicao informada existe
 * inputs: lista de contribuicoes, o nome da pagina e o nome da contribuicao que sera procurada
 * output: 0 caso a contribuicao exista e 1 caso nao exista
 * pre-condicao: lista de contribuicaos existe
 * pos-condicao: -
 */
int VerificaExistenciaContribuicao (ListaContribuicao* contri, char* nome, char* pag);

#endif