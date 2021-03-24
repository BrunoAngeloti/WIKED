#ifndef CONTRIBUICAO_H_
#define CONTRIBUICAO_H_
#include <stdio.h>

typedef struct contribuicao Contribuicao;
#include "ListaEditores.h"
#include "ListaPaginas.h"

/*Inicializa contribuicao com o nome dela, nome do arquivo e editor
 * inputs: nome da pagina, nome do editor e o nome do arquivo
 * output: ponteiro para a contribuicao inicializada
 * pre-condicao: nome da pagina, nome editor e nome do arquivo existem
 * pos-condicao: pagina de retorno existe e contem nome, nome editor e arquivo
 */
Contribuicao* IniciaContribuicao (char* pagina, char* ed, char* text);

/*Imprime a contribuicao
 * inputs: contribuicao contri e o arquivo de saida
 * output: -
 * pre-condicao: contribuicao contri existe e arquivo ja aberto
 * pos-condicao: -
 */
void ImprimeContribuicao (Contribuicao* contri, FILE* arq);

/*Imprime os textos da contribuicao
 * inputs: contribuicao contri e o arquivo de saida
 * output: -
 * pre-condicao: contribuicao contri existe e arquivo ja aberto
 * pos-condicao: -
 */
void ImprimeTextoContribuicao (Contribuicao* contri, FILE* arq);

/*Retorna o nome da contribuicao
 * inputs: contribuicao contri
 * output: ponteiro para o nome da contribuicao
 * pre-condicao: contribuicao contri existe
 * pos-condicao: contribuicao nao e modificada
 */
char* RetornaNomeContribuicao(Contribuicao* contri);

/*Retorna o nome do texto da contribuicao
 * inputs: contribuicao contri
 * output: ponteiro para o nome do texto da contribuicao
 * pre-condicao: contribuicao contri existe
 * pos-condicao: contribuicao nao e modificada
 */
char* RetornaTextContribuicao(Contribuicao* contri);

/*Retorna o nome do editor da contribuicao
 * inputs: contribuicao contri
 * output: ponteiro para o nome do editor da contribuicao
 * pre-condicao: contribuicao contri existe
 * pos-condicao: contribuicao nao e modificada
 */
char* RetornaEdContribuicao(Contribuicao* contri);

/*Retorna o estado da contribuicao (deletado ou nao)
 * inputs: contribuicao contri
 * output: ponteiro para o estado da contribuicao
 * pre-condicao: contribuicao contri existe
 * pos-condicao: contribuicao nao e modificada
 */
int RetornaEstadoContribuicao(Contribuicao* contri);

/*Retorna a contribuicao com o estado (deletado ou nao) atualizado
 * inputs: contribuicao contri
 * output: ponteiro para contribuicao
 * pre-condicao: contribuicao contri existe
 * pos-condicao: estado da contribuicao modificada
 */
Contribuicao* AlteraEstadoContri(Contribuicao* contri);

/*Libera memória alocada para a contribuicao
 * inputs: contribuicao contri
 * output: -
 * pre-condicao: contribuicao contri existe
 * pos-condicao: toda a memória alocada para contribuicao foi liberada
 */
void DestroiContribuicao (Contribuicao* contri);

#endif