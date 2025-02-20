#include <stdio.h>                          //EDUARDO OSMARI BORTOLOTTO

void SaidaBits(int tamanho, int *vetor) {
    for (int i = 0; i < tamanho; i++) {
        if (*(vetor+i) == 9) { //Verificando se o bit tem o valor 9 para informar a saída
            printf("\nF\n"); //Saída "F" correspondendo a uma falha.
            return;
        }
    }
    
    printf("\nS\n"); //Saída "S", todos os bits lidos com sucesso
    return;
}

void LerBits(int tamanho, int *vetor) { 
    int entrada;
    
    int cont = 0; //Contador para realizar 8 iterações
    while (cont < tamanho) {
        scanf("%d", &entrada); //Entrada dos bits
        
        if (entrada != 1 && entrada != 0 && entrada != 9) { //Verificar se o valor de entrada é 0, 1 ou 9
            printf("Valor inválido digite novamente.\n");
        } else { 
            *(vetor + cont++) = entrada; //Valor de entrada atribuido ao vetor, contador incrementado
        }
    }

    return;
}

int main() {
    int tamanho = 8; //Tamanho do vetor
    int vetor[tamanho]; //Vetor para guardar 1 byte(sequência de 8 bits)

    LerBits(tamanho, vetor); //Entrada
    SaidaBits(tamanho, vetor); //Saída

    return 0;
}
