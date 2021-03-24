#include <stdio.h>
#ifndef EDITORES_H_
#define EDITORES_H_

typedef struct editor Editor;

/*Inicializa editor com o nome dele
 * inputs: nome do editor
 * output: ponteiro para o editor inicializado
 * pre-condicao: nome existe
 * pos-condicao: editor de retorno existe e contem seu nome
 */
Editor* IniciaEditor (char* nome);

/*Retorna o nome do editor
 * inputs: editor ed
 * output: ponteiro para o nome do editor
 * pre-condicao: editor ed existe
 * pos-condicao: editor nao e modificado
 */
char* RetornaNomeEditor (Editor* ed);

/*Libera memória alocada para o editor
 * inputs: editor ed
 * output: -
 * pre-condicao: editor ed existe
 * pos-condicao: toda a memória alocada para o editor foi liberada
 */
void DestroiEditor (Editor* ed);

#endif