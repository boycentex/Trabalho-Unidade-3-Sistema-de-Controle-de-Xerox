#include"xerox.h"
// Sistema de Controle de Xerox 
/* objetivo: manter o controle dos pedidos de xerox da universidade realizados por alunos, professores e funcionarios, alem de controlar os custos e volumes de copias realizadas
*/

void menu(){ 
    printf("escolha uma opcao\n");
    printf("1. Adicionar pedido de xerox\n");
    printf("2. Excluir pedido de xerox;\n");
    printf("3. Listar pedidos de xerox\n");
    printf("4. Buscar pedido por numero ou nome do solicitante\n");
    printf("5. Editar dados do pedido\n");
    printf("6. Consultar pedidos por status\n");
    printf("7. Consultar total de copias realizadas e valor arrecadado\n");
    printf("8. Sair\n");
    printf("\n");
}


int main() {
    setlocale(LC_ALL, "Portuguese");

    No *lista = NULL;
    int opcao;
    char entrada[10];

    do {
        menu();

        int entrada_valida = 0;
        while (!entrada_valida) {
            scanf("%s", entrada); 

            if (validar_opcao(entrada)) {
                opcao = atoi(entrada); 
                entrada_valida = 1;  
            } else {
                printf("Entrada invalida\n");
            }
        }

        switch(opcao) {
            case 1:
                lista = adicionar_pedido(lista);
                printf("Pedido Adicionado\n");
                salvar_pedidos(lista);
                break;

            case 2: {
                int num;
                printf("Informe o numero do pedido que deseja excluir: ");
                scanf("%d", &num);
                lista = excluir(lista, num);
                excluir_arquivo(num);
                break;
            }

            case 3:
                printf("Lista de Pedidos:\n");
                listar();
                break;

            case 4: {
                int num;
                No *aux;
                printf("Informe o numero do pedido para realizar a busca\n");
                scanf("%d", &num);
                aux = buscar(lista, num);
                if (aux == NULL) {
                    printf("Pedido nao encontrado\n");
                    int x;
                    printf("Deseja criar um novo pedido?\n");
                    printf("1 - para sim.\n");
                    printf("0 - para nao.\n");
                    scanf("%d", &x);
                    if (x == 1) {
                        lista = adicionar_pedido(lista);
                        atualizar_arquivo(lista);
                        printf("Novo pedido adicionado com sucesso\n");
                    }
                } else {
                    pedido_achado(aux);
                }
                break;
            }

            case 5: {
                int num;
                printf("Informe o numero do pedido que deseja editar\n");
                scanf("%d", &num);
                lista = editar_pedido(lista, num);
                atualizar_arquivo(lista);
                break;
            }

            case 6:
                consultar_status(lista);
                break;

            case 7:
                copias_e_valor(lista);
                break;

            case 8:
            printf("saindo\n");
            break;
            
            default:            
                printf("Opcao invalida, tente novamente.\n");
                break;
        }
    } while (opcao != 8);

    printf("operacao finalizada\n");

    return 0;
}