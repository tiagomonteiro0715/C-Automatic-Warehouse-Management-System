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

como fazer com que o menu apareça uma só vez??

apresentada numa matriz 4x4, com o ID do lote e o seu tipo (ver Figura 6). - onde é que o tipo fica?? é suposto contagenar o IR com o tipo? -- ID_Tipo 



showTray - está bom assim ou coloco uma matriz para ficar tudo alinhado?
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
}
LOTE;

typedef struct prateleira {
  size_t LOTE;
  char Position[LATERAL_SIZE][LATERAL_SIZE][NUM_PRATELEIRAS];
}
PRATELEIRA;

void le_lote(LOTE * ptr) {
  printf("\n===Conteudos lote===\n id: %d\n destiny:%s\n date:%s\n quantity:%d\n type:%d\n n",
    ( * ptr).id,
    ( * ptr).destiny,
    ( * ptr).date,
    ( * ptr).quantity,
    ( * ptr).type
  );
}

//-----------------------------------------------------------------------------------------------------------

int showTray() {
  char inputTray[100];
  int testingVar;
  FILE * fp;
  char str[60];
  int i = 1;
  getchar(); // Para apanhar o [enter]

  printf("Filename: ");
  scanf("%s", inputTray);
  printf("\n");
  fp = fopen(inputTray, "r");
  if (fp == NULL) {
    printf("Error opening text file\n");
    exit(1);
  }

  while (fgets(str, sizeof(str), fp)) {
    fscanf(fp, "%d", & testingVar);
    printf("%d ", testingVar);
    if (!(i % 4)) {
      printf("\n");
    }
    i = i + 1;
  }
  //https://www.youtube.com/watch?v=TzNhPOwjlb0
  //depois deste video usar só read para ler o ficheiro .dat
  //ver trabalho de ano passado na drive do NEEC como leram ficheiros .dat e como está no livro

  fclose(fp);
  return 0;

}
//-----------------------------------------------------------------------------------------------------------

int showCompleteBatch() {
  FILE * fp = fopen("warehouse.dat", "rb");

  if (fp == NULL) {
    printf("Error opening text file\n");
    exit(1);
  }

  /*
  fread binary file c

  como ver estrutura de ficheiro binário??

  showtray - fazer array para colocar lá os valores. fica melhor assim. como é uma função, depois de ussada a memoria é apagada.

  ver trabalho de ano passado emeplo para ver como eles virem ficheiro .dat to paulo pinto

  https://stackoverflow.com/questions/35820879/read-a-dat-file-in-c

  ler livro de PM
  */

  return 0;
}

void showMenu() {

  printf("\n\n1 - Show tray\n");
  printf("2 - Show batch info\n");
  printf("3 - List batches\n");
  printf("4 - Show wharehouse occupancy\n");

  printf("5 - Store tray\n");
  printf("6 - Swap batch placement\n");
  printf("7 - Show statistics\n");

  printf("8 - Perform expedition\n");

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
    choice = getchar();
    switch (choice) {
    case '1':
      showTray();
      showMenu();
      break;
    case '2':
      showCompleteBatch();
      showMenu();
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

  showMenu();

  choices();

}