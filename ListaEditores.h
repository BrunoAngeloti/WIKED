#ifndef ListaEditores_h
#define ListaEditores_h

#include <stdio.h>
#include "Editores.h"

typedef struct listaEditor ListaEditor;

/*Inicializa lista de editores
 * inputs: -
 * output: ponteiro para a lista de editores inicializada
 * pre-condicao: -
 * pos-condicao: lista de editores de retorno existe
 */
ListaEditor* InicListaEditor ();

/*Insere um editor em uma lista de editores
 * inputs: lista de editores, editor e o arquivo de log
 * output: -
 * pre-condicao: lista de editores existe, editor existe e arquivo ja aberto
 * pos-condicao: editor inserido na lista com sucesso
 */
void InsereListaEditor (ListaEditor* lista, Editor* ed, FILE* log);

/*Libera memória alocada para a lista de editores
 * inputs: lista de editores
 * output: -
 * pre-condicao: lista de editores existe
 * pos-condicao: toda a memória alocada para lista de editores foi liberada
 */
void DestroiListaEditor (ListaEditor* lista);

/*Verifica se aquele editor informado existe
 * inputs: lista de editores e o nome do editor que sera procurado
 * output: 1 caso o editor exista e 0 caso nao exista
 * pre-condicao: lista de editores existe
 * pos-condicao: -
 */
int VerificaExistenciaEditor (ListaEditor* ed, char* nome);

#endif