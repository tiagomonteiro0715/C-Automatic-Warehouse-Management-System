#include <stdio.h>

#include <stdlib.h>

#include <string.h>


/* Defining the constants that will be used in the program. */
#define bool int
#define TRUE 1
#define FALSE 0

#define MAX_DESTINY_STR 30
#define MAX_DATE_STR 12
#define MAX_TYPE_STR 10

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
 * It converts a number to a type of product.
 * 
 * @param saveCharVar The variable that will save the converted value.
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
  if (fullText == TRUE) {
    if (inputInt == 1) {
      strcpy(saveCharVar, "Cartoes");
    }
    if (inputInt == 2) {
      strcpy(saveCharVar, "Livretes");
    }
  }
}

/**
 * It prints the contents of a struct if the user input matches the struct's id
 * 
 * @param ptr pointer to the current slot
 * @param expectedUserInputId The id that the user inputted
 */
void le_lote_pedido(SLOT * ptr, int expectedUserInputId) {
  char ConvertedtypeName[MAX_TYPE_STR];

  convertNumToType(ConvertedtypeName, ( * ptr).lote.type, TRUE);

  if ((expectedUserInputId == ( * ptr).lote.id) && (( * ptr).flag == 1)) {
    printf("\n\n=== Produto ===\n Id: %d\n Destination:%s\n Quantity:%d\n Type:%s\n Exp. Date:%s",
      ( * ptr).lote.id,
      ( * ptr).lote.destiny,
      ( * ptr).lote.quantity,
      ConvertedtypeName,
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
  printf("\n\n=== Produto ===\n Id: %d\n Destination:%s\n Quantity:%d\n Type:%d\n Exp. Date:%s",
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
 * @return the value of the flag variable in the slot structure.
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

/**
 * It takes an input number, and prints out the slot position of the number
 * 
 * @param inputNum the number that is inputted by the user
 */
void print_NumToSlotPosition(int inputNum) {
  inputNum = inputNum % 100;
  int decimal = inputNum / 10;
  int unit = inputNum % 10;
  printf("\n Slot: %d %d", decimal, unit);
}

/****************************************************************
 ***********************  Funções  *******************************
 ****************************************************************/
/**
 * It reads a tray file and prints the contents of the file in a matrix format
 * 
 * @param override If the user inputted a file name, it will be FALSE. If the user did not input a file
 * name, it will be TRUE.
 * 
 * @return the value 0.
 */
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
  /* Checking if the user inputted a file name, and if the user did not input a file name, it will open
  the file "tray.txt" */
  if (override == FALSE) {
    getchar(); // Para apanhar o [enter]
    printf("Filename: ");
    scanf("%s", inputTrayName);
    printf("\n");
    fp = fopen(inputTrayName, "r");
  } else {
    fp = fopen("tray.txt", "r");
  }

  /* Checking if the file is open. If it is not, it prints an error message and exits the program. */
  if (fp == NULL) {
    printf("Error opening text file\n");
    exit(1);
  }

  /* Reading a file and printing the contents of the file. */
  while (fgets(strToReadInput, sizeof(strToReadInput), fp)) {
    sscanf(strToReadInput, "%d %s %s %d %d", & inputVar, destinyVar, dateVar, & quantityVar, & typeVarInt); // fscanf(fp, "%d %d", &inputVar, &typeVar);

    /* Printing a new line every 4 lines. */
    if (!(countLoop % 4)) {
      printf("\n");
    }

    printf("%2d", inputVar);
    /* Converting the inputVar to a character and printing it. */
    convertNumToType( & typeVarChar, typeVarInt, FALSE);
    printf("_%c ", typeVarChar);

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

  /* Opening the file warehouse.dat in binary mode for reading and writing. */
  FILE * fp = fopen("warehouse.dat", "rb+");

  SLOT slotExample;
  int countLine = 0;

  /* Checking if the file is open. If it is not, it prints an error message and exits the program. */
  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }

  /* Reading the binary file and printing the contents of the file. */
  while (fread( & slotExample, sizeof(SLOT), 1, fp)) {
    le_slot_completo( & slotExample);

    /* Counting the number of slots that are occupied in the warehouse. */
    countLine = countLine + 1;
    int Shelf = countLine / 100;

    /* Printing the slot position and the shelf number in the warehouse */
    if ((slotExample.flag == 1)) {
      print_NumToSlotPosition(countLine);
      printf(" Shelf: %d", Shelf);
    }

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

  /* Opening the file warehouse.dat in binary mode for reading and writing. */
  FILE * fp = fopen("warehouse.dat", "rb+");

  SLOT slotExample;
  int userInputId;
  int countLine = 0;

  /* Asking the user to input an ID number. */
  printf("ID: ");
  scanf("%d", & userInputId);
  getchar();

  /* Opening a file and checking if it is NULL. If it is NULL, it will print an error message and exit. */
  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }

  /* Reading the file and printing the slot position and shelf number. */
  while (fread( & slotExample, sizeof(SLOT), 1, fp)) {
    le_slot_pedido( & slotExample, userInputId);

    /* Printing the shelf number and slot position. */
    countLine = countLine + 1;
    int Shelf = countLine / 100;
    if ((slotExample.flag == 1)) {
      print_NumToSlotPosition(countLine);
      printf(" Shelf: %d", Shelf);
    }
  }

  fclose(fp);

  return 0;
}

void printInputShelf(FILE * fp, SLOT slotExample, int inputShelf, char inputStoreTempVar) {
  int printCurrentLine = 0;
  int countAllCharParser;
  int currentShelf;

  printf("\n\n -----WAREHOUSE-----\n");
  printf(" 0 1 2 3 4 5 6 7 8 9");

  for (countAllCharParser = 0; fread( & slotExample, sizeof(SLOT), 1, fp); countAllCharParser++) {
    if (!(countAllCharParser % 9 && (countAllCharParser != 0))) {
      /*if (currentShelf == inputShelf) {
        printf("\n %d ", (printCurrentLine % 10));
      }*/ 
      printf("\n %d ", (printCurrentLine));//% 10
      printCurrentLine += 1;
    }

    checkOccupancy( & slotExample, & inputStoreTempVar, FALSE);
    /*if (currentShelf == inputShelf) {
      printf("%c ", inputStoreTempVar);
    }*/ 
    printf("%c ", inputStoreTempVar);      
    currentShelf = printCurrentLine / 10;
  }
}

/**
 * It reads the binary file, and prints out the contents of the file in a grid format
 * 
 * @return the number of slots that are occupied in the warehouse.
 */
int warehouseOccupancy() {

  /* Opening the file warehouse.dat in binary mode for reading and writing. */
  FILE * fp = fopen("warehouse.dat", "rb+");
  SLOT slotExample;

  /* Declaring the variables that will be used in the program. */
  char inputStoreTemp = ' ';
  int userInputIntShelf;

  /* Asking the user to input the shelf number. */
  printf("Shelf: ");
  scanf("%d", & userInputIntShelf);
  getchar();

  /* Opening a file and checking if it is NULL. If it is NULL, it will print an error message and exit. */
  if (fp == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }

  switch (userInputIntShelf) {
  case 0: //fazer função para isto tudo. usar   int shelf = printCurrentLine/10
    printInputShelf(fp, slotExample, userInputIntShelf, inputStoreTemp);
    break;

  case 1:
    printInputShelf(fp, slotExample, userInputIntShelf, inputStoreTemp);
    break;

  case 2:
    printInputShelf(fp, slotExample, userInputIntShelf, inputStoreTemp);
    break;

  case 3:
    printInputShelf(fp, slotExample, userInputIntShelf, inputStoreTemp);
    break;

  case 4:
    printInputShelf(fp, slotExample, userInputIntShelf, inputStoreTemp);
    break;
  }
  return 0;
}



int saveTrayToWarehouse() {

  FILE * fp;
  SLOT exampleSlot;
  FILE * fpWarehouse = fopen("warehouse.dat", "rb+");

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

  if (fp == NULL) {
    printf("Error opening text file\n");
    exit(1);
  }

  if (fpWarehouse == NULL) {
    printf("Error opening binary file\n");
    exit(1);
  }

/***************************************************************************/
/*Zona de codigo a desenvolver*/
  while (fgets(strToReadInput, sizeof(strToReadInput), fp)) {
    fscanf(fp, "%d %s %s %d %d", & inputVar, destinyVar, dateVar, & quantityVar, & typeVarInt); // fscanf(fp, "%d %d", &inputVar, &typeVar);
  }

  while (fread( & exampleSlot, sizeof(SLOT), 1, fpWarehouse)) {
    if(exampleSlot.flag == 0){

  }
  }


/***************************************************************************/

  fclose(fp);
  fclose(fpWarehouse);

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
      saveTrayToWarehouse();
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