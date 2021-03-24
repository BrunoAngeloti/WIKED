#include <stdio.h>

#ifndef PAGINAS_H_
#define PAGINAS_H_

typedef struct pagina Pagina;

/*Inicializa pagina com o nome dela e seu arquivo
 * inputs: nome da pagina e o nome do arquivo
 * output: ponteiro para a pagina inicializada
 * pre-condicao: nome e nome do arquivo existem
 * pos-condicao: pagina de retorno existe e contem nome e arquivo
 */
Pagina* IniciaPagina (char* nome, char* arquivo);

/*Imprime a pagina
 * inputs: pagina pag
 * output: -
 * pre-condicao: pagina pag existe
 * pos-condicao: -
 */
void ImprimePagina (Pagina* pag);

/*Retorna o nome do arquivo
 * inputs: pagina pag
 * output: ponteiro para o nome do arquivo
 * pre-condicao: pagina pag existe
 * pos-condicao: pagina nao e modificada
 */
char* RetornaArquivoPagina (Pagina* pag);

/*Retorna o nome da pagina
 * inputs: pagina pag
 * output: ponteiro para o nome da pagina
 * pre-condicao: pagina pag existe
 * pos-condicao: pagina nao e modificada
 */
char* RetornaNomePagina (Pagina* pag);

/*Libera memória alocada para a pagina
 * inputs: pagina pag
 * output: -
 * pre-condicao: pagina pag existe
 * pos-condicao: toda a memória alocada para pagina foi liberada
 */
void DestroiPagina (Pagina* pag);

/*Retorna se a pagina ja foi verificada no caminho
 * inputs: pagina pag
 * output: 1 se ja passou no caminho, 0 se nao passou
 * pre-condicao: pagina pag existe
 * pos-condicao: pagina nao e modificada
 */
int RetornaSePassou (Pagina* pag);

/*Altera se a pagina ja foi verificada no caminho
 * inputs: pagina pag
 * output: -
 * pre-condicao: pagina pag existe
 * pos-condicao: Passou da pagina modificado
 */
void AlteraPassouPagina (Pagina* pag);

/*Define todas as paginas como nao foram passadas no caminho
 * inputs: pagina pag
 * output: -
 * pre-condicao: pagina pag existe
 * pos-condicao: Passou da pagina modificado
 */
void ZeraPassouPagina (Pagina* pag);

#endif