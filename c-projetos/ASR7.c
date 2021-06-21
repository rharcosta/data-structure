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
    printf("| 3) Bubble Sort                                               |\n");
    printf("| 4) Quick Sort                                                |\n");
    printf("| 5) Merge Sort                                                |\n");
    printf("| 6) Imprimir array original                                   |\n");
    printf("| 7) Imprimir array ordenado                                   |\n");
    printf("| 8) Sair                                                      |\n");
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

void bubbleSort(int *array, int tam) {
    int i, j, aux;
    for(j = tam - 1; j > 0; j--) {
        for(i = 0; i < j; i++) {
            if(array[i] > array[i + 1]) {
                aux = array[i];
                array[i] = array[i + 1];
                array[i + 1] = aux;
            }
        }
    }
}

void quickSort(int *array, int p, int u) {
    int i, j, pivo, aux;
    i = p;
    j = u;
    pivo= array[(i + j)/2];
    do{
        while(array[i] < pivo && i < u) i++;
        while(array[j] > pivo && j > p) j--;
        if(i <= j){
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
            i++;
            j--;
        }
    }
            while(i <= j);
            if(p < j) quickSort(array, p, j);
            if(i < u) quickSort(array, i, u);
}

void merge(int *ordenado, int *temporario, int esquerda, int meio, int direita) {
    int i, esq_fim, tam, tmp_pos;
    esq_fim = meio - 1;
    tmp_pos = esquerda;
    tam = direita - esquerda + 1;
    while ((esquerda <= esq_fim) && (meio <= direita)) {
        if (ordenado[esquerda] <= ordenado[meio]) {
            temporario[tmp_pos] = ordenado[esquerda];
            tmp_pos++;
            esquerda++;
        }
        else {
            temporario[tmp_pos] = ordenado[meio];
            tmp_pos++;
            meio++;
        }
    }
    if (esquerda <= esq_fim) {
        memcpy(&temporario[tmp_pos], &ordenado[esquerda], (esq_fim - esquerda + 1)*sizeof(int));
    }
    if (meio <= direita) {
        memcpy(&temporario[tmp_pos], &ordenado[meio], (direita - meio + 1)*sizeof(int));
    }
    memcpy(&ordenado[direita - tam + 1], &temporario[direita - tam + 1], tam*sizeof(int));
}

void mergesort(int *ordenado, int *temporario, int esquerda, int direita) {
    int meio;
    if (direita > esquerda) {
        meio = (direita + esquerda) / 2;
        mergesort(ordenado, temporario, esquerda, meio);
        mergesort(ordenado, temporario, meio+1, direita);
        merge(ordenado, temporario, esquerda, meio+1, direita);
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

    while(opcao != '8'){
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

        //BUBBLESORT
        case '3': memcpy(ordenado, original, sizeof(int) * tam);
                  t1 = current_timestamp();
                  bubbleSort(ordenado, tam);
                  t2 = current_timestamp();
                  printf("\nDuracao em microssegundos: %lld\n", t2-t1);
                  getchar();
                  getchar();
                  break;

        //QUICKSORT
        case '4': memcpy(ordenado, original, sizeof(int) * tam);
                  t1 = current_timestamp();
                  quickSort(ordenado, 0, tam-1);
                  t2 = current_timestamp();
                  printf("\nDuracao em microssegundos: %lld\n", t2-t1);
                  getchar();
                  getchar();
                  break;

        //MERGESORT
        case '5': memcpy(ordenado, original, sizeof(int) * tam);
                  t1 = current_timestamp();
                  int *temporario;
                  temporario = (int *)malloc(sizeof(int) * tam);
                  mergesort(ordenado, temporario, 0, tam-1);
                  t2 = current_timestamp();
                  printf("\nDuracao em microssegundos: %lld\n", t2-t1);
                  getchar();
                  getchar();
                  break;


        //IMPRIMINDO O ARRAY ORIGINAL
        case '6': imprimirArray(original, tam);
                  getchar();
                  getchar();
                  break;

        //IMPRIMINDO O ARRAY ORDENADO
        case '7': imprimirArray(ordenado, tam);
                  getchar();
                  getchar();
                  break;

        //SAINDO DO PGM
        case '8': printf("\nSaindo do programa...\n");
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

