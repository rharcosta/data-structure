#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIVISOR 1029
#define FATOR 127
#define TABLESIZE 4583

int hash(int m){
    return ((m / DIVISOR) * FATOR + m) % TABLESIZE;
}

int main(){
    int valores[] = {654321, 123456, 454545, 4583, 45830, 45904, 12700, 127, 1270, 1559};

    for(int i = 0; i < sizeof(valores)/sizeof(int); i++){
        int hashObtido = hash(valores[i]);
        printf("%d -> Hash: %d\n", valores[i], hashObtido);
    }
}
