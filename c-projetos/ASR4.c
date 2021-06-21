//DECLARACAO DAS BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ESTRUTURA SETOR
typedef struct _set setor;
struct _set {
    char nome[30];
    int cod;
    setor *prox;
};

//ESTRUTURA FUNCIONARIO
typedef struct _func func;
struct _func {
    char nome[30];
    int doc;
    func *prox;
    setor *setor;
};

//ESTRUTURA CABECA SETOR
typedef struct _cabset cabset;
struct _cabset{
    int qtd;
    setor *ini;
};

//ESTRUTURA CABECA FUNCIONARIO
typedef struct cabfunc cabfunc;
struct cabfunc{
    int qtd;
    func *ini;
};

setor *criarNoSetor(char *nome, int cod) {
    setor *novo;
    novo = (setor *) malloc(sizeof(setor));
    novo -> cod = cod;
    strcpy(novo -> nome, nome);
    novo -> prox = NULL;
    return novo;
}

void inserirPrimeiroSetor(cabset *cabeca, setor *novo) {
    cabeca -> ini = novo;
    cabeca -> qtd = 1;
}

void inserirInicioSetor(cabset *cabeca, setor *novo){
    novo -> prox = cabeca -> ini;
    cabeca -> ini = novo;
    cabeca -> qtd++;
}

void inserirMeioSetor(cabset *cabeca, setor *ant, setor *novo) {
    novo -> prox = ant -> prox;
    ant -> prox = novo;
    cabeca -> qtd++;
}

void inserirFimSetor(cabset *cabeca, setor *ultimo, setor *novo){
    ultimo -> prox = novo;
    cabeca -> qtd++;
}

func *criarNoFuncionario(char *nome, int doc) {
    func *novo;
    novo = (func *) malloc(sizeof(func));
    novo -> doc = doc;
    strcpy(novo -> nome, nome);
    novo -> prox = NULL;
    novo->setor = NULL;
    return novo;
}

void inserirPrimeiroFuncionario(cabfunc *cabeca, func *novo) {
    cabeca -> ini = novo;
    cabeca -> qtd = 1;
}

void inserirInicioFuncionario(cabfunc *cabeca, func *novo){
    novo -> prox = cabeca -> ini;
    cabeca -> ini = novo;
    cabeca -> qtd++;
}

void inserirMeioFuncionario(cabfunc *cabeca, func *ant, func *novo) {
    novo -> prox = ant -> prox;
    ant -> prox = novo;
    cabeca -> qtd++;
}

void inserirFimFuncionario(cabfunc *cabeca, func *ultimo, func *novo){
    ultimo -> prox = novo;
    cabeca -> qtd++;
}

void inserirOrdenadoSetor(cabset *cabeca, int cod, char *nome) {
//CRIACAO DO PONTEIRO AUX, ANT
setor *auxSetor, *antSetor;

    //PONTEIRO NOVOSETOR VAI RECEBER OS PARAMETROS DO CRIARNOSETOR
    setor *novoSetor = criarNoSetor(nome, cod);

    auxSetor = cabeca -> ini; //AUX VAI RECEBER O INICIO DA CABECA
    antSetor = auxSetor;      //ANT VAI RECEBER O AUX

    while(auxSetor != NULL) {       //LOOP PARA PERCORRER OS DADOS ENQUANTO NAO NULO
        //SE O CODIGO QUE MEU AUX APONTA FOR MAIOR QUE O CODIGO QUE EU QUERO INSERIR, ELE SAIRA DO WHILE
        if(auxSetor -> cod > cod){
            break;
        //SE O CODIGO QUE MEU AUX APONTA FOR IGUAL AO CODIGO QUE EU QUERO INSERIR, ELE EXIBIRA UMA MENSAGEM
        }else if(auxSetor -> cod == cod) {
            printf("Ja existe um setor com esse codigo!\n");
            return;
        }
        antSetor = auxSetor;           //O ANT RECEBE O AUX
        auxSetor = auxSetor -> prox;   //O AUX RECEBE O PROX
    }


    //SE O AUX FOR NULO
    if(auxSetor == NULL){

        //SE ANT FOR NULO, ELES SAO IGUAIS, LOGO A LISTA ESTA VAZIA
        if(auxSetor == antSetor)
        inserirPrimeiroSetor(cabeca, novoSetor);

        //SE O ANT NAO FOR NULO, ELES NAO FOREM IGUAIS, LOGO A LISTA ACABOU
        else
        inserirFimSetor(cabeca, antSetor, novoSetor);

    //SE O AUX NAO FOR NULO
    }else{

        //SE O AUX FOR IGUAL AO ANT E ELES NAO FOREM NULOS, ELE INSERE NO INICIO
        if(auxSetor == antSetor)
        inserirInicioSetor(cabeca, novoSetor);


        else
        //SE ELES NAO FOREM IGUAIS E NAO FOREM NULOS, ELE INSERE NO MEIO
        inserirMeioSetor(cabeca, antSetor, novoSetor);
    }   printf("Setor inserido com sucesso!\n");

}

void inserirOrdenadoFuncionarioEmSetor(cabset *cabecaSetor, cabfunc *cabecaFunc, int cod, char *nome, int doc) {
    //PONTEIRO NOVOFUNC VAI RECEBER OS PARAMETROS DO CRIARNOFUNCIONARIO
    func *novoFunc = criarNoFuncionario(nome,doc);
    //O AUX DO SETOR VAI RECEBER O INICIO DA CABECA DO SETOR
    setor *auxSetor = cabecaSetor -> ini;

    while(auxSetor != NULL){
        if(auxSetor -> cod == cod){ //VERIFICANDO SE O CODIGO QUE O AUXILIAR APONTA E IGUAL AO CODIGO QUE QUERO INSERIR
         novoFunc -> setor = auxSetor;   //O SETOR QUE O NOVO FUNCIONARIO APONTA VAI RECEBER O AUX
         break;
        }else{
        //SE ELES NAO FOREM IGUAIS, O AUX VAI APONTAR PARA O PROX
        auxSetor = auxSetor -> prox;
        }
    }

    if(novoFunc -> setor == NULL){ //SE O SETOR DO FUNC NAO EXISTE
        printf("Setor inexistente!\n");
        return;
    }

    // COMEÇO DA ORDENAÇÃO - MESMA COISA QUE O SETOR
    func *auxFunc, *antFunc;
    auxFunc = cabecaFunc -> ini;
    antFunc = auxFunc;

    while(auxFunc != NULL) {
        if(auxFunc -> doc > doc){
            break;
        }else if(auxFunc -> doc == doc) {
            printf("Ja existe um funcionario com esse documento!\n");
            return;
        }
        antFunc = auxFunc;
        auxFunc = auxFunc -> prox;
    }

    if(auxFunc == NULL){
        if(auxFunc == antFunc)
        inserirPrimeiroFuncionario(cabecaFunc, novoFunc);
        else
        inserirFimFuncionario(cabecaFunc, antFunc, novoFunc);
    }else{
        if(auxFunc == antFunc)
        inserirInicioFuncionario(cabecaFunc, novoFunc);
        else
        inserirMeioFuncionario(cabecaFunc, antFunc, novoFunc);
    }
        printf("Funcionario inserido com sucesso!\n");

}

void removerFuncionario(cabfunc *cabeca, int doc) {

    //MESMA COISA QUE O REMOVER SETOR
    func *auxFunc, *antFunc;
    auxFunc = cabeca -> ini;
    antFunc = auxFunc;

    while(auxFunc != NULL) {
        if(auxFunc -> doc == doc){
            break;
        }
        antFunc = auxFunc;
        auxFunc = auxFunc -> prox;

    }
    if (auxFunc == NULL){
        printf("Funcionario inexistente!\n");
    }else{
        if(auxFunc == antFunc)
            cabeca -> ini = auxFunc -> prox;
        else
            antFunc -> prox = auxFunc -> prox;
    printf("Funcionario %s removido!\n", auxFunc -> nome);
    free(auxFunc);
    cabeca -> qtd--;
    }

}

void removerSetorComFuncionarios(cabset *cabecaSetor, cabfunc *cabecaFunc, int cod) {

     //CRIACAO DE UM AUX DA ESTRUTURA FUNC
    func *auxFunc;
     //INICIALIZANDO MEU AUXFUNC PARA RECEBER O INICIO DA CABECA
    auxFunc = cabecaFunc -> ini;

    //MESMA COISA PARA O SETOR
    setor *auxSetor, *antSetor;
    auxSetor = cabecaSetor -> ini;  //AUXSETOR VAI RECEBER O INICIO DA CABECA
    antSetor = auxSetor;            //ANTSETOR VAI RECEBER O AUXSETOR

    //ENQUANTO MEU AUXSETOR FOR DIFERENTE DE NULO, ELE VAI PERCORRER A LISTA ATE ENCONTRAR UM CODIGO IGUAL
    while(auxSetor != NULL) {
        if(auxSetor -> cod == cod){
            break;
        }
        antSetor = auxSetor;
        auxSetor = auxSetor -> prox;

    }

    while(auxFunc != NULL){
        if(auxFunc -> setor == auxSetor)
            removerFuncionario(cabecaFunc, auxFunc -> doc);
        auxFunc = auxFunc -> prox;
    }

    if (auxSetor == NULL){
        printf("Setor inexistente!\n");
    }else{
        if(auxSetor == antSetor)
            cabecaSetor-> ini = auxSetor -> prox;
        else
            antSetor -> prox = auxSetor -> prox;
    printf("Setor %s removido!\n", auxSetor -> nome);
    free(auxSetor);
    cabecaSetor -> qtd--;
    }
}

void listar(cabfunc *cabeca) {

    //SE A QTD DA CABECA FOR 0, NAO EXISTE FUNCIONARIO PARA LISTAR
    if(cabeca -> qtd == 0){
        printf("Nao existem funcionarios para a listagem!\n");
        return;
    }

    func *auxFunc = cabeca -> ini;

    //ENQUANTO O AUXFUNC FOR DIFERENTE DE NULO, ELE LISTARA OS FUNCIONARIOS E APONTARA PARA O PROXIMO DA LISTA
    while(auxFunc != NULL){
        printf("Nome: %s\t\t Documento: %d\t\t Setor: %s\n", auxFunc -> nome, auxFunc -> doc, auxFunc->setor->nome);
        auxFunc = auxFunc -> prox;
    }
}

void imprimeMenu() {
    printf("================================================================\n");
    printf("| Programa para operacao de multilista                         |\n");
    printf("================================================================\n");
    printf("| Operacoes:                                                   |\n");
    printf("| 1) Incluir setor                                             |\n");
    printf("| 2) Incluir funcionario em setor                              |\n");
    printf("| 3) Remover funcionario                                       |\n");
    printf("| 4) Remover setor e seus funcionarios                         |\n");
    printf("| 5) Listar funcionarios e seus setores                        |\n");
    printf("| 6) Sair                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("Entre a opcao desejada: ");
}

int main(int argc, char** argv) {
    char opcao = '0';
    char nome[30];
    int cod;
    int doc;

    cabset *cabecaSetor;
    cabfunc *cabecaFunc;
    cabecaSetor = (cabset *) malloc(sizeof(cabset));
    cabecaSetor -> qtd = 0;
    cabecaSetor -> ini = NULL;
    cabecaFunc = (cabfunc *) malloc(sizeof(cabfunc));
    cabecaFunc -> qtd = 0;
    cabecaFunc -> ini = NULL;

    while(opcao != '6') {
        system("CLS");
        imprimeMenu();
        opcao = getchar();
        printf("\nQuantidade atual na lista de Setores: %d\n", cabecaSetor->qtd);
        printf("Quantidade atual na lista de Funcionarios: %d\n\n", cabecaFunc->qtd);
        switch(opcao) {

            //INCLUIR SETOR
            case '1':   printf("Entre com o codigo do setor: ");
                        scanf("%d", &cod);
                        printf("Entre com o nome do setor: ");
                        scanf("%s", nome);
                        inserirOrdenadoSetor(cabecaSetor, cod, nome);
                        getchar();
                        getchar();
                        break;

            //INCLUIR FUNCIONARIO NO SETOR
            case '2':   if (cabecaSetor -> qtd == 0){
                            printf("Nao ha setores para incluir o funcionario!\n");
                            getchar();
                            getchar();
                            break;
                        }
                        printf("Entre com o nome do funcionario: ");
                        scanf("%s", nome);
                        printf("Entre com o documento do funcionario: ");
                        scanf("%d", &doc);
                        printf("Entre com o codigo do setor do funcionario: ");
                        scanf("%d", &cod);
                        inserirOrdenadoFuncionarioEmSetor(cabecaSetor, cabecaFunc, cod, nome, doc);
                        getchar();
                        getchar();
                        break;

            //REMOVER FUNCIONARIOS
            case '3':   if (cabecaFunc -> qtd == 0){
                            printf("Nao ha funcionarios para a remocao!\n");
                            getchar();
                            getchar();
                            break;
                        }
                        printf("Digite o documento do funcionario a ser removido: ");
                        scanf("%d", &doc);
                        removerFuncionario(cabecaFunc, doc);
                        getchar();
                        getchar();
                        break;

            //REMOVER SETOR COM FUNCIONARIOS
            case '4':   if (cabecaSetor -> qtd == 0){
                            printf("Nao ha setores para a remocao!\n");
                            getchar();
                            getchar();
                            break;
                        }
                        printf("Digite o codigo do setor a ser removido: ");
                        scanf("%d", &cod);
                        removerSetorComFuncionarios(cabecaSetor, cabecaFunc, cod);
                        getchar();
                        getchar();
                        break;

            //LISTAGEM
            case '5':   listar(cabecaFunc);
                        getchar();
                        getchar();
                        break;

            //SAIR
            case '6':   printf("\nSaindo do programa...\n");
                        break;

            //NENHUMA OPCAO ANTERIOR
            default:    printf("\nOpcao invalida!\n");
                        getchar();
                        getchar();
                        break;
        }
    }
    return (EXIT_SUCCESS);
}
