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

/****************************************************************
 *****************  Declaração de estruturas  *******************
 ****************************************************************/
struct loteCompleto {
  int id; //4 bytes
  char destiny[MAX_DESTINY_STR]; //30 bytes
  char date[MAX_DATE_STR]; //12 bytes
  int quantity; //4 bytes
  int type; //4 bytes
};

typedef struct slot {
  struct loteCompleto lote;
  int flag; //0 - livre || 1 - ocupado
}
SLOT;
/****************************************************************
 *******  Declaração de funções de leitura de estruturas  *******
 ****************************************************************/
void le_lote_pedido(SLOT * ptr, int expectedUserInputId) {
  if (expectedUserInputId == ( * ptr).lote.id) {
    printf("\n\n=== Produto ===\n Id: %d\n Destination:%s\n Quantity:%d\n Type:%d\n Exp. Date:%s\n\n",
      ( * ptr).lote.id,
      ( * ptr).lote.destiny,
      ( * ptr).lote.quantity,
      ( * ptr).lote.type,
      ( * ptr).lote.date
    );
  }
}

void le_lote_completo(SLOT * ptr) {
  printf("\n\n id: %d destiny:%s date:%s quantity:%d type:%d",
    ( * ptr).lote.id,
    ( * ptr).lote.destiny,
    ( * ptr).lote.date,
    ( * ptr).lote.quantity,
    ( * ptr).lote.type
  );
}

void le_slot_pedido(SLOT * ptr, int expectedUserInputId) {
  le_lote_pedido(ptr, expectedUserInputId);
}

void le_slot_completo(SLOT * ptr) {
  if(( * ptr).flag == 1){
   le_lote_completo(ptr);
    printf(" flag:%d \n",
    ( * ptr).flag
  ); 
  }
  

}

int checkOccupancy(SLOT * ptr, char * inputFlagState, bool giveBoolVal) {
  if (giveBoolVal == FALSE) {
    if (( * ptr).flag == 0) {
      strcpy(inputFlagState, ".");
    }
    if (( * ptr).flag == 1) {
      strcpy(inputFlagState, "X");
    }
  }

  if (giveBoolVal == TRUE) {
    if (( * ptr).flag == 0) {
      return FALSE;
    }
    if (( * ptr).flag == 1) {
      return TRUE;
    }

  }
  return 0;
}
/****************************************************************
 ***********************  Funções  *******************************
 ****************************************************************/
void convertNumToType(char * saveCharVar, int inputInt, bool fullText) {
  if (fullText == FALSE) {
    if (inputInt == 1) {
      strcpy(saveCharVar, "C");
    }
    if (inputInt == 2) {
      strcpy(saveCharVar, "L");
    }
  }

}

int showTray(bool override) {
  FILE * fp;
  char inputTrayName[100];
  char strToReadInput[60];
  int countLoop = 0;

  int inputVar;
  char destinyVar[MAX_DESTINY_STR];
  char dateVar[MAX_DATE_STR];
  int quantityVar;

  int typeVarInt;
  char typeVarChar;
  if (override == FALSE) {
    getchar(); // Para apanhar o [enter]
    printf("Filename: ");
    scanf("%s", inputTrayName);
    printf("\n");
    fp = fopen(inputTrayName, "r");
  } else {
    fp = fopen("tray.txt", "r");
  }

  if (fp == NULL) { //d´a NULL porque n~ao est´a a apontar para nada
    printf("Error opening text file\n");
    exit(1);
  }

  while (fgets(strToReadInput, sizeof(strToReadInput), fp)) {
    fscanf(fp, "%d %s %s %d %d", &inputVar, destinyVar, dateVar, & quantityVar, & typeVarInt); // fscanf(fp, "%d %d", &inputVar, &typeVar);

    if (!(countLoop % 4)) {
      printf("\n");
    }

    convertNumToType( & typeVarChar, typeVarInt, FALSE);
    printf(" %d_%c ", inputVar, typeVarChar);

    countLoop += 1;
  }

  fclose(fp);
  return 0;

}
//-----------------------------------------------------------------------------------------------------------

int showCompleteBatch() {

  FILE * fp = fopen("warehouse.dat", "rb+");
  SLOT slotExample[5][10][10];
  SLOT slotExampleOne;
  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }
/*
  for (int z = 0; z <= 4; z++) {
    for (int y = 0; y <= 9; y++) {
      for (int x = 0; x <= 9; x++) {
        fread( & slotExample[z][y][x], sizeof(SLOT), 1, fp);
        le_slot_completo( & slotExample[z][y][x]);

      }
    }
  }
*/
  
  while(fread(&slotExampleOne, sizeof(SLOT), 1, fp)){
  		le_slot_completo(&slotExampleOne);
    }
  

  fclose(fp);

  return 0;
}

int batchInfo() {
  FILE * fp = fopen("warehouse.dat", "rb+");
  SLOT slotExample;
  int userInputId;

  printf("ID: ");
  scanf("%d", & userInputId);
  getchar();

  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }

  while (fread( & slotExample, sizeof(SLOT), 1, fp)) {
    le_slot_pedido( & slotExample, userInputId);
  }
  
  fclose(fp);

  return 0;
}

int warehouseOccupancy() {
  FILE * fp = fopen("warehouse.dat", "rb+");
  SLOT slotExample;
  char input;
  int userInputShelf;
  int countLine = 1;
  int printCurrentLine = 0;
  printf("Shelf: ");
  scanf("%d", & userInputShelf);
  getchar();

  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }

  printf("\n\n -----WAREHOUSE-----\n");
  printf(" 0 1 2 3 4 5 6 7 8 9\n");
  
  while (fread( & slotExample, sizeof(SLOT), 1, fp)) {
    if (!(countLine % 9)) {
      printCurrentLine += 1;
      printf("%d\n", printCurrentLine);
    }
    checkOccupancy( & slotExample, & input, FALSE);
    printf("%c ", input);

    countLine += 1;
  }

  return 0;
}

int storeTray() {
  //checkOccupancy( & slotExample, & input, TRUE);

  FILE * fp;
  char inputTrayName[100];
  char strToReadInput[60];

  int inputVar;
  char destinyVar[MAX_DESTINY_STR];
  char dateVar[MAX_DATE_STR];
  int quantityVar;

  int typeVarInt;

  getchar(); // Para apanhar o [enter]
  printf("Tray Filename: ");
  scanf("%s", inputTrayName);
  printf("\n");
  fp = fopen(inputTrayName, "r");

  if (fp == NULL) { //d´a NULL porque n~ao est´a a apontar para nada
    printf("Error opening text file\n");
    exit(1);
  }

  while (fgets(strToReadInput, sizeof(strToReadInput), fp)) {
    fscanf(fp, "%d %s %s %d %d", & inputVar, destinyVar, dateVar, & quantityVar, & typeVarInt); // fscanf(fp, "%d %d", &inputVar, &typeVar);
  }

  fclose(fp);
  return 0;

  return 0;
}
void showMenu() {

  printf("\n\n1 - Show tray\n");

  printf("2 - Show batch info\n");
  printf("3 - List batches\n");
  printf("4 - Show wharehouse occupancy\n\n");

  printf("5 - Store tray\n");
  printf("6 - Swap batch placement\n");
  printf("7 - Show statistics\n\n");

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
      batchInfo();
      showMenu();
      break;
    case '3':
      showCompleteBatch();
      showMenu();
      break;
    case '4':
      warehouseOccupancy();
      showMenu();
      break;
    case '5':
      storeTray();
      showMenu();
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
