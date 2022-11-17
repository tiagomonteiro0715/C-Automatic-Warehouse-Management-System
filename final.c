/*trabalho 8 - ajudar nas estruturas: https://github.com/tiagomonteiro0715/Microprocessor-Programming/blob/main/PMAED-verao-2022/0.%20j%C3%A1%20feito/0PmTrabalhosEstruturas/code/final.c

Trabalho final ano passado: https://github.com/tiagomonteiro0715/pm/blob/main/code/final.c

2017 2018 - https://github.com/tiagomonteiro0715/Microprocessor-Programming/blob/main/PMAED-verao-2022/2-pm-trabalho-2017-2018/code/main.c 

Ler resto do trabalho ponta a ponta e fazer já funções básicas. 
È agora que se define toda a estrutura do trabalho.

Por bem o nome das variaveis em portugues e em variaveis com numeros colocar #define's

abrir ficherio .dat para ver formato
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define TRUE 1
#define FALSE 0

#define MAX_DESTINY_STR 30
#define MAX_DATE_STR 12

#define NUM_PRATELEIRAS 5
#define LATERAL_SIZE 49


typedef struct lote {
  int id;
  char destiny[MAX_DESTINY_STR];
  char date[MAX_DATE_STR];
  int quantity;
  int type;
} LOTE;

typedef struct prateleira {
  size_t LOTE;
  char Position[49][49];
} PRATELEIRA;

PRATELEIRA armazem[4];

//-----------------------------------------------------------------------------------------------------------

int readBinary() {
  FILE * fp;

  fp = fopen("file.data", "rb");
  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }
  //reler enunciato todo + 

  fclose(fp);

  return 0;
}

void showMenu() {

  printf("\nCompanhia de Aviação “Ja Fui”\n");
  printf("Programa de reservas\n\n\n");

  printf("0 - Show tray\n");
  printf("1 - Show batch info\n");
  printf("2 - List batches\n");
  printf("3 - Show wharehouse occupancy\n");

  printf("4 - Store tray\n");
  printf("5 - Swap batch placement\n");
  printf("6 - Show statistics\n");

  printf("7 - Perform expedition\n");

  printf("e - exit\n\n");

}

void choices() {
  char choice;
  int choiceSucess = 0;

  while (choiceSucess == 0) {
    showMenu();

    choice = getchar();
    switch (choice) {
    case '0':
      break;
    case '1':
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      break;
    case '5':
      break;
    case '6':
      break;
    case '7':
      break;
    case 'e':
      exit(1);
      break;
    }
  }

}

int sum(int a, int b){
    return a+b;
}

int main() {
choices();

}