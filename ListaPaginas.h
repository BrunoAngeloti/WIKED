#ifndef ListaPaginas_h
#define ListaPaginas_h

#include <stdio.h>

typedef struct listaPagina ListaPagina;
#include "Paginas.h"
#include "ListaContribuicao.h"
#include "ListaLink.h"

/*Inicializa lista de paginas
 * inputs: -
 * output: ponteiro para a lista de paginas inicializada
 * pre-condicao: -
 * pos-condicao: lista de paginas de retorno existe
 */
ListaPagina* InicListaPagina();

/*Insere uma pagina em uma lista de paginas
 * inputs: lista de pagina, pagina e o arquivo de log
 * output: -
 * pre-condicao: lista de pagina existe, pagina existe e arquivo ja aberto
 * pos-condicao: Pagina inserida na lista com sucesso
 */
void InsereListaPagina (ListaPagina* lista, Pagina* pag, FILE* log);

/*Chama todas as funcoes necessarias para imprimir a WikiEd toda
 * inputs: lista de paginas, lista de contribuicoes e lista de links
 * output: -
 * pre-condicao: lista de pagina existe, lista de contribuicoes existe e lista de links existe
 * pos-condicao: -
 */
void ImprimeWiki (ListaPagina* lista, ListaContribuicao* contri, ListaLink* link);

/*Encontra a pagina que sera impressa e manda imprimir 
 * inputs: lista de paginas, nome da pagina que sera impressa e o arquivo de log
 * output: ponteiro para a pagina que foi impressa
 * pre-condicao: lista de pagina existe e arquivo de log ja aberto
 * pos-condicao: -
 */
Pagina* ImprimeListaPagina (ListaPagina* lista, char* arquivo, FILE* Log);

/*Retira uma pagina da lista de paginas
 * inputs: lista de paginas, nome da pagina que sera retirada e o arquivo de log
 * output: -
 * pre-condicao: lista de pagina existe e arquivo de log ja aberto
 * pos-condicao: pagina retirada da lista com sucesso
 */
void RetiraListaPagina (ListaPagina* lista, char* arquivo, FILE* log, ListaLink* links);

/*Libera memória alocada para a lista de paginas
 * inputs: lista de paginas
 * output: -
 * pre-condicao: lista de paginas existe
 * pos-condicao: toda a memória alocada para lista de paginas foi liberada
 */
void DestroiListaPagina (ListaPagina* lista);

/*Verifica se aquela pagina informada existe
 * inputs: lista de paginas e o nome da pagina que sera procurada
 * output: 1 caso a pagina exista e 0 caso nao exista
 * pre-condicao: lista de paginas existe
 * pos-condicao: -
 */
int VerificaExistenciaPagina (ListaPagina* pag, char* nome);

/*Encontra uma pagina na lista
 * inputs: lista de paginas e o nome da pagina que sera procurada
 * output: pagina que foi procurada
 * pre-condicao: lista de paginas existe
 * pos-condicao: lista de pagina nao modificada
 */
Pagina* EncontraPagina (ListaPagina* pag, char* nome);

/*Mostra se ja passou por esse caminho na busca de caminho
 * inputs: lista de paginas e o nome da pagina
 * output: 0 para nao passou e 1 para se ja passou
 * pre-condicao: lista de paginas existe
 * pos-condicao: lista de pagina nao modificada
 */
int JaPassouPorEsteCaminho(ListaPagina* pag, char* nome);

/*Altera valor do caminho em uma determinada pagina
 * inputs: lista de paginas e o nome da pagina
 * output: -
 * pre-condicao: lista de paginas existe
 * pos-condicao: pagina com o Estado do caminho alterado
 */
void AlteraEstadoCaminho(ListaPagina* pag, char* nome);

/*Zera o valor do caminho em todas as paginas
 * inputs: lista de paginas
 * output: -
 * pre-condicao: lista de paginas existe
 * pos-condicao: Estados dos caminhos das paginas zerados novamente
 */
void ZeraEstadoCaminhos(ListaPagina* pag);

#endif