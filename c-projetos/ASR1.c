#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>  //Não muito recomendado

#define MAX_REG 10
#define MAX_LENGTH 1024
#define CLEAR "CLS" //Limpa  a tela do Windows
//No linux "CLEAR"

//Estrutura Cliente
typedef struct _cliente {
    //Campos da estrutura cliente
    int codigo;
    char nome[50];
    char documento[20];
} cliente;

void imprimeMenu() {
    printf("================================================================\n");
    printf("|            Programa para cadastro de clientes                |\n");
    printf("================================================================\n");
    printf("| Operacoes:                                                   |\n");
    printf("| 1) Incluir cliente                                           |\n");
    printf("| 2) Remover cliente                                           |\n");
    printf("| 3) Listar clientes                                           |\n");
    printf("| 4) Sair                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("Pressione a opcao desejada: ");
}

void incluirCliente(cliente **p_cliente, int *count){
    char aux[50];
    char aux2[20];
    int contador = *count;
    cliente *clienteNovo;

    //Verificação para ver se a lista está cheia
    if(contador < MAX_REG){

    //Incluir
    clienteNovo = malloc(sizeof(cliente));
    printf("\nEntre com o codigo: ");
    gets(aux);
    clienteNovo -> codigo = atoi(aux);

    printf("\nEntre com o nome: ");
    gets(aux);
    strcpy(clienteNovo -> nome, aux);

    printf("\nEntre com o documento: ");
    gets(aux2);
    strcpy(clienteNovo -> documento, aux2);


    for(int i = 0; i <= contador; i++){
        if(i == contador){
            p_cliente[contador] = clienteNovo;
            ++contador;
            printf("Cliente cadastrado!");
            break;
        }
        else if(p_cliente[i]->codigo > clienteNovo->codigo){
            for(int j = contador - 1; j >= i; j--){
                p_cliente[j+1] = p_cliente[j];
            }
            p_cliente[i] = clienteNovo;
            ++contador;
            break;
        }
        else if(p_cliente[i]->codigo == clienteNovo -> codigo){
            printf("\nJa existe um codigo cadastrado igual ao inserido!");
            break;
        }
      }


    } else {
    //Arranjo cheio
    printf("\nLista cheia!");
    } *count = contador;
}

void removerCliente(cliente **p_cliente, int *count){
    int contador = *count;
    int cod;
    int achou = 0;
    char aux[20];
    cliente *removerCliente;

    if(contador != NULL){
    printf("\nEntre com o codigo do cliente a ser removido: ");
    gets(aux);
    cod = atoi(aux);


    for(int i = 0; i < contador; i++){
        removerCliente = p_cliente[i];
        if(removerCliente->codigo == cod){
            achou = 1;
            break;
        }
    }} else printf("\nLista Vazia");
    if(contador != NULL){
    if(achou){
        --contador;
        for(int i = 0; i < contador; ++i){
            p_cliente[i] = p_cliente[i+1];
        }
        p_cliente[contador] = NULL;
        printf("\nCliente removido!");
    }
    else{
        printf("\nNenhum cliente foi encontrado com o codigo (%d).", cod);
    }
    }
    *count = contador;

}

void listarClientes(cliente **p_cliente, int *count){

    //Verificando se a lista esta vazia ou nao
    cliente *listarCliente;
    int contador = *count;
    if(contador != NULL){
    for(int i = 0; i < contador; ++i, ++listarCliente){
        listarCliente = p_cliente[i];
        printf("\nCodigo: %d | Nome: %s | Documento: %s",
               listarCliente->codigo,
               listarCliente->nome,
               listarCliente->documento);
    }
    }else{
        printf("\nA lista esta vazia!");
    }

}

int main(int argc, char** argv){
    cliente *clientes[MAX_REG];
    cliente **p_cliente;
    p_cliente = &clientes[0];
    int ok, count=0;
    char opcao = '0';
    ok = 1;
    while(ok) {
        system(CLEAR);
        imprimeMenu();
        opcao = getch();
        switch(opcao) {
            case '1': incluirCliente(p_cliente, &count); getch(); break;
            case '2': removerCliente(p_cliente, &count); getch(); break;
            case '3': listarClientes(p_cliente, &count); getch(); break;
            case '4': ok = 0; break;
            default: printf("\nOpcao invalida!\n"); getch(); break;
        }
    }
    printf("\n");
    return (EXIT_SUCCESS);
}
