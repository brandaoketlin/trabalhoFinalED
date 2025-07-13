#include <stdio.h>      
#include <stdlib.h>     
#include "listaProducao.h"

//função para exibir o menu de opções para o usuário
void exibir_menu() { //função 'exibir_menu'
    printf("\n--- Sistema de Acompanhamento de Producao Agricola ---\n"); //título do sistema na tela
    printf("1. Incluir Producao\n");   //opção 1 do menu
    printf("2. Consultar\n");         //opção 2 do menu
    printf("3. Alterar Producao\n");  //opção 3 do menu
    printf("4. Excluir Producao\n");  //opção 4 do menu
    printf("5. Listar Todos\n");      //opção 5 do menu
    printf("6. Sair\n");              //opção 6 do menu
    printf("Escolha uma opcao: ");   //solicitação para o usuário digitar a opção desejada
}

// Função para exibir o submenu de consulta
void exibir_submenu_consulta() { //define a função 'exibir_submenu_consulta'
    printf("\n--- Opcoes de Consulta ---\n");  //imprime o título do submenu
    printf("1. Consultar por Data\n");      //imprime a opção 1 do submenu
    printf("2. Consultar por Cultivar\n"); //imprime a opção 2 do submenu
    printf("3. Voltar ao menu principal\n"); //imprime a opção para retornar ao menu anterior
    printf("Escolha uma opcao: ");        //imprime a solicitação para o usuário digitar a opção desejada
}

// Função principal que inicia e controla o programa
int main() { // Início da função principal do programa
    No* lista = cria_lista(); //declara um ponteiro 'lista' e o inicializa como uma lista vazia (NULL) chamando a função cria_lista()
    int opcao, codigo;      //declara variáveis do tipo inteiro para guardar a opção do menu e os códigos de produção
    Producao p;             //declara uma variável do tipo 'Producao' para armazenar temporariamente os dados de uma produção
    
    do { //inicia um loop 'do-while', que garante que o menu seja exibido pelo menos uma vez antes de checar a condição de parada
        exibir_menu(); //chama a função que mostra as opções do menu principal na tela
        scanf("%d", &opcao); //lê o número inteiro digitado pelo usuário e o armazena na variável 'opcao'

        switch (opcao) { //inicia uma estrutura 'switch' para executar o bloco de código correspondente à 'opcao' escolhida
            case 1: // se o usuário escolheu a opção 1 (Incluir Produção)
                printf("\n--- Incluir Nova Producao ---\n"); //exibe um título para a operação na tela
                le_producao(&p); //chama a função 'le_producao' para ler os dados da nova produção do teclado e guardar na variável 'p'
                
                if (consulta_por_codigo(lista, p.codigo)) { //verifica se já existe uma produção com o mesmo código, chamando sua função de consulta
                    printf("ERRO: Codigo de producao %d ja existe! Inclusao cancelada.\n", p.codigo); //se o código já existe, exibe uma mensagem de erro
                } else { // Se o código não existe
                    lista = insere_lista_ordenado_data(lista, p); // chama a função de inserção e atualiza o ponteiro 'lista' com o novo início da lista
                    printf("Producao incluida com sucesso!\n"); //informa ao usuário que a inclusão foi bem-sucedida
                }
                break; //termina a execução do 'case 1' e sai do 'switch'

            case 2: //se o usuário escolheu a opção 2 (Consultar)
                { //abre um bloco de código para declarar variáveis que só serão usadas dentro deste 'case'
                    int sub_opcao; //declara uma variável para a opção do submenu
                    do { //inicia um loop 'do-while' para o submenu de consulta
                        exibir_submenu_consulta(); //mostra as opções do submenu na tela
                        scanf("%d", &sub_opcao); //lê a opção do submenu digitada pelo usuário

                        switch (sub_opcao) { //inicia um 'switch' para a opção do submenu
                            case 1: //se a sub-opção for 1 (Consulta por Data)
                                { //abre um novo bloco de código
                                    Data d; //cria uma estrutura 'Data' temporária para armazenar a data da busca
                                    printf("Digite a data da consulta (dd mm aaaa): "); //pede a data ao usuário
                                    scanf("%d %d %d", &d.dia, &d.mes, &d.ano); //lê a data fornecida pelo usuário
                                    consulta_por_data(lista, d); //chama a sua função de consulta por data
                                }
                                break; //sai do 'case 1' do submenu
                            case 2: //se a sub-opção for 2 (Consulta por Cultivar)
                                { //abre um novo bloco de código
                                    char cultivar_busca[20]; //cria uma string para guardar o nome do cultivar a ser buscado
                                    printf("Digite o nome do cultivar para a consulta: "); //pede o nome do cultivar ao usuário
                                    scanf("%s", cultivar_busca); //lê o nome digitado pelo usuário
                                    consulta_por_cultivar(lista, cultivar_busca); //chama a sua função de consulta por cultivar
                                }
                                break; //sai do 'case 2' do submenu
                            case 3: //se a sub-opção for 3 (Voltar)
                                printf("Voltando ao menu principal...\n"); //informa que está voltando
                                break; //sai do 'switch' do submenu o que consequentemente encerrará o loop 'do-while'
                            default: //caso o usuário digite uma opção que não existe no submenu
                                printf("Opcao invalida! Tente novamente.\n"); //mensagem de erro
                        }
                    } while (sub_opcao != 3); //loop do submenu continua repetindo até que o usuário escolha a opção 3 para sair
                }
                break; // Termina a execução do 'case 2' e sai do 'switch' principal

            case 3: //se o usuário escolheu a opção 3 (Alterar)
                printf("\n--- Alterar Producao ---\n"); //exibe um título para a operação na tela
                printf("Digite o codigo da producao que deseja alterar: "); //pede o código do registro que será alterado
                scanf("%d", &codigo); //lê o código digitado pelo usuário
                if (!altera_lista(lista, codigo)) { //chama a sua função de alteração e verifica se ela retornou 0 (falha)
                    printf("ERRO: Producao com codigo %d nao encontrada.\n", codigo); //se falhou informa que o código não foi encontrado
                } else { //se a função retornou 1 (sucesso)
                    printf("Producao alterada com sucesso!\n"); //informa ao usuário que a alteração foi um sucesso
                }
                break; //termina o 'case 3'

            case 4: //se o usuário escolheu a opção 4 (Excluir)
                printf("\n--- Excluir Producao ---\n"); //exibe um título para a operação na tela
                printf("Digite o codigo da producao que deseja excluir: "); //pede o código do registro a ser excluído
                scanf("%d", &codigo); //lê o código digitado pelo usuário
                lista = remove_lista(lista, codigo); //chama a sua função de remoção e atualiza o ponteiro 'lista' com o novo início da lista retornado pela função
                break; //termina o 'case 4'

            case 5: //se o usuário escolheu a opção 5 (Listar Todos)
                lista_todos(lista); //chama a sua função que imprime todos os registros da lista na tela
                break; //termina o 'case 5'

            case 6: //se o usuário escolheu a opção 6 (Sair)
                printf("Finalizando o programa...\n"); //mensagem de despedida
                break; //sai do 'switch' o que fará com que a condição do loop 'do-while' seja falsa, encerrando o programa

            default: //se o usuário digitou uma opção que não existe no menu principal
                printf("Opcao invalida! Por favor, escolha uma opcao de 1 a 6.\n"); //mensagem de erro.
        }
    } while (opcao != 6); // O loop principal do programa continua em execução enquanto a opção escolhida for diferente de 6

    libera_lista(lista); // chama a sua função para percorrer a lista e liberar toda a memória alocada antes de fechar o programa
    lista = NULL; // atribui NULL ao ponteiro 'lista' manualmente para garantir que ele não aponte para memória inválida

    return 0; // retorna 0 indicando que o programa terminou com sucesso
}
