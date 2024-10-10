#ifndef XEROX_H
#define XEROX_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

typedef struct xerox Xerox;

typedef struct no No;

// Funções para validação
int validar_nome(char* nome);
int validar_tipo_solicitante(char* tipo);
int validar_opcao(char *entrada);
int validar_status(char* status);
int validar_data(char* data);
int validar_numeros(char *entrada2);
int validar_valor_total(char *entrada);

// Função para preencher os dados do pedido
void preencher(Xerox* novo);

// Função para adicionar um novo pedido à lista
No* adicionar_pedido(No *lista);

// Funções para salvar e atualizar pedidos no arquivo
void salvar_pedidos(No *lista);
void atualizar_arquivo(No *lista);

// Função para excluir um pedido da lista
No *excluir(No *lista, int num);
void excluir_arquivo(int num);

// Função para listar os pedidos armazenados no arquivo
void listar();

// Função para buscar um pedido específico na lista
No *buscar(No *lista, int numero);

// Função para editar um pedido da lista
No* editar_pedido(No *lista, int numero);

// Função para consultar pedidos pelo status
void consultar_status(No *lista);

// Função para calcular total de cópias e valor arrecadado
void copias_e_valor(No *lista);

// Função para exibir um pedido encontrado
void pedido_achado(No *l);

#endif