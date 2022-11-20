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

int showTray(bool override) {
  char inputTray[100];
  int testingVar;
  FILE * fp;
  char str[60];
  int i = 1;

  if (override== FALSE){
  getchar(); // Para apanhar o [enter]
  printf("Filename: ");
  scanf("%s", inputTray);
  printf("\n");
  fp = fopen(inputTray, "r");
  }else{
    fp = fopen("tray.txt", "r");
  }



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
  

//tentativa de ler ficheiro warehouse.dat
/*
  char buffer[10];
   while (feof(fp) != EOF) // to read file
    {
      fread(buffer, sizeof(char), 1, fp);
      printf("\n%s", buffer);
   }
*/


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
      showTray(FALSE);
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

int main(int argc, char * argv[]) {
if (argc == 2) {
    if (!(strcmp(argv[1], "tray.txt"))) {
      showTray(TRUE);

    }
}
  showMenu();
  choices();

}
