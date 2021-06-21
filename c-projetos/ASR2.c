#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _no no;
struct _no{
    int valor;
    no *proximo;
};

no *criarNo(int _valor) {
    no *novo;
    novo = (no *) malloc(sizeof(no));
    novo->valor = _valor;
    novo->proximo = NULL;
    return novo;
}

void removerUnico(no **_cabeca) {
    free(*_cabeca);
    *_cabeca = NULL;
}

void removerInicio(no **_cabeca){
no *aux = *_cabeca;
no *prox = aux -> proximo;
*_cabeca = prox;
free(aux);
}

void removerMeio(no *ant) {
    no *aux = ant->proximo;
    no *prox = aux->proximo;
    ant->proximo = prox;
    free(aux);
}

void inserirPrimeiro(no **_cabeca, no *_novo) {
	*_cabeca = _novo;
}

void inserirInicio(no **_cabeca, no *_novo){
	_novo->proximo = *_cabeca;
    *_cabeca = _novo;
}

void inserirFim(no *_ultimo, no *_novo){
	_ultimo->proximo = _novo;
}

void inserirMeio(no *_ant, no *_novo) {
	_novo->proximo = _ant->proximo;
    _ant->proximo = _novo;
}

void inserirOrdenado(no **_cabeca, int _valor) {
    no *novo = criarNo(_valor);
    no *aux = *_cabeca;
    no *ant;

    //Inserir Primeiro
    if(aux == NULL) { //Nó vazio
        inserirPrimeiro(_cabeca, novo);
        printf("Valor inserido com sucesso!\n");
    }else{

        //Inserir no inicio
        if(aux -> valor > _valor) {
            inserirInicio(_cabeca, novo);
            printf("Valor inserido com sucesso!\n");
        }else{

            //Vai ficar no while ate encontrar o próximo elemento nulo do nó
            while(aux -> proximo != NULL){
                ant = aux;
                aux = aux -> proximo;
                //Se o valor do aux for maior que o valor que quero inserir
                //o valor será inserido no meio
                if (aux -> valor > _valor){
                    inserirMeio(ant,novo);
                    aux = novo;
                    printf("Valor inserido com sucesso!\n");
                    break;
                }
            }

          //Se o proximo valor do nó for nulo
        } if (aux-> proximo == NULL){
                if(aux -> valor == _valor){
                printf("Este valor ja foi inserido!\n");
                }else{
                //Inserir no fim
                inserirFim(aux,novo);
                printf("Valor inserido com sucesso!\n");
                }

            }
    }
}

void listar(no *ini) {
    while(ini != NULL) {
        printf("%d - ", ini->valor);
        ini = ini->proximo;
    }
    printf("\n");

}

void remover(no **_cabeca, int _valor) {
    no *ant;
    no *aux = *_cabeca;
    if (aux == NULL){
            printf("Esse valor nao pode ser removido, pois nao existe!\n");
        return;
    }
    if (aux -> valor == _valor){
        if(aux -> proximo == NULL){
            removerUnico(_cabeca);
            printf("Valor removido com sucesso!\n");
        }else{
            removerInicio(_cabeca);
            printf("Valor removido com sucesso!\n");
        }return;
    }
    while(aux -> valor != _valor){
        ant = aux;
        if(aux -> proximo != NULL)
            aux = aux -> proximo;
        else {
            printf("Valor nao encontrado!\n");
            return;
        }


    }
    removerMeio(ant);
    printf("Valor removido com sucesso!\n");
}

void imprimeMenu() {
    printf("================================================================\n");
    printf("| Programa para operacao de lista simplesmente encadeada       |\n");
    printf("================================================================\n");
    printf("| Operacoes:                                                   |\n");
    printf("| 1) Incluir elemento                                          |\n");
    printf("| 2) Remover elemento                                          |\n");
    printf("| 3) Listar elementos                                          |\n");
    printf("| 4) Sair                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("Entre a opcao desejada: ");
}

int main(int argc, char** argv) {
    no *cabeca;
    cabeca = NULL;
    int valor;
    char opcao = '0';
    while(opcao != '4') {
        system("CLS");
        imprimeMenu();
        opcao = getchar();
        switch(opcao) {
            case '1':   printf("Entre com o valor a inserir: ");
                        scanf("%d", &valor);
                        inserirOrdenado(&cabeca, valor);
                        getchar();
                        getchar();
                        break;
            case '2':   printf("Entre com o valor a remover: ");
                        scanf("%d", &valor);
                        remover(&cabeca, valor);
                        getchar();
                        getchar();
                        break;
            case '3':   listar(cabeca);
                        getchar();
                        getchar();
                        break;
            case '4':   printf("Saindo do programa...\n");
                        break;
            default:    printf("\nOpcao invalida!\n");
                        getchar();
                        getchar();
                        break;
        }
    }
    return (EXIT_SUCCESS);
}
