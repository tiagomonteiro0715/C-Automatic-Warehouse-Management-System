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
 *****************  Declaração de estruturas  ********************
 ****************************************************************/
struct loteCompleto {
  unsigned int id; //4 bytes
  char destiny[MAX_DESTINY_STR]; //30 bytes
  char date[MAX_DATE_STR]; //12 bytes
  unsigned int quantity; //4 bytes
  unsigned int type; //4 bytes
};

typedef struct slot {
  struct loteCompleto lote;
  unsigned int flag; //0 - livre || 1 - ocupado
}
SLOT;
/****************************************************************
 *******  Declaração de funções de leitura de estruturas  *******
 ****************************************************************/
void le_lote_pedido(SLOT * ptr, int expectedUserInputId) {
  if (expectedUserInputId == ( * ptr).lote.id) {
    printf("\n\n=== Produto ===\n Id: %u\n Destination:%s\n Quantity:%u\n Type:%u\n Exp. Date:%s\n\n",
      ( * ptr).lote.id,
      ( * ptr).lote.destiny,
      ( * ptr).lote.quantity,
      ( * ptr).lote.type,
      ( * ptr).lote.date
    );
  }
}

void le_lote_completo(SLOT * ptr) {
  printf("\n\n id: %u destiny:%s date:%s quantity:%u type:%u",
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
  le_lote_completo(ptr);
  printf(" flag:%u \n",
    ( * ptr).flag
  );
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
    fscanf(fp, "%d %s %s %d %d", & inputVar, destinyVar, dateVar, & quantityVar, & typeVarInt); // fscanf(fp, "%d %d", &inputVar, &typeVar);

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
  SLOT slotExample[4][9][9];
  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }

  for (int z = 0; z <= 4; z++) {
    for (int y = 0; y <= 9; y++) {
      for (int x = 0; x <= 9; x++) {
        fread( & slotExample[z][y][x], sizeof(SLOT), 1, fp);
        le_slot_completo( & slotExample[z][y][x]);

      }
    }
  }

  /*
  while(fread(&slotExample[9][9][4], sizeof(SLOT), 1, fp)){
  		le_slot_completo(&slotExample[9][9][4]);
    }
  */

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

  return 0;
}

int warehouseOccupancy() {

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