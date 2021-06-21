//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define CLEAR "CLS"

//METODO PARA CALCULAR TEMPO
unsigned long long current_timestamp() {
    struct timeval tv;
    unsigned long long tim;
    gettimeofday(&tv, NULL);
    tim = 1000000 * tv.tv_sec + tv.tv_usec;
    return tim;
}

//CRIANDO UM ARRAY(PONTEIRO) COM TAMANHO TAM
int *criarArray(int tam) {
    int *array = (int *) malloc(sizeof(int) * tam);
    for (int i = 0; i < tam; i++) {
        array[i] = i + 1;
    }
    return array;
}

//DESORGANIZANDO O ARRAY
int *desorganizar(int *array, int tam) {
    time_t tim;
    srand((unsigned) time(&tim));
    for (int i = 0; i < tam; i++) {
        int rand_pos = (int)(((double)rand()/RAND_MAX) * tam);
        int t = array[rand_pos];
        array[rand_pos] = array[i];
        array[i] = t;
    }
    return array;
}

//IMPRIMINDO O ARRAY
void imprimirArray(int *array, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", array[i]);
    }
}

//MENU
void imprimeMenu() {
    printf("================================================================\n");
    printf("|     Tempo de execucao de diferentes metodos de ordenacao     |\n");
    printf("================================================================\n");
    printf("| Operacoes:                                                   |\n");
    printf("| 1) Insertion Sort                                            |\n");
    printf("| 2) Shell Sort                                                |\n");
    printf("| 3) Imprimir array original                                   |\n");
    printf("| 4) Imprimir array ordenado                                   |\n");
    printf("| 5) Sair                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("Pressione a opcao desejada: ");
}

void insertionSort(int *array, int tam) {

   int i, k, aux;
    for(k = 1; k < tam; k++){
        aux = array[k];
        for(i = k - 1; i >= 0 && aux < array[i]; i--)
            array[i + 1] = array[i];
        array[i + 1] = aux;
    }
}

void shellSort(int *array, int tam) {

   int gap, j, k, aux;
    for(gap = tam / 2; gap >= 1; gap = gap / 2){
        for(j = gap; j < tam; j++){
            aux = array[j];
        for(k = j -gap; k >= 0 && aux < array[k]; k-=gap){
            array[k + gap] = array[k];
        }
            array[k + gap] = aux;
        }
    }
}

int main() {
    int *original, *ordenado, tam;
    char opcao = '0';
    unsigned long long t1, t2;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    original = desorganizar(criarArray(tam), tam);
    ordenado = (int *) malloc(sizeof(int) * tam);
    memcpy(ordenado, original, sizeof(int) * tam);
    getchar();

    while(opcao != '5'){
    system("CLS");
    imprimeMenu();
    opcao = getchar();
    switch(opcao){

        //INSERTIONSORT
        case '1': memcpy(ordenado, original, sizeof(int) * tam);
                  t1 = current_timestamp();
                  insertionSort(ordenado, tam);
                  t2 = current_timestamp();
                  printf("\nDuracao em microssegundos: %lld\n", t2-t1);
                  getchar();
                  getchar();
                  break;

        //SHELLSORT
        case '2': memcpy(ordenado, original, sizeof(int) * tam);
                  t1 = current_timestamp();
                  shellSort(ordenado, tam);
                  t2 = current_timestamp();
                  printf("\nDuracao em microssegundos: %lld\n", t2-t1);
                  getchar();
                  getchar();
                  break;

        //IMPRIMINDO O ARRAY ORIGINAL
        case '3': imprimirArray(original, tam);
                  getchar();
                  getchar();
                  break;

        //IMPRIMINDO O ARRAY ORDENADO
        case '4': imprimirArray(ordenado, tam);
                  getchar();
                  getchar();
                  break;

        //SAINDO DO PGM
        case '5': printf("\nSaindo do programa...\n");
                  break;

        //NENHUMA OPCAO ANTERIOR
        default:  printf("\nOpcao invalida!\n");
                  getchar();
                  getchar();
                  break;
        }
    }
    return (EXIT_SUCCESS);

}
