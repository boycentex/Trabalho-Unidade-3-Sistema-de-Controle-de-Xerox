#include"xerox.h"

typedef struct xerox{
    int numero_do_pedido;
    char nome_do_solicitante[50]; 
    char tipo_do_solicitante[20]; // (aluno, professor, funcionario)
    int quantidade_de_paginas;
    char data_do_pedido[10];
    float valor_total;
    char status_do_pedido[10]; // (pendente, concluıdo, cancelado)
}Xerox;

typedef struct no
{
    Xerox *xerox;
    struct no* proximo;
}No;

int validar_opcao(char *entrada) {
    // Verifica se todos os caracteres na string são dígitos
    for (int i = 0; i < strlen(entrada); i++) {
        if (!isdigit(entrada[i])) {
            return 0; // Retorna 0 se encontrar algum caractere não numérico
        }
    }
    return 1; // Retorna 1 se for um número válido
}

int validar_numeros(char *entrada2) {
    // Verifica se todos os caracteres na string são dígitos
    for (int i = 0; i < strlen(entrada2); i++) {
        if (!isdigit(entrada2[i])) {
            return 0; // Retorna 0 se encontrar algum caractere não numérico
        }
    }
    return 1; 
}

int validar_nome(char* nome) {
    int i;

    // Verifica cada caractere do nome
    for (i = 0; nome[i] != '\0'; i++) {
        // Permite apenas letras e espaços
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            printf("Nome invalido. Use apenas letras e espacos.\n");
            return 0;
        }
    }

    return 1; // Nome válido
}

int validar_tipo_solicitante(char* tipo) {
   
    if (strcmp(tipo, "aluno") == 0 || strcmp(tipo, "professor") == 0 || strcmp(tipo, "funcionario") == 0) {
        return 1;
    }
    printf("Tipo de solicitante invalido\n");
    return 0; 
}

int validar_status(char* status) {
    if (strcmp(status, "pendente") == 0 || strcmp(status, "concluido") == 0 || strcmp(status, "cancelado") == 0) {
        return 1;
    }
    printf("Status invalido\n");
    return 0; 
}

int validar_data(char* data) {
    int dia, mes, ano;
    char barra1, barra2;

    // Verifica se o formato é estritamente "dd/mm/aaaa"
    if (sscanf(data, "%d%c%d%c%d", &dia, &barra1, &mes, &barra2, &ano) != 5 || barra1 != '/' || barra2 != '/') {
        printf("Formato de data invalido\n");
        return 0;
    }

    // Verifica se o mês está entre 1 e 12
    if (mes < 1 || mes > 12) {
        printf("Formato de data invalido\n");
        return 0;
    }

    // Verifica se o dia está dentro do intervalo padrão de dias 
    if (dia < 1 || dia > 31 || (mes == 2 && dia > 29) || 
       ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)) {
        printf("Formato de data invalido\n");
        return 0;
    }

    if(ano < 2024){ 
        printf("ano invalido\n");
        return 0;
    }

    return 1; // Data válida
}

int validar_valor_total(char *entrada) {
    char *novo;
    strtof(entrada, &novo);
    float valor = strtof(entrada, &novo); 
    
    if (*novo != '\0' || valor <= 0) {
        // Se houver qualquer caractere após o número (exceto o terminador de string), é inválido
        return 0;
    }
    return 1;
}

void preencher(Xerox* novo){ 
    int numvalido;
    char entrada2[10];
    char entrada3[10];
    char entrada4[10];
    int nomevalido;
    int tipovalido;
    int datavalida;
    char status[20];

    do {
        printf("Informe o numero do pedido\n");
        scanf("%s", entrada2); // Lê a entrada como string

        if (validar_numeros(entrada2)) {
            novo->numero_do_pedido = atoi(entrada2); // Converte a string para inteiro
            numvalido = 1;    // Marca a entrada como válida
        } else {
            printf("Entrada invalida\n");
            numvalido = 0;
        }
    } while(!numvalido);

    
    do {
        printf("Informe o nome do solicitante\n");
        scanf(" %[^\n]", novo->nome_do_solicitante);
        nomevalido = validar_nome(novo->nome_do_solicitante); 
    } while (!nomevalido); 

    do {
        printf("Informe o tipo de solicitante (aluno/professor/funcionario)\n");
        scanf(" %[^\n]", novo->tipo_do_solicitante);
        tipovalido = validar_tipo_solicitante(novo->tipo_do_solicitante); 
    } while (!tipovalido);

    do {
        printf("Informe a quantidade de paginas\n");
        scanf("%s", entrada3); // Lê a entrada como string

        if (validar_numeros(entrada3)) {
            novo->quantidade_de_paginas = atoi(entrada3); // Converte a string para inteiro
            numvalido = 1;    // Marca a entrada como válida
        } else {
            printf("Entrada invalida\n");
            numvalido = 0;
        }
    } while(!numvalido);

    do {
        printf("Informe a data do pedido (formato dd/mm/aaaa):\n");
        scanf("%s", novo->data_do_pedido);
        datavalida = validar_data(novo->data_do_pedido); 
    } while (!datavalida);

    do{
        printf("Informe o valor do pedido:\n");
        scanf("%s", entrada4); // Lê a entrada como string
        if (validar_valor_total(entrada4)) {
            novo->valor_total = strtof(entrada4, NULL); // Converte a string para float
            numvalido = 1; // Marca a entrada como válida
        } else {
            printf("Entrada invalida.\n");
            numvalido = 0;
        }

    } while (!numvalido);

    do {
        printf("Informe o status do pedido (pendente/concluido/cancelado):\n");
        scanf("%19s", status);
    } while (!validar_status(status));

    strcpy(novo->status_do_pedido, status);

}

No* adicionar_pedido(No *lista){ 
    Xerox *novopedido = (Xerox*) malloc(sizeof(Xerox));
    if(novopedido == NULL){ 
        printf("erro\n");
        exit(1);
    }
    preencher(novopedido);

    No* novoNo = (No*) malloc(sizeof(No));
    if(novoNo == NULL){ 
        printf("erro\n");
        exit(1);
    }
    novoNo->xerox = novopedido;
    novoNo->proximo = lista;

    return novoNo;
}

void salvar_pedidos(No *lista){

    FILE *arq = fopen("pedidos.txt", "a+");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    No *aux = lista;
    while (aux != NULL) {
        // Escrever os dados no arquivo, separados por quebras de linha
        fprintf(arq, "Numero do pedido: %d\nNome do solicitante: %s\nTipo de solicitante: %s\nQuantidade de paginas: %d\nData do pedido: %s\nValor total: %.2f\nStatus do pedido: %s\n\n", 
                aux->xerox->numero_do_pedido, aux->xerox->nome_do_solicitante, 
                aux->xerox->tipo_do_solicitante, aux->xerox->quantidade_de_paginas, 
                aux->xerox->data_do_pedido, aux->xerox->valor_total, 
                aux->xerox->status_do_pedido);
        aux = aux->proximo;
    }

    fclose(arq); 
    printf("Pedidos salvos com sucesso!\n");

}

void atualizar_arquivo(No *lista){ 
    FILE *arquivo = fopen("pedidos.txt", "r+");
    if(arquivo == NULL){ 
        printf("Erro ao ler o arquivo\n");
        return;
    }
    No *aux = lista;
    while (aux != NULL) {
        
        fprintf(arquivo, "Numero do pedido:%d\nNome do solicitante:%s\nTipo de solicitante:%s\nQuantidade de paginas:%d\nData do pedido:%s\nValor total:%.2f\nStatus do pedido:%s\n", 
                aux->xerox->numero_do_pedido, aux->xerox->nome_do_solicitante, 
                aux->xerox->tipo_do_solicitante, aux->xerox->quantidade_de_paginas, 
                aux->xerox->data_do_pedido, aux->xerox->valor_total, 
                aux->xerox->status_do_pedido);
        aux = aux->proximo;
    }

    fclose(arquivo);
    printf("Pedido atualizado com sucesso!\n");
    printf("\n");
}

No *excluir(No *lista, int num) {
    if (lista == NULL) {
        printf("A lista esta vazia.\n");
        return NULL;
    }

    No *anterior = NULL;
    No *atual = lista;

    
    while (atual != NULL && atual->xerox->numero_do_pedido != num) {
        anterior = atual;
        atual = atual->proximo;
    }

    
    if (atual == NULL) {
        printf("Pedido com numero %d nao encontrado.\n", num);
        return lista;
    }

    // caso for o primeiro da lista
    if (anterior == NULL) {
        No *nova_raiz = atual->proximo;
        free(atual->xerox);
        free(atual);
        printf("Pedido numero %d excluido com sucesso.\n", num);
        return nova_raiz;
    }

    // caso estiver no meio ou no fim da lista
    anterior->proximo = atual->proximo;
    free(atual->xerox);
    free(atual);
    printf("Pedido numero %d excluido com sucesso.\n", num);
    return lista;
}

void listar() {
    
    FILE *arquivo = fopen("pedidos.txt", "r");
    if(arquivo == NULL){ 
        printf("erro na leitura ou arquivo nao existe\n");
        return;
    }
    char linhas[200];
    while (fgets(linhas, sizeof(linhas), arquivo) != NULL) { 
        
        printf("%s", linhas);
    }
    printf("\n");

    fclose(arquivo);

}

No *buscar(No *lista, int numero){ 
    if (lista == NULL)
    {
        printf("lista vazia\n");
        return NULL;
    }
    
    No *aux;
    for (aux = lista; aux != NULL; aux = aux->proximo)
    {
        if(aux->xerox->numero_do_pedido == numero){ 
            return aux;
        }
    }

    return NULL;
}

No* editar_pedido(No *lista, int numero) {
    if (lista == NULL) { 
        printf("lista vazia\n");
        return NULL;
    }

    No *aux = lista;
    
    while (aux != NULL && aux->xerox->numero_do_pedido != numero) {
        aux = aux->proximo;
    }

    if (aux == NULL) {
        printf("Pedido nao encontrado\n");
        return lista;
    }

    printf("Pedido número %d encontrado!\n", numero);

    int opcao;
    do {
        
        printf("1. Nome do solicitante\n");
        printf("2. Tipo de solicitante\n");
        printf("3. Quantidade de páginas\n");
        printf("4. Data do pedido\n");
        printf("5. Valor total\n");
        printf("6. Status do pedido\n");
        printf("0. Sair\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &opcao);
        int numvalido;
        char entrada3[10];
        char entrada4[10];
        int nomevalido;
        int tipovalido;
        int datavalida;
        char status[20];

        switch (opcao) {
            case 1:
                do {
                    printf("Novo nome do solicitante\n");
                    scanf(" %49[^\n]s", aux->xerox->nome_do_solicitante);
                    nomevalido = validar_nome(aux->xerox->nome_do_solicitante);
                } while (!nomevalido);
                
                break;
            case 2:
                do {
                    printf("Novo tipo de solicitante (aluno/professor/funcionario)\n");
                    scanf(" %[^\n]", aux->xerox->tipo_do_solicitante);
                    tipovalido = validar_tipo_solicitante(aux->xerox->tipo_do_solicitante);
                } while (!tipovalido);
                break;
            case 3:
                do {
                    printf("Informe a quantidade de paginas\n");
                    scanf("%s", entrada3); // Lê a entrada como string

                    if (validar_numeros(entrada3)) {
                        aux->xerox->quantidade_de_paginas = atoi(entrada3); // Converte a string para inteiro
                        numvalido = 1;    // Marca a entrada como válida
                } else {
                    printf("Entrada invalida\n");
                    numvalido = 0;
                }
                } while(!numvalido);
                break;
            case 4:
                do {
                    printf("Nova data do pedido (formato dd/mm/aaaa):\n");
                    scanf("%s", aux->xerox->data_do_pedido);
                    datavalida = validar_data(aux->xerox->data_do_pedido); 
                } while(!datavalida);
                break;
            case 5:
                do{
                    printf("Informe o valor do pedido:\n");
                    scanf("%s", entrada4); // Lê a entrada como string
                    if (validar_valor_total(entrada4)) {
                        aux->xerox->valor_total = strtof(entrada4, NULL); // Converte a string para float
                        numvalido = 1; // Marca a entrada como válida
                    } else {
                        printf("Entrada invalida.\n");
                        numvalido = 0;
                    }

                } while (!numvalido);
                break;
            case 6:
                do {
                    printf("Novo status do pedido (pendente/concluido/cancelado):\n");
                    scanf("%19s", status);
                } while (!validar_status(status));

                    // Copia o status válido para a estrutura
                    strcpy(aux->xerox->status_do_pedido, status);
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    printf("Edicao do pedido concluida!\n");
    return lista;
}


void consultar_status(No *lista){ 
    if(lista == NULL){ 
        printf("lista vazia\n");
        return;
    }
    No *aux;
    int encontrado = 0;
    char status[10];
    printf("informe o status que deseja saber\n");
    scanf("%s", status);
    for(aux = lista; aux != NULL; aux = aux->proximo){ 
        if(strcmp(status, aux->xerox->status_do_pedido) == 0){ 
            encontrado=1;
            printf("pedido/pedidos com o status de %s\n", status);
            printf("Numero do Pedido: %d\nNome do Solicitante: %s\nTipo de Solicitante: %s\nNumero de Paginas: %d\nData do Pedido: %s\nValor: %.2f\n", aux->xerox->numero_do_pedido, aux->xerox->nome_do_solicitante, aux->xerox->tipo_do_solicitante, aux->xerox->quantidade_de_paginas, aux->xerox->data_do_pedido, aux->xerox->valor_total);
        }
    }
    if(encontrado == 0){ 
        printf("pedido nao encontrado\n");
    }
}

void copias_e_valor(No *lista){ 
    if(lista == NULL){ 
        printf("lista vazia\n");
        return;
    }

    No *aux;
    int copiasTotal = 0;
    float valorArrecadado = 0.0; 
    for (aux=lista; aux != NULL; aux = aux->proximo)
    {
        copiasTotal += aux->xerox->quantidade_de_paginas;
        valorArrecadado += aux->xerox->valor_total;
    }

    printf("Total de copias realizadas: %d\n", copiasTotal);
    printf("Valor arrecadado: %.2f\n", valorArrecadado);

}

void pedido_achado(No *l){ 
    if(l == NULL){ 
        printf("lista vazia\n");
        return;
    }
    
    printf("Numero do Pedido: %d\nNome do Solicitante: %s\nTipo de Solicitante: %s\nNumero de Paginas: %d\nData do Pedido: %s\nValor: %.2f\nStatus: %s\n", l->xerox->numero_do_pedido, l->xerox->nome_do_solicitante, l->xerox->tipo_do_solicitante, l->xerox->quantidade_de_paginas, l->xerox->data_do_pedido, l->xerox->valor_total, l->xerox->status_do_pedido);
}

void excluir_arquivo(int num){ 
    FILE *arquivo = fopen("pedidos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na leitura do arquivo\n");
        return;
    }

    FILE *novo_arquivo = fopen("novo_arquivo.txt", "w");
    if (novo_arquivo == NULL) {
        printf("Erro ao criar arquivo\n");
        fclose(arquivo);
        return;
    }

    No *aux = (No*) malloc(sizeof(No));
    if (aux == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(arquivo);
        fclose(novo_arquivo);
        return;
    }

    aux->xerox = (Xerox*) malloc(sizeof(Xerox));
    if (aux->xerox == NULL) {
        printf("Erro ao alocar memória para xerox\n");
        free(aux);
        fclose(arquivo);
        fclose(novo_arquivo);
        return;
    }

    int encontrado = 0;

    while (fscanf(arquivo, "Numero do pedido:%d\nNome do solicitante:%[^\n]\nTipo de solicitante:%[^\n]\nQuantidade de paginas:%d\nData do pedido:%[^\n]\nValor total:%f\nStatus do pedido:%[^\n]\n", 
            &aux->xerox->numero_do_pedido, aux->xerox->nome_do_solicitante, aux->xerox->tipo_do_solicitante, 
            &aux->xerox->quantidade_de_paginas, aux->xerox->data_do_pedido, &aux->xerox->valor_total, 
            aux->xerox->status_do_pedido) != EOF) {

        if (aux->xerox->numero_do_pedido != num) {
            fprintf(novo_arquivo, "Numero do pedido:%d\nNome do solicitante:%s\nTipo de solicitante:%s\nQuantidade de paginas:%d\nData do pedido:%s\nValor total:%.2f\nStatus do pedido:%s\n", 
                    aux->xerox->numero_do_pedido, aux->xerox->nome_do_solicitante, aux->xerox->tipo_do_solicitante, 
                    aux->xerox->quantidade_de_paginas, aux->xerox->data_do_pedido, aux->xerox->valor_total, 
                    aux->xerox->status_do_pedido);
        } else {
            encontrado = 1; // Pedido encontrado para exclusão
        }
    }

    fclose(arquivo);
    fclose(novo_arquivo);

    // Verifica se o pedido foi encontrado e excluído
    if (encontrado == 1) {
        remove("pedidos.txt");
        rename("novo_arquivo.txt", "pedidos.txt");
        printf("Pedido excluido com sucesso!\n");
    } else {
        printf("Pedido com número %d não encontrado.\n", num);
        remove("novo_arquivo.txt");
    }

    free(aux->xerox);
    free(aux);
}
