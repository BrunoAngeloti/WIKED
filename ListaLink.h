#ifndef ListaLink_h
#define ListaLink_h

typedef struct listaLink ListaLink;

#include <stdio.h>
#include "Link.h"
#include "ListaPaginas.h"

/*Inicializa lista de links
 * inputs: -
 * output: ponteiro para a lista de links inicializada
 * pre-condicao: -
 * pos-condicao: lista de links de retorno existe
 */
ListaLink* InicListaLink ();

/*Insere um link em uma lista de links
 * inputs: lista de link, um link e arquivo log
 * output: -
 * pre-condicao: lista de link existe, link existe e arquivo ja aberto
 * pos-condicao: link inserido na lista com sucesso
 */
void InsereListaLink (ListaLink* lista, Link* link, FILE* log);

/*Encontra o link que sera impresso e manda imprimir 
 * inputs: lista de links, nome da pagina que sera verificada e o arquivo de saida
 * output: -
 * pre-condicao: lista de links existe e arquivo de saida ja aberto
 * pos-condicao: -
 */
void ImprimeListaLink (ListaLink* lista, char* pag, FILE* arq);

/*Retira um link da lista de links
 * inputs: lista de links, nome da origem do link, nome do destino do link e o arquivo de log
 * output: -
 * pre-condicao: lista de link existe e arquivo de log ja aberto
 * pos-condicao: link retirado da lista com sucesso
 */
Link* RetiraListaLink (ListaLink* lista, char* origem, char* destino, FILE* log);

/*Libera memória alocada para a lista de links
 * inputs: lista de links
 * output: -
 * pre-condicao: lista de links existe
 * pos-condicao: toda a memória alocada para lista de links foi liberada
 */
void DestroiListaLink (ListaLink* lista);

/*Verifica se aquele link informado existe
 * inputs: lista de links, nome da origem e nome do destino
 * output: 1 caso a pagina exista e 0 caso nao exista
 * pre-condicao: lista de links existe
 * pos-condicao: -
 */
int VerificaExistenciaLink (ListaLink* link, char* origem, char* destino);


/*Informa se existe caminho da origem para o destino informado
 * inputs: lista de links, nome da origem, nome do destino, arquivo de log e lista de paginas
 * output: -
 * pre-condicao: lista de link existe, pagina de origem e destino existem, arquivo de log aberto e lista de paginas existe
 * pos-condicao: caminho informado com sucesso
 */
void Caminho(ListaLink* link, char* origem, char* destino, FILE* log, ListaPagina* paginas);

/*Retira links da lista de links referentes a pagina retirada 
 * inputs: nome da pagina e a lista de links
 * output: -
 * pre-condicao: lista de link existe
 * pos-condicao: links retirados da lista com sucesso
 */
void RetiraListaLinkPaginaRetirada(char* pag, ListaLink* links);

#endif