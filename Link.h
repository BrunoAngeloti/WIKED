#ifndef LINK_H_
#define LINK_H_
#include <stdio.h>

typedef struct link Link;

/*Inicializa link com a origem e o destino
 * inputs: nome da origem, nome do destino, texto da origem e texto do destino
 * output: ponteiro para o link inicializada
 * pre-condicao: paginas de origem e destino existem
 * pos-condicao: link de retorno existe e contem a origem e o destino
 */
Link* IniciaLink (char* origem, char* destino, char* arquivoO, char* arquivoD);

/*Libera memória alocada para o link
 * inputs: link link
 * output: -
 * pre-condicao: link link existe
 * pos-condicao: toda a memória alocada para link foi liberada
 */
void DestroiLink (Link* link);

/*Retorna o destino do link
 * inputs: link link
 * output: ponteiro para o destino do link
 * pre-condicao: link link existe
 * pos-condicao: link nao e modificada
 */
char* RetornaDestinoLink(Link* link);

/*Retorna o origem do link
 * inputs: link link
 * output: ponteiro para o origem do link
 * pre-condicao: link link existe
 * pos-condicao: link nao e modificada
 */
char* RetornaOrigemLink(Link* link);

/*Retorna o arquivo de origem do link
 * inputs: link link
 * output: ponteiro para o arquivo de origem do link
 * pre-condicao: link link existe
 * pos-condicao: link nao e modificada
 */
char* RetornaArquivoOrigemLink(Link* link);

/*Retorna o arquivo de destino do link
 * inputs: link link
 * output: ponteiro para o arquivo de destino do link
 * pre-condicao: link link existe
 * pos-condicao: link nao e modificada
 */
char* RetornaArquivoDestinoLink(Link* link);

#endif