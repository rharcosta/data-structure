#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define CLEAR "CLS"

typedef struct _no no;
struct _no{
	int valor;
	no *anterior;
	no *proximo;
};

no *criarNo(int _valor) {
	no *novo;
	novo = (no *) malloc(sizeof(no));
	novo->valor = _valor;
	novo->anterior = NULL;
	novo->proximo = NULL;
	return novo;
}

void inserirPrimeiro(no **_cabeca, no *_novo) {
	*_cabeca = _novo;
}

void inserirInicio(no **_cabeca, no *_novo){
	_novo->proximo = *_cabeca;
	_novo->proximo->anterior = _novo;
	*_cabeca = _novo;
}

void inserirFim(no *_ultimo, no *_novo){
	_ultimo->proximo = _novo;
	_novo->anterior = _ultimo;
}

void inserirMeio(no *_ant, no *_novo) {
	_novo->proximo = _ant->proximo;
	_ant->proximo = _novo;
	_novo->proximo->anterior = _novo;
	_novo->anterior = _ant;
}

void inserirOrdenado(no **_cabeca, int _valor) {
    no *novo = criarNo(_valor);
    no *aux = *_cabeca;


    if(aux == NULL) {
        inserirPrimeiro(_cabeca, novo);
        printf("Valor inserido com sucesso!\n");
    }
    else if(aux -> valor > _valor) {
            inserirInicio(_cabeca, novo);
            printf("Valor inserido com sucesso!\n");
    }
    else if(aux -> valor == _valor){
            printf("Este valor ja foi inserido!\n");
            return;
    }

            else{

            while(aux -> proximo != NULL){
                if(aux -> valor == _valor){
                printf("Este valor ja foi inserido!\n");
                return;
                }
                aux = aux -> proximo;
                if (aux -> valor > _valor){
                    inserirMeio(aux -> anterior,novo);
                    printf("Valor inserido com sucesso!\n");
                    return;
                }
            }
                if(aux -> valor == _valor){
                printf("Este valor ja foi inserido!\n");
                return;
                }else{
                inserirFim(aux,novo);
                printf("Valor inserido com sucesso!\n");
                }


            }
}
void removerUnico(no **_cabeca) {
    free(*_cabeca);
    *_cabeca = NULL;
}

void removerInicio(no **_cabeca){
    no *aux = *_cabeca;
    no *prox = aux -> proximo;
    prox -> anterior = NULL;
    *_cabeca = prox;
    free(aux);
}

void removerMeio(no *meio) {
    meio -> anterior -> proximo = meio -> proximo;
    if(meio -> proximo != NULL){
        meio -> proximo -> anterior = meio -> anterior;
        free(meio);
    }
}
void remover(no **_cabeca, int _valor) {
    no *aux = *_cabeca;
    if (aux == NULL){
        printf("Esse valor nao pode ser removido, pois nao existe!\n");
        return;
    }
    else if (aux -> valor == _valor){
        if(aux -> proximo == NULL){
            removerUnico(_cabeca);
            printf("Valor removido com sucesso!\n");
        }else{
            removerInicio(_cabeca);
            printf("Valor removido com sucesso!\n");
        }return;
    }
    while(aux -> valor != _valor){
        if(aux -> proximo != NULL)
            aux = aux -> proximo;
        else {
            printf("Valor nao encontrado!\n");
            return;
        }
    }
    removerMeio(aux);
    printf("Valor removido com sucesso!\n");
}

void listar(no *_cabeca) {
    while(_cabeca != NULL) {
        printf("%d - ", _cabeca->valor);
        _cabeca = _cabeca->proximo;
    }
    printf("\n");

}


void imprimeMenu() {
    printf("================================================================\n");
    printf("|       Programa para lista duplamente encadeada ordenada      |\n");
    printf("================================================================\n");
    printf("| Operacoes:                                                   |\n");
    printf("| 1) Incluir elemento                                          |\n");
    printf("| 2) Remover elemento                                          |\n");
    printf("| 3) Listar elementos                                          |\n");
    printf("| 4) Sair                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("Pressione a opcao desejada: ");
}



int main() {
	no *cabeca = NULL;
    int ok = 1;
    char opcao = '0';
	int valor;
	char palavra[20];
    while(ok) {
        system(CLEAR);
        imprimeMenu();
        opcao = getch();
        switch(opcao) {
            case '1':   printf("\nDigite um numero a inserir: ");
                        gets(palavra);
                        valor = atoi(palavra);
						inserirOrdenado(&cabeca, valor);
						getch();
						break;
            case '2': 	printf("\nDigite um numero a remover: ");
                        gets(palavra);
                        valor = atoi(palavra);
						remover(&cabeca, valor);
						getch();
						break;
            case '3': 	listar(cabeca);
						getch();
						break;
            case '4': 	ok = 0;
						break;
            default: 	printf("\nOpcao invalida!\n");
						getch();
						break;
        }
    }
    printf("\n");
    return (EXIT_SUCCESS);
}
