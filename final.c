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
  unsigned int id;
  char destiny[MAX_DESTINY_STR];
  char date[MAX_DATE_STR];
  unsigned int quantity;
  unsigned int type;
}
LOTE;

//static const LOTE loteVazio; //usamos static para iniciar todos os valores. Bem bom. Assim não os tenho que preenher - https://stackoverflow.com/questions/10927274/gcc-uninitialized-global-variables/10927409#10927409

/*
typedef struct prateleira {
  size_t LOTE;
  char Position[LATERAL_SIZE][LATERAL_SIZE][NUM_PRATELEIRAS];
}
PRATELEIRA;
*/

/*
void le_lote(LOTE * ptr) {
  printf("\n\n===Conteudos lote===\n id: %u\n destiny:%s\n date:%s\n quantity:%u\n type:%u\n\n",
    ( * ptr).id,
    ( * ptr).destiny,
    ( * ptr).date,
    ( * ptr).quantity,
    ( * ptr).type
  );
}
*/

void le_lote(LOTE * ptr) {
  printf("\n\n id: %u destiny:%s date:%s quantity:%u type:%u\n",
    ( * ptr).id,
    ( * ptr).destiny,
    ( * ptr).date,
    ( * ptr).quantity,
    ( * ptr).type
  );
}
LOTE exemploLote;
//-----------------------------------------------------------------------------------------------------------

int showTray(bool override) {
  char inputTray[100];
  int testingVar;
  FILE * fp;
  char str[60];
  int i = 1;

  if (override == FALSE) {
    getchar(); // Para apanhar o [enter]
    printf("Filename: ");
    scanf("%s", inputTray);
    printf("\n");
    fp = fopen(inputTray, "r");
  } else {
    fp = fopen("tray.txt", "r");
  }

  if (fp == NULL) { //d´a NULL porque n~ao est´a a apontar para nada
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

  size_t varTest;
  char * size = " "; 
  char * enter = "\n";
  //&& varTest != (fread(buff, sizeof(LOTE), 1, fp) == *size)
  LOTE * buff = malloc(sizeof(LOTE));
  while ((varTest = fread(buff, sizeof(LOTE), 1, fp)) > 0 ) {
    if(varTest != *size || varTest != *enter){
      le_lote(buff); 
    }
    

  }
  free(buff);

  /*
  fread binary file c
 tipo 1 - C - cartoes
 tipo 2 - L - livretes

 por isto bem na funç~ao showtray.txt
 
 conctagenar ambos com _ e funç~ao de convers~ao de numero para letra. usar strcpy
  */

  /*
  fazer fwrite para um ficheiro texto para usar fscanf e para ver se está a ler bem o ficheiro
  https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm

  senão tenho que mandar email ao professor

  posso fazer isso??

  pela linha de comandos está a haver problemas

  correr contigo na maquina virtual
  */

  /*links que me ajudaram
  https://stackoverflow.com/questions/21721808/how-to-fread-structs
  https://stackoverflow.com/questions/37779302/fread-into-struct-reads-data-incorrectly
  https://stackoverflow.com/questions/16075233/reading-and-processing-wav-file-data-in-c-c
  https://stackoverflow.com/questions/61834780/reading-binary-file-and-storing-it-to-struct-in-c?noredirect=1&lq=1
  https://stackoverflow.com/questions/21721808/how-to-fread-structs
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
      break;
    case '3':
      showCompleteBatch();
      showMenu();
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