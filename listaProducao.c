#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaProducao.h"

No* cria_lista(){
    return NULL;
}

void libera_lista(No** li){ 
    if(li != NULL);{        //verifica se ta valido
        No* no_atual;       //ponteiro temporario pra percorrer a lista
        while((*li) != NULL){ //loop q fica repetindo enquanto a lista nao ta nula
            no_atual = (*li); //guarda o no atual
            (*li) = (*li) -> next; //avanca pro proximo
            free(no_atual);    //libera a memoria do no q guardou
        }
    }
}