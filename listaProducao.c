// Arquivo: listaProducao.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaProducao.h"
#if defined(_WIN32) || defined(_WIN64)
#include <string.h>
#define strcasecmp _stricmp
#endif

//função para limpar o buffer do teclado.
void limpar_buffer_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


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

int consulta_por_codigo(No* li, int codigo){ //pra evitar duplicacao
    No* no_atual = li;  //ponteiro pra percorrer a lista
    while(no_atual != NULL){  //loop pra percorrer a lista ate o fim
        if(no_atual -> dados.codigo == codigo){  //compara o codigo do no_atual com o codigo que estamos procurando
            return 1; //encontrou = verdadeiro, retorna 1
        }
        no_atual = no_atual -> next; //se nao encontrou ele avanca pro proximo no da lista
    }
    return 0; //se termina o loop sem encontrar = falso, retorna 0
}

No* insere_lista_ordenado_data(No* li, Producao p) {
    No* novo_no = (No*)malloc(sizeof(No)); //aloca na memoria um espaco pra um novo no
    if(novo_no == NULL){ //verifica se alocacao falhou (retornou que e NULL)
        return li; // ai retorna a lista original sem alteracao
    }
    novo_no -> dados = p; //copia os dados da producao para os dados do novo_no
    //se a lista tiver vazia ou tem que colocar o novo_no antes do primeiro
    if (li == NULL || // verifica se a lista está vazia
        (li->dados.dataProducao.ano > p.dataProducao.ano) || // se o ano do primeiro no e maior que o do novo
        (li->dados.dataProducao.ano == p.dataProducao.ano && li->dados.dataProducao.mes > p.dataProducao.mes) || // se os anos são iguais e o mês e maior
        (li->dados.dataProducao.ano == p.dataProducao.ano && li->dados.dataProducao.mes == p.dataProducao.mes && li->dados.dataProducao.dia > p.dataProducao.dia)) { // se ano/mês são iguais e o dia e maior
        novo_no -> next = li; //  'proximo' do novo nó aponta para o antigo início da lista
        return novo_no;        // retorna o endereço do novo nó, que agora é o novo início da lista
        }
    //se for inserir o novo no no meio ou no final da lista
        No* atual = li; //cria ponteiro pra percorrer a lista do inicio
        while (atual -> next != NULL && //continua enquanto nao chega no fim da lista, loop pra achar a posicao
            (atual -> next -> dados.dataProducao.ano < p.dataProducao.ano|| //enquanto a data do prox. no for menor q a do novo
            (atual -> next -> dados.dataProducao.ano == p.dataProducao.ano && atual -> next -> dados.dataProducao.mes < p.dataProducao.mes)||
             (atual -> next -> dados.dataProducao.ano == p.dataProducao.ano && atual-> next -> dados.dataProducao.mes == p.dataProducao.mes && atual -> next -> dados.dataProducao.dia < p.dataProducao.dia))) {
        atual = atual -> next; // avança o ponteiro atual para o próximo no.
    }
     novo_no -> next = atual -> next; // faz o novo no apontar para o nó que estava depois do atual
    atual -> next = novo_no;          // faz o no atual apontar para o novo no, encaixando na lista

    return li; // Retorna o ponteiro original do início da lista pq o primeiro elemento não mudou
}

No* remove_lista(No* li, int codigo) { //define a função que recebe a lista e um código e retorna a lista atualizada
    if (li == NULL) { //verifica se a lista ta vazia
        return NULL;  //se estiver não tem nada pra remover então retorna NULL
    }

    No *anterior = NULL; //cria um ponteiro para guardar o no anterior (começa como nulo).
    No *atual = li;      //cria um ponteiro para percorrer a lista que começa do início (li)

    while (atual != NULL && atual -> dados.codigo != codigo) { //continua enquanto não achar o codigo e não chegar ao fim da lista
        anterior = atual;       //o no 'atual' se torna o 'anterior' na próxima linha
        atual = atual -> next; //o ponteiro 'atual' avança para o próximo no
    }

    if (atual == NULL) { //verifica se o elemento foi encontrado
        printf("ERRO: Producao com codigo %d nao encontrada.\n", codigo); //informa ao usuário que não encontrou
        return li; //retorna a lista original sem nenhuma alteração
    }

    if (anterior == NULL) {
        li = atual -> next;
    } else {
        anterior -> next = atual -> next;
    }

    free(atual);
    printf("Producao excluida com sucesso!\n");
    return li;
}

void consulta_por_data(No* li, Data d) { //define a funcão de consulta por uma data especifica
    if (li == NULL) return;              //se a lista não existe ou está vazia ela retorna
    No* no_atual = li;                   //cria um ponteiro para percorrer a lista
    int encontrou = 0;                   //cria um "aviso" para verificar se achou algum registro
    while (no_atual != NULL) {           //loop que percorre toda a lista
        if (no_atual -> dados.dataProducao.dia == d.dia && //compara o dia mês e ano do no atual com a data especifica
            no_atual -> dados.dataProducao.mes == d.mes &&
            no_atual -> dados.dataProducao.ano == d.ano) {
            printf("%02d/%02d/%d: %s - Tipo %c - %d Fardos\n", //imprime os dados formatados se encontrou o registro
                   no_atual -> dados.dataProducao.dia,      //dia da produção
                   no_atual -> dados.dataProducao.mes,      //mês da produção
                   no_atual -> dados.dataProducao.ano,      //ano da produção
                   no_atual -> dados.fardoProducao.cultivar,  //nome do cultivar
                   no_atual -> dados.fardoProducao.tipoDeFeno,//tipo do feno (A B ou C)
                   no_atual -> dados.qntFardos);           //quantidade de fardos
            encontrou = 1; // aviso para indicar que achou ao menos um registro
        }
        no_atual = no_atual -> next; //vai para o próximo no da lista
    }
    if (!encontrou) { //ao final do loop se o aviso 'encontrou' ainda for 0 é falso
        printf("Nenhum registro de producao encontrado para a data %02d/%02d/%d.\n", d.dia, d.mes, d.ano); //mensagem de erro
    }
}

void consulta_por_cultivar(No* li, char* cultivar) { //funcao pra somar e consultar producaos de um cultivar
    if (li == NULL) return; // Se a lista não existe ou está vazia ela retorna.

    int soma_A = 0, soma_B = 0, soma_C = 0; //declara variáveis para somar as quantidades de cada tipo de feno
    int diametro_A = 0, diametro_B = 0, diametro_C = 0; //declara variáveis para guardar o diâmetro de cada tipo

    No* no_atual = li; //ponteiro para percorrer a lista
    while (no_atual != NULL) { //inicia um loop que percorre toda a lista.
        // Compara (sem diferenciar maiúsculas/minúsculas) o cultivar do no com o nome procurado
        if (strcasecmp(no_atual->dados.fardoProducao.cultivar, cultivar) == 0) {
            if (no_atual->dados.fardoProducao.tipoDeFeno == 'A' || no_atual->dados.fardoProducao.tipoDeFeno == 'a') {
                soma_A += no_atual->dados.qntFardos;
                diametro_A = no_atual->dados.fardoProducao.diametro;
            } else if (no_atual->dados.fardoProducao.tipoDeFeno == 'B' || no_atual->dados.fardoProducao.tipoDeFeno == 'b') {
                soma_B += no_atual->dados.qntFardos;
                diametro_B = no_atual->dados.fardoProducao.diametro;
            } else if (no_atual->dados.fardoProducao.tipoDeFeno == 'C' || no_atual->dados.fardoProducao.tipoDeFeno == 'c') {
                soma_C += no_atual->dados.qntFardos;
                diametro_C = no_atual->dados.fardoProducao.diametro;
            }
        }
        no_atual = no_atual->next; //vai para o próximo no
    }

    int encontrou = 0; //cria um aviso ra verificar se alguma produção desse cultivar foi encontrada

    if (soma_A > 0) { //se a soma para o tipo A for maior que zero
        float diametro_m = (float)diametro_A / 100.0; //converte o diâmetro de centímetros para metros
        float area_base = diametro_m * diametro_m;    //calcula a área da base quadrada de um fardo
        int num_pilhas = ceil((float)soma_A / 3.0);  //calcula quantas pilhas são necessárias (arredondando para cima)
        float area_total = num_pilhas * area_base;    //calcula a área total multiplicando a área da base pelo número de pilhas
        printf("%s: Tipo A - %d fardos - Area Minima de Armazenagem: %.2f m2\n", cultivar, soma_A, area_total); //imprime o resultado formatado
        encontrou = 1; // Ativa o aviso
    }
    if (soma_B > 0) { //repete o mesmo processo para o feno do tipo B
        float diametro_m = (float)diametro_B / 100.0;
        float area_base = diametro_m * diametro_m;
        int num_pilhas = ceil((float)soma_B / 3.0);
        float area_total = num_pilhas * area_base;
        printf("%s: Tipo B - %d fardos - Area Minima de Armazenagem: %.2f m2\n", cultivar, soma_B, area_total);
        encontrou = 1;
    }
    if (soma_C > 0) { //repete mesmo processo para o feno do tipo C
        float diametro_m = (float)diametro_C / 100.0;
        float area_base = diametro_m * diametro_m;
        int num_pilhas = ceil((float)soma_C / 3.0);
        float area_total = num_pilhas * area_base;
        printf("%s: Tipo C - %d fardos - Area Minima de Armazenagem: %.2f m2\n", cultivar, soma_C, area_total);
        encontrou = 1;
    }

    if (!encontrou) { //após todas as verificacões e o aviso encontrou continuar falso
        printf("Nenhum registro encontrado para o cultivar '%s'.\n", cultivar); //informa q nao achou nada
    }
}

void le_producao(Producao *p) { //função que recebe um ponteiro para uma estrutura 'Producao'.
    printf("Digite o codigo da producao: ");         //mensagem pedindo o código
    scanf("%d", &p -> codigo);                         //le o número inteiro digitado e o armazena no campo 'codigo' da estrutura
    limpar_buffer_teclado(); // Limpa o buffer para a próxima leitura

    printf("Digite a data (dd mm aaaa): ");          //pede a data
    scanf("%d %d %d", &p -> dataProducao.dia, &p -> dataProducao.mes, &p -> dataProducao.ano); //le os três inteiros da data
    limpar_buffer_teclado(); // Limpa o buffer para a próxima leitura

    printf("Digite o cultivar (Tifton85, Florakirk, Jiggs, Coastcross): "); //pede o nome do cultivar
    scanf("%s", p -> fardoProducao.cultivar);           //lê a string digitada e a armazena no campo 'cultivar'
    limpar_buffer_teclado(); // Limpa o buffer para a próxima leitura

    printf("Digite o tipo de feno (A, B ou C): ");     //pede o tipo de feno
    scanf(" %c", &p -> fardoProducao.tipoDeFeno);        //lê o caractere do tipo de feno (o espaço antes de %c ignora espaços em branco e 'Enters')
    limpar_buffer_teclado(); // Limpa o buffer para a próxima leitura

    printf("Digite o diametro do fardo em cm (80 a 160): "); //pede o diâmetro
    scanf("%d", &p -> fardoProducao.diametro);          //le o diâmetro
    limpar_buffer_teclado(); // Limpa o buffer para a próxima leitura

    printf("Digite a quantidade de fardos: ");         //pede a quantidade
    scanf("%d", &p -> qntFardos);                     //lê a quantidade
    limpar_buffer_teclado(); // Limpa o buffer para a próxima leitura

    printf("Digite o tempo de producao em minutos: "); //pede o tempo
    scanf("%d", &p -> tempoMin);                     //le o tempo
    limpar_buffer_teclado(); // Limpa o buffer ao final
}

int altera_lista(No* li, int codigo) { //função q altera um registro q ja existe buscando pelo codigo
    if (li == NULL) return 0; //se a lista está vazia retorna 0

    No* no_atual = li; //ponteiro para percorrer a lista
    while (no_atual != NULL && no_atual -> dados.codigo != codigo) { //loop para encontrar o nó com o código que precisa
        no_atual = no_atual -> next; //vai pro próximo no
    }

    if (no_atual == NULL) { //se o loop terminou e não encontrou o nó
        return 0; //retorna 0 (não encontrou)
    }

    //se encontrou pede para digitar os novos dados
    printf("--- Digite os NOVOS dados para a producao codigo %d ---\n", codigo);
    Producao p_alterada; //cria uma estrutura 'Producao' temporária para receber os novos dados
    le_producao(&p_alterada); //chama a função auxiliar para preencher a estrutura temporária

    p_alterada.codigo = codigo; //garante que o código original seja mantido pq ele é a chave de busca
    no_atual -> dados = p_alterada; //copia todos os novos dados da estrutura temporária para o nó encontrado na lista

    return 1; // Retorna 1 (deu boa)
}

void lista_todos(No* li) { //função q lista todos os registros de producao na lista
    if (li == NULL) { //verifica se a lista está vazia
        printf("Nenhum registro de producao cadastrado.\n"); //se estiver informa
        return; //e finaliza a função.
    }
    printf("\n--- LISTA DE TODAS AS PRODUCOES (Ordenado por data) ---\n"); //título para a listagem
    No* no_atual = li; //ponteiro para percorrer a lista
    while (no_atual != NULL) { //loop que vai até o fim da lista
        Producao p = no_atual -> dados; //copia os dados do nó atual para uma variável local 'p' para facilitar o acesso
        printf("----------------------------------------\n"); //linha divisória
        printf("Codigo: %d\n", p.codigo); //imprime
        printf("Data: %02d/%02d/%d\n", p.dataProducao.dia, p.dataProducao.mes, p.dataProducao.ano); //imprime a data formatada
        printf("Cultivar: %s\n", p.fardoProducao.cultivar); //imprime o cultivar
        printf("Tipo do Feno: %c\n", p.fardoProducao.tipoDeFeno); //imprime o tipo do feno
        printf("Diametro: %d cm\n", p.fardoProducao.diametro); //imprime o diâmetro
        printf("Quantidade: %d fardos\n", p.qntFardos); //imprime a quantidade
        printf("Tempo: %d min\n", p.tempoMin); //imprime o tempo

        no_atual = no_atual -> next; //vai para o próximo nó da lista
    }
    printf("----------------------------------------\n\n");
}