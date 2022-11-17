/*trabalho 8 - ajudar nas estruturas: https://github.com/tiagomonteiro0715/Microprocessor-Programming/blob/main/PMAED-verao-2022/0.%20j%C3%A1%20feito/0PmTrabalhosEstruturas/code/final.c

Trabalho final ano passado: https://github.com/tiagomonteiro0715/pm/blob/main/code/final.c

2017 2018 - https://github.com/tiagomonteiro0715/Microprocessor-Programming/blob/main/PMAED-verao-2022/2-pm-trabalho-2017-2018/code/main.c 

Assim, o sistema de expedição deverá distribuir os Lotes seleccionados consoante as quantidades
(size) e os tipos (1 mm para Cartões e 4 mm para Livretes) pelas caixas (altura interior de 200 mm)
na disposição anterior

Cada lote tem 200 mm

só deve trocar de lote quando a some de cartoes e livretes dá mais de 200 mm

Duvida - ver se o 1º ponto de abrir o armazem quando o fichero abre está certo ou não.

como ler um ficheiro binário????

é preciso uma estrutura que diga como os tabuleiros devem estar dispostos. 
Não, isso é na função de apresentação. no ficheiro texto está linha por linha
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define TRUE 1
#define FALSE 0

#define MAX_DESTINY_STR 30
#define MAX_DATE_STR 12

#define NUM_TABULEIRO 4
#define NUM_PRATELEIRAS 4
#define LATERAL_SIZE 9


typedef struct lote {
  int id;
  char destiny[MAX_DESTINY_STR];
  char date[MAX_DATE_STR];
  int quantity;
  int type;
} LOTE;


typedef struct prateleira {
  size_t LOTE;
  char Position[LATERAL_SIZE][LATERAL_SIZE][NUM_PRATELEIRAS];
} PRATELEIRA;


LOTE exemplo_Um_Binario= { 1, "Sintra", "2022-07-16", 50, 2};
LOTE exemplo_Dois_Binario= { 2, "Lisboa", "2022-08-05", 50, 2};
LOTE exemplo_Tres_Binario= { 3, "Lisboa", "2022-05-27", 50, 2};
LOTE exemplo_Quatro_Binario= { 4, "Porto", "2022-03-12", 50, 2};
LOTE exemplo_Cinco_Binario= { 5, "Sintra", "2022-11-07", 50, 2};

//-----------------------------------------------------------------------------------------------------------
/*
int writeText(LOTE * ptr) {
  FILE * fp;
  fp = fopen("file.txt", "w+");

  fprintf(fp, "%d   %s   %s   %d   %d  ", ptr -> id, ptr -> destiny, ptr -> date, ptr -> quantity, ptr -> type);

  fclose(fp);
  printf("\nFile was written\n\n");

  return 0;
}
*/
void showMenu() {

  printf("0 - Show tray\n");
  printf("1 - Show batch info\n");
  printf("2 - List batches\n");
  printf("3 - Show wharehouse occupancy\n");

  printf("4 - Store tray\n");
  printf("5 - Swap batch placement\n");
  printf("6 - Show statistics\n");

  printf("7 - Perform expedition\n");

  printf("e - Exit\n\n");

}

void choices() {
  char choice;
  int choiceSucess = 0;

  FILE * fp;

  fp = fopen("warehouse.dat", "rb");
  if (fp == NULL) {
    printf("Error opening warehouse file\n");
    exit(1);
  }


  while (choiceSucess == 0) {
    showMenu();

    choice = getchar();
    switch (choice) {
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
    case '8':
      break;
    case 'e':
      fclose(fp);
      exit(1);
      break;
    }
  }

}

int main() {
choices();

}