#include <stdio.h>      
#include <stdlib.h>     
#include "listaProducao.h"

//função para exibir o menu de opções para o usuário
void exibir_menu() {
    printf("\n--- Sistema de Acompanhamento de Producao Agricola ---\n");
    printf("1. Incluir Producao\n");
    printf("2. Consultar\n");
    printf("3. Alterar Producao\n");
    printf("4. Excluir Producao\n");
    printf("5. Listar Todos\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para exibir o submenu de consulta
void exibir_submenu_consulta() {
    printf("\n--- Opcoes de Consulta ---\n");
    printf("1. Consultar por Data\n");
    printf("2. Consultar por Cultivar\n");
    printf("3. Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");
}

// Função principal que inicia e controla o programa
int main() {
    No* lista = cria_lista();
    int opcao, codigo;
    Producao p;
    
    do {
        exibir_menu();
        
        //tenta ler um número. Se conseguir, scanf retorna 1. Se falhar (ex: usuário digitou uma letra), retorna 0
        if (scanf("%d", &opcao) != 1) {
            printf("\nERRO: Entrada invalida! Por favor, digite um numero de 1 a 6.\n"); //avisa sobre o erro
            limpar_buffer_teclado(); //chama a função que limpa a entrada inválida do teclado
            opcao = 0; //define um valor padrão para 'opcao' para que o switch não execute nenhum case e o loop continue
        }

        switch (opcao) {
            case 1:
                printf("\n--- Incluir Nova Producao ---\n");
                le_producao(&p);
                
                if (consulta_por_codigo(lista, p.codigo)) {
                    printf("ERRO: Codigo de producao %d ja existe! Inclusao cancelada.\n", p.codigo);
                } else {
                    lista = insere_lista_ordenado_data(lista, p);
                    printf("Producao incluida com sucesso!\n");
                }
                break;

            case 2:
                {
                    int sub_opcao;
                    do {
                        exibir_submenu_consulta();
                        if (scanf("%d", &sub_opcao) != 1) {
                            printf("\nERRO: Entrada invalida! Por favor, digite um numero.\n");
                            limpar_buffer_teclado();
                            sub_opcao = 0;
                        }

                        switch (sub_opcao) {
                            case 1:
                                {
                                    Data d;
                                    printf("Digite a data da consulta (dd mm aaaa): ");
                                    scanf("%d %d %d", &d.dia, &d.mes, &d.ano);
                                    consulta_por_data(lista, d);
                                }
                                break;
                            case 2:
                                {
                                    char cultivar_busca[20];
                                    printf("Digite o nome do cultivar para a consulta: ");
                                    scanf("%s", cultivar_busca);
                                    consulta_por_cultivar(lista, cultivar_busca);
                                }
                                break;
                            case 3:
                                printf("Voltando ao menu principal...\n");
                                break;
                            default:
                                if(sub_opcao != 0) { // Evita mostrar a mensagem de erro duas vezes
                                    printf("Opcao invalida! Tente novamente.\n");
                                }
                        }
                    } while (sub_opcao != 3);
                }
                break;

            case 3:
                printf("\n--- Alterar Producao ---\n");
                printf("Digite o codigo da producao que deseja alterar: ");
                scanf("%d", &codigo);
                if (!altera_lista(lista, codigo)) {
                    printf("ERRO: Producao com codigo %d nao encontrada.\n", codigo);
                } else {
                    printf("Producao alterada com sucesso!\n");
                }
                break;

            case 4:
                printf("\n--- Excluir Producao ---\n");
                printf("Digite o codigo da producao que deseja excluir: ");
                scanf("%d", &codigo);
                lista = remove_lista(lista, codigo);
                break;

            case 5:
                lista_todos(lista);
                break;

            case 6:
                printf("Finalizando o programa...\n");
                break;

            default:
                if (opcao != 0) { //evita mostrar a mensagem de erro duas vezes
                    printf("Opcao invalida! Por favor, escolha uma opcao de 1 a 6.\n");
                }
        }
    } while (opcao != 6);

    libera_lista(lista);
    lista = NULL;

    return 0;
}