#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaProducao.h"

No* cria_lista(){
    return NULL;
}

void libera_lista(No* li){   
    No* no_temporario;      //ponteiro temporario pra percorrer a lista
        while(li != NULL){ //loop q fica repetindo enquanto a lista nao ta nula
            no_temporario = li; //guarda o no atual
            li = li -> next; //avanca pro proximo
            free(no_temporario);    //libera a memoria do no q guardou
        }
    }

int consulta_por_codigo(No* li, int codigo){

}