#include <stdio.h>

#include <stdlib.h>

#include <string.h>


/* Defining the constants that will be used in the program. */
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
/**
 * A loteCompleto is a struct that contains an int, a char[], a char[], an int, and an int.
 * @property {int} id - the id of the lote
 * @property {char} destiny - The destiny of the lote.
 * @property {char} date - "dd/mm/yyyy"
 * @property {int} quantity - number of items in the lot
 * @property {int} type - 0 =&gt; "Cereal"
 */
struct loteCompleto {
  int id; //4 bytes
  char destiny[MAX_DESTINY_STR]; //30 bytes
  char date[MAX_DATE_STR]; //12 bytes
  int quantity; //4 bytes
  int type; //4 bytes
};

/**
 * A slot is a structure that contains a loteCompleto structure and an integer flag.
 * @property lote - a struct that contains a loteCompleto, which is a struct that contains a lote,
 * which is a struct that contains a loteSimples, which is a struct that contains a loteSimples, which
 * is a struct that contains a loteSimples, which is a
 * @property {int} flag - 0 - free || 1 - occupied
 */
typedef struct slot {
  struct loteCompleto lote;
  int flag; //0 - livre || 1 - ocupado
}
SLOT;
/****************************************************************
 *******  Declaração de funções de leitura de estruturas  *******
 ****************************************************************/
/**
 * It prints the contents of a struct if the user input matches the struct's id
 * 
 * @param ptr pointer to the current slot
 * @param expectedUserInputId The id that the user inputted
 */
void le_lote_pedido(SLOT * ptr, int expectedUserInputId) {
  if ((expectedUserInputId == ( * ptr).lote.id) && (( * ptr).flag == 1)) {
    printf("\n\n=== Produto ===\n Id: %d\n Destination:%s\n Quantity:%d\n Type:%d\n Exp. Date:%s\n\n",
      ( * ptr).lote.id,
      ( * ptr).lote.destiny,
      ( * ptr).lote.quantity,
      ( * ptr).lote.type,
      ( * ptr).lote.date
    );
  }
}

/**
 * It prints the contents of a SLOT structure
 * 
 * @param ptr pointer to the slot
 */
void le_lote_completo(SLOT * ptr) {
  printf("\n\n=== Produto ===\n Id: %d\n Destination:%s\n Quantity:%d\n Type:%d\n Exp. Date:%s\n\n",
    ( * ptr).lote.id,
    ( * ptr).lote.destiny,
    ( * ptr).lote.quantity,
    ( * ptr).lote.type,
    ( * ptr).lote.date
  );
}

/**
 * It reads a lot of data from the user, and then it reads a lot of data from the user
 * 
 * @param ptr a pointer to a SLOT struct
 * @param expectedUserInputId The expected user input id.
 */
void le_slot_pedido(SLOT * ptr, int expectedUserInputId) {
  le_lote_pedido(ptr, expectedUserInputId);
}

/**
 * It reads a complete slot, if the flag is 1
 * 
 * @param ptr pointer to the slot
 */
void le_slot_completo(SLOT * ptr) {
  if (( * ptr).flag == 1) {
    le_lote_completo(ptr);
  }
}

/**
 * It checks the occupancy of a slot and returns a boolean value or a string value depending on the
 * value of the boolean parameter.
 * 
 * @param ptr pointer to the slot
 * @param inputFlagState This is a char array that will be used to store the flag state of the slot.
 * @param giveBoolVal TRUE or FALSE
 * 
 * @return the value of the flag variable.
 */
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
/**
 * "If the inputInt is 1, then save the string "C" to the saveCharVar, otherwise if the inputInt is 2,
 * then save the string "L" to the saveCharVar."
 * 
 * The above function is called in the following way:
 * 
 * @param saveCharVar The variable that will be saved to.
 * @param inputInt The number that will be converted to a string.
 * @param fullText TRUE or FALSE
 */
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

/**
 * It reads a file and prints the contents of it
 * 
 * @param override if true, it will read from a file called "tray.txt" directly from the command line
 * 
 * @return the number of characters that were written to the file.
 */
//-----------------------------------------------------------------------------------------------------------

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

/**
 * It reads the binary file and prints the content of the file
 * 
 * @return the number of slots that are complete.
 */
int showCompleteBatch() {

  FILE * fp = fopen("warehouse.dat", "rb+");
  SLOT slotExample;
  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }
  while (fread( & slotExample, sizeof(SLOT), 1, fp)) {
    le_slot_completo( & slotExample);
  }

  fclose(fp);

  return 0;
}

/**
 * It reads a binary file and prints the information of a specific ID
 * 
 * @return the value 0.
 */
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

/**
 * It reads the binary file, and prints out the contents of the file in a grid format
 * 
 * @return the number of slots that are occupied in the warehouse.
 */
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
/**
 * It prints a menu
 */
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

/**
 * It takes a string as an argument, and if the string is equal to "tray.txt", it calls the showTray
 * function with the argument TRUE
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The argument vector.
 */
int main(int argc, char * argv[]) {
  if (argc == 2) {
    if (!(strcmp(argv[1], "tray.txt"))) {
      showTray(TRUE);
    }
  }
  showMenu();
  choices();
}