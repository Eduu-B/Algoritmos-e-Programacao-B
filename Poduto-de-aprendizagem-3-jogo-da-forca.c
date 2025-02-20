#include <stdio.h>
#include <stdlib.h>
#include <string.h>                                                //Desenvolva um programa, na linguagem C, para implementar o Jogo da Forca
#include <ctype.h>
#include <time.h>                                                 //Nome: Eduardo Osmari Bortolotto
                                                                  
FILE* acessar_arquivo(char*);
char** alocar_lista_palavras(int);
int alocar_palavras(char*, FILE*, char**);
void menu(char**, int);
char* sortear_palavra(char**, int);                              //OBS: para facilitar as palavras estão todas minúsculas e sem acentuação
void jogo(char*);
int acertou_chute(char, char*);
int ganhou(char*, char*);
void exibir_palavra(char*, char*);
void fechar_liberar(FILE*, char**);

int main() {
  char buffer[50];

  FILE* fp = acessar_arquivo("palavras.txt"); //Abrindo arquivo de texto para leitura

  char** lista_palavras = alocar_lista_palavras(200); //Alocando lista de palavras

  int tamanho = alocar_palavras(buffer, fp, lista_palavras); //Alocando cada palavra
  
  menu(lista_palavras, tamanho); //Menu do jogo

  fechar_liberar(fp, lista_palavras); //Fechar arquivo e liberar memória

  return 0;
}

FILE* acessar_arquivo(char* string){ 
  FILE* fp; //Ponteiro do tipo file

  fp = fopen(string, "r"); //Abrindo o arquivo para leitura

  if(fp == NULL){ //Testando se o arquivo pode ser aberto
    printf("Erro ao abrir para leitura!\n");
    exit(1);
  }

  return fp; //Retornando ponteiro
}

char** alocar_lista_palavras(int linhas){
  char** lista_palavras; //ponteiro para ponteiro tipo char
  
  lista_palavras = malloc(linhas * sizeof(char *)); //Alocando memória para ponteiros tipo char

  if(lista_palavras == NULL){ //Testando se a alocação foi bem sucedida
    printf("Erro de alocação!\n");
    exit(1);
  }

  return lista_palavras; //Retornando ponteiro para ponteiro
}

int alocar_palavras(char* buffer, FILE* fp, char** lista_palavras){
  int tamanho = 0;

  while(fgets(buffer, 50, fp)){ //Armazenando em buffer oque está sendo lido do arquivo, enquanto não for null
  
    buffer[strcspn(buffer, "\n")] = '\0'; //No índice onde a string buffer contém o caractere '\n' substituir por '\0'

    lista_palavras[tamanho] = malloc((strlen(buffer) + 1) * sizeof(char)); //Alocando memória para cada palavra(string)

    if(lista_palavras[tamanho] == NULL){ //Testando se a alocação foi bem sucedida
      printf("Erro de alocação!\n");
      exit(1);
    }

    strcpy(lista_palavras[tamanho], buffer); //Copiando de buffer para lista_palavras no índice

    tamanho++; //Incrementando tamanho 
  }

  return tamanho; //Retornando tamanho
}

void menu(char** lista_palavras, int tamanho){
  char opcao;

    while(1){

    char* palavra_sorteada = sortear_palavra(lista_palavras, tamanho); //Sorteando uma palavra

    printf("\n\n--------------------------\n\n         FORCA EM C       \n\n--------------------------\n\n") ;
    printf("A-Jogar\nB-Sair");
    printf("\n\n        Feito por Eduardo Bortolotto\n");

      scanf("%c", &opcao);
      
      switch(toupper(opcao)) {
        case 'A':
          jogo(palavra_sorteada); //Jogar o jogo
          free(palavra_sorteada);  //Liberar memória alocada
          break;
        case 'B':
          return; //Sair
          break;
        default:
          printf("Escolha uma opção válida\n"); //Caso não tenha sido escolhida uma opção válida
          break;
      }
    }
}

char* sortear_palavra(char** lista_palavras, int tamanho){
  //Sorteando valor aleatório
  srand(time(0));
  int num_aleatorio = rand() % tamanho;

  char* palavra_sorteado = malloc(50 * sizeof(char)); //Alocando memória para palavra sorteada
  palavra_sorteado = lista_palavras[num_aleatorio]; //Palavra sorteada recebe lista palavras em um índice aleatório

  return palavra_sorteado; //Retornando palavra sorteada
}


void jogo(char* palavra_sorteada){
  int quantidade_tentativas = 5;
  int palpites = 0;
  char lista_palpites[50];

  printf("\nExibindo a palavra apenas para demonstração -> %s\n", palavra_sorteada); ;//Exibe a palavra sorteada(apenas para ficar mais legível para testar)
  printf("\nQuantidade de tentativas restantes: %d\n", quantidade_tentativas);

  while(1){
    char chute;
    
    printf("\nDiga uma letra: "); //Ler uma letra
    scanf(" %c", &chute);

    lista_palpites[palpites++] = chute; //"lista_palpites" no índice "palpites" sendo incrementado recebe "chute", guardando em um array os chutes

    if(acertou_chute(chute, palavra_sorteada)){ //Se retornar 1 acertou a letra
      printf("\nAcertou a letra!\n");

      if(ganhou(palavra_sorteada, lista_palpites)){  //Se retornar 1 ganhou
        printf("\n*** Ganhou ***\n");
        printf("\nA palavra era %s\n\n", palavra_sorteada);
        getchar();
        printf("\nAperte enter para continuar\n");
        getchar();

        return;
      }
    } 
    else{
      printf("\nErrou a letra!\n"); //Se errar a letra a quantidade de tentativas é decrementada
      quantidade_tentativas--;
      printf("Quantidades de tentativas restantes: %d\n", quantidade_tentativas);

      if(quantidade_tentativas == 0){ //Se quantidade de tentativas chegar em 0 perde o jogo
        printf("\n*** Perdeu ***\n");
        printf("\nA palavra era %s\n\n", palavra_sorteada); //Exibe a palavra
        getchar();
        printf("\nAperte enter para continuar\n");
        getchar();
        return;
      }
    }
    
    exibir_palavra(lista_palpites, palavra_sorteada); //Mostra os "tracinhos" e as letras
  }

}

int acertou_chute(char chute, char* palavra_sorteada){

  for(int i=0; *(palavra_sorteada+i); i++){ //Verifica se a palavra sorteada contém a letra do chute
    if(chute == *(palavra_sorteada+i))
      return 1;
  }
  return 0;
}

int ganhou(char* palavra_sorteada, char* lista_palpites){

  for(int i=0; *(palavra_sorteada+i); i++){  //Primeiro for, variável letra recebe cada letra de palavra sorteada
    char letra = *(palavra_sorteada+i);
    int flag = 0;

    for(int j=0; *(lista_palpites+j); j++){  //Segundo for, verifica se letra está na lista_palpites 
      if(letra == *(lista_palpites+j))
        flag = 1;
    }
    if(!flag) return 0;    //Caso alguma flag seja false return 0
  }
  return 1; //Se todas as letras der flag true return 1;
}

void exibir_palavra(char* lista_palpites, char* palavra_sorteada) {

  printf("\n");
  for(int i=0; *(palavra_sorteada+i); i++){   //Primeiro for, variável letra recebe cada letra de palavra sorteada
    char letra = *(palavra_sorteada+i);
    int flag = 0;

    for(int j=0; *(lista_palpites+j); j++){  //Segundo for, verifica se letra está na lista_palpites
      if(letra == *(lista_palpites+j))
        flag = 1;  
    }
    if(flag == 1)     //Se a letra da palavra sorteada estiver na lista_palpites flag true, print a letra se não estiver flag false, print um "tracinho"
      printf("%c ", letra);
    else
      printf("_ ");
  }
  printf("\n");
  return;
}

void fechar_liberar(FILE* fp, char** lista_palavras){
  fclose(fp);
  free(lista_palavras);
}
