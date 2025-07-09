#ifndef LISTAPRODUCAO_H //para náo incluir mais de uma vez esse arquivo
#define LISTAPRODUCAO_H //pra indicar que o arquivo ja foi incluido
#include <math.h> //biblioteca pra usar no cal. da area

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct fardo{
    char cultivar[20]; //coloquei 20 so como base, nao sabia quantos char guardar
    char tipoDeFeno;
    int diametro;
} Fardo;

typedef struct producao{
    int codigo;
    Data dataProducao; //estrutura Data para armezenar a data da prod
    Fardo fardoProducao; //estrutura Fardo para as infos de fardo
    int qntFardos;
    int tempoMin;
} Producao;

//ESTRUTURA DA LISTA ENCADEADA
typedef struct no{
    Producao dados;//cada no vai armezenar todos os dados do registro de 'Producao'
    struct no* next; //ponteiro q aponta pro prox no na sequencia
} No;

//PROTOT DAS FUNCOES(TIPO UM MENU) 
No* cria_lista(); //funcao pra criar e iniciar a lista
void libera_lista(No** li); //funcao pra liberar a memoria que a lista usou

int insere_lista_ordenada_data(No** li, Producao p); //inserir registro na lista de producao em ordem pela data
int consulta_por_codigo(No* li, int codigo); //funcao auxiliar pra procurar um registro pelo codigo
void consulta_por_data(No* li, Data d); //cunsultar producao por data
void consulta_por_cultivar(No* li, char* cultivar); //consultar producao e somar de um cultivar
int altera_lista(No* li, int codigo); //altera registro que ja existe buscando pelo codigo
int remove_lista(No** li, int codigo); //remove registro buscando pelo codigo tambem
void lista_todos(No* li); //mostrar todos os registros de producao na lista

#endif
