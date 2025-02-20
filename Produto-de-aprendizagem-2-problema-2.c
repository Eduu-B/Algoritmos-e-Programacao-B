#include <stdio.h>             
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

  //EDUARDO OSMARI BORTOLOTTO

void informar_elementos(int *matriz, int tamanho) {

  printf("\n");
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      printf("Digite um valor na matriz linha %d coluna %d : ", i+1, j+1); //Informar elementos
      scanf("%d", matriz + (i * tamanho + j)); // Leitura usando aritmética de ponteiro
      printf("\n");
    }
  }
}

void gerar_elementos(int *matriz, int tamanho) {
  srand(time(0)); //Função srand

  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      *(matriz + (i * tamanho + j)) = rand() % 100; //Geração de números aleatórios
    }
  }
}

void Menu1(int *matriz, int tamanho) {  
  int opcao;

  while(1) { //Loop true
    printf("\nSelecione uma opção:\n1 - Informar os elementos da Matriz\n2 - Gerar os elementos da Matriz\n");
    scanf("%d", &opcao);

    switch(opcao) {
    case 1:
      informar_elementos(matriz, tamanho); //O usuário informa os valores
      return;
    case 2:
      gerar_elementos(matriz, tamanho); //O programa gera os valores
      return;
    default:
      printf("Escolha uma opção válida!\n"); //Caso não tenha sido digitado uma opção válida realiza outra iteração
    }
  }
}

int matriz_simetrica(int *matriz, int tamanho) {
  int elemento1, elemento2;

  //Verificar simetria
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      elemento1 = *(matriz + i * tamanho + j);
      elemento2 = *(matriz + j * tamanho + i);   //Atribuindo valor da posição [i][j] a elemento1 e [j][i] a elemento2

      if (elemento1 != elemento2) { //Verificando se elemento 1 é diferente de elemento 2
        return 0;
      }
    }                      //retorna 0 ou 1
  }

  return 1;
}

int matriz_diagonal(int *matriz, int tamanho) {
  int elemento;

  //Verificar se é diagonal
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      if (i != j) { //Excluindo a diagonal principal
        elemento = *(matriz + i * tamanho + j); //Atribuindo valor da posição [i][j] a elemento
        if (elemento != 0) { //Verificando se elemento é diferente de 0
          return 0;
        }
      }
    }                   //retorna 0 ou 1
  }

  return 1;
}

int matriz_triangular_superior(int *matriz, int tamanho) {
  int elemento;

  //Verificar se é triangular superior
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      if (i > j) { //Excluindo elementos acima da diagonal principal
        elemento = *(matriz + i * tamanho + j); //Atribuindo valor da posição [i][j] a elemento
        if (elemento != 0) { //Verificando se elemento é diferente de 0
          return 0;
        }
      }
    }                   //retorna 0 ou 1
  }

  return 1;
}

int matriz_triangular_inferior(int *matriz, int tamanho) {
  int elemento;

  //Verificar se é triangular inferior
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      if (i < j) { //Excluindo elementos abaixo da diagonal principal
        elemento = *(matriz + i * tamanho + j); //Atribuindo valor da posição [i][j] a elemento
        if (elemento != 0) {  //Verificando se elemento é diferente de 0
          return 0;
        }
      }
    }                       //retorna 0 ou 1
  }

  return 1;
}

void classificar_matriz(int *matriz, int tamanho) {

  if (matriz_simetrica(matriz, tamanho)) {  //Se o retorno for 1 é simétrica, se for 0 não é simétrica
    printf("\nMatriz é simétrica!\n");
  } else {
    printf("\nMatriz não é simétrica!\n");
  }

  if (matriz_diagonal(matriz, tamanho)) { //Se o retorno for 1 é matriz diagonal
    printf("Matriz é diagonal!\n");
  } else {
    if (matriz_triangular_superior(matriz, tamanho)) { //Se o retorno for 1 é matriz triangular superior
      printf("Matriz é triangular superior!\n");
    } else if (matriz_triangular_inferior(matriz, tamanho)) { //Se o retorno for 1 é matriz triangular inferior
      printf("Matriz é triangular inferior!\n");
    } else {
      printf("Matriz não é diagonal!\n");
      printf("nem triangular superior!\n");   //Caso não entre em nenhuma condição acima
      printf("e nem triangular inferior!\n");
    }
  }
}

int somatorio_primeira_coluna(int *matriz, int tamanho) {
  int somatorio = 0; //Variável para acumular

  for (int i = 0; i < tamanho; i++) {  //Percorrendo apenas a primeira coluna
    somatorio += *(matriz + i * tamanho); 
  }
  return somatorio; //Retorna o somatorio

}

void mult_primeira_linha(int *matriz, int tamanho) {
    int valor, multiplicacao[tamanho][tamanho];

    printf("Informe um número inteiro a ser multiplicado pelos elementos da primeira linha: ");
    scanf("%d", &valor);

    for(int i = 0; i < tamanho; i++){
      for(int j = 0; j < tamanho; j++){
        multiplicacao[i][j] = *(matriz + i * tamanho + j);  //Usando uma matriz auxiliar para receber valores da matriz alocada
      }
    } 

    for (int j = 0; j < tamanho; j++) {   //Percorrendo apenas a primeira linha
      multiplicacao[0][j] = *(matriz + j) * valor; //Realizando a multiplicação e guardando na matriz auxiliar
    }
    printf("\n");

    printf("Elementos da primeira linha multiplicados:\n");
    for (int i = 0; i < tamanho; i++) {
      for(int j = 0; j < tamanho; j++) {
        printf("%d ", multiplicacao[i][j]); //Mostrar matriz com os elementos da primeira linha multiplicados
      }
      printf("\n");
    }
    printf("\n");
}

int soma_diag_principal(int *matriz, int tamanho) {
  int soma_diagonal = 0;

  for (int i = 0; i < tamanho; i++) { 
    soma_diagonal += *(matriz + i * tamanho + i);  //Percorrendo apenas a diagonal principal
  }
  return soma_diagonal; //Retorna a soma
}

void maior_valor(int *matriz, int tamanho) {
  int maior = *(matriz); //Maior = matriz[0][0]

  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      if (*(matriz + i * tamanho + j) > maior) {
        maior = *(matriz + i * tamanho + j);    //Loop para descobrir o maior valor da matriz
      }
    }
  }

  printf("O maior valor da matriz é %d\n", maior);

  int cont = 1; //Contador para mostrar quantas vezes valores iguais aparecem
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      if (*(matriz + i * tamanho + j) == maior) {
        printf("ocorrência nº %d do maior valor | linha : %d coluna: %d\n", cont++, i+1, j+1); //mostrando ocorrências, linha e coluna do maior valor
      }
    }
  }
}

void calculos_matriz(int *matriz, int tamanho) {

  int somatorio = somatorio_primeira_coluna(matriz, tamanho); //Somátorio primeira coluna
  printf("\nO somatório dos elementos da primeira coluna é: %d\n\n", somatorio);

  mult_primeira_linha(matriz, tamanho); //Multiplicação dos elementos da primeira linha, por um número inteiro

  int soma_diagonal_principal = soma_diag_principal(matriz, tamanho);  //A soma da diagonal principal
  printf("\nA soma da diagonal principal é %d\n\n", soma_diagonal_principal);

  maior_valor(matriz, tamanho); //Maior valor e sua posição(índice linha e coluna)
}

void Menu2(int *matriz, int tamanho) {
  char opcao;

  while(1) { //Loop true
    printf("\nSelecione uma opção:\nA - Classe de matriz\nB - Cálculos sobre a matriz\nC - Sair\n");
    scanf(" %c", &opcao);

    switch(toupper(opcao)) {
    case 'A':
      classificar_matriz(matriz, tamanho); //Classe de matriz
      break;
    case 'B':
      calculos_matriz(matriz, tamanho); //Cálculos sobre a matriz
      break;
    case 'C': 
      return; //Sair
    default:
      printf("Escolha uma opção válida!\n"); ////Caso não tenha sido digitado uma opção válida realiza outra iteração
    }
  }
}

void mostrarMatriz(int *matriz, int tamanho) {
  //Apenas para mostrar matriz criada
  printf("\nMatriz criada\n\n");
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      int elemento = *(matriz + (i * tamanho + j));
      printf("%d ", elemento);
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int *matriz, tamanho; //Ponteiro para inteiro e tamanho das linhas e colunas

  printf("Informe o tamanho das linhas e colunas da matriz NxN: "); //Informar tamanho NxN
  scanf("%d", &tamanho);

  matriz = (int *) malloc(tamanho * tamanho * sizeof(int)); //Realizando alocação dinâmica de memória

  if (!matriz) { //Testando se a alocação foi bem-sucedida
    printf("Erro de alocação dinâmica\n");
    exit(1);
  }

  //Matriz passada por referência e tamanho por valor
  Menu1(matriz, tamanho); //Primeiro menu, informar ou gerar elementos da matriz

  mostrarMatriz(matriz, tamanho); //Apenas para visualizar matriz criada

  Menu2(matriz, tamanho); //Segundo menu, classe e calculos sobre matriz

  free(matriz); //Liberação de memória

  return 0;
}
