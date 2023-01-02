#include <stdio.h>

#include <stdlib.h>

#include <string.h>


/* Defining the constants that will be used in the program. */
#define bool int
#define TRUE 1
#define FALSE 0

#define MAX_DESTINY_STR 30
#define MAX_DATE_STR 12

#define NUM_DISTRITOS_CONTINENTAL 17

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

int isnull(char * string) {
  return (strlen(string) == 0);
}
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
 * It prints the contents of a SLOT structure
 * 
 * @param ptr pointer to the slot
 */
void leLote(SLOT * ptr) {
  printf("\n\n=== Produto ===\n Id: %d\n Destination:%s\n Quantity:%d\n Type:%d\n Exp. Date:%s",
    ( * ptr).lote.id,
    ( * ptr).lote.destiny,
    ( * ptr).lote.quantity,
    ( * ptr).lote.type,
    ( * ptr).lote.date
  );
}

/**
 * It reads a complete slot, if the flag is 1
 * 
 * @param ptr pointer to the slot
 */
void leSlot(SLOT * ptr) {
  if (( * ptr).flag == 1) {
    leLote(ptr);
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
int checkOccupancy(SLOT * ptr, char * inputFlagState) {
  if (( * ptr).flag == 0) {
    strcpy(inputFlagState, ".");
  }
  if (( * ptr).flag == 1) {
    strcpy(inputFlagState, "X");
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

  FILE * filePtr;

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
    filePtr = fopen(inputTrayName, "r");
  } else {
    filePtr = fopen("tray.txt", "r");
  }

  /* Checking if the file is open. If it is not, it prints an error message and exits the program. */
  if (filePtr == NULL) {
    printf("Error opening text file\n");
    return 0;
  }

  /* Reading a file and printing the contents of the file. */
  while (fgets(strToReadInput, sizeof(strToReadInput), filePtr)) {
    sscanf(strToReadInput, "%d %s %s %d %d", & inputVar, destinyVar, dateVar, & quantityVar, & typeVarInt);

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

  fclose(filePtr);
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
  FILE * filePtr = fopen("warehouse1.dat", "rb+");
  SLOT structBuffer;

  int countLine = 0;

  /* Checking if the file is open. If it is not, it prints an error message and exits the program. */
  if (filePtr == NULL) {
    printf("Error opening binary file\n");
    return 0;
  }

  /* Reading the binary file and printing the contents of the file. */
  while (fread( & structBuffer, sizeof(SLOT), 1, filePtr)) {
    leSlot( & structBuffer);

    /* Counting the number of slots that are occupied in the warehouse. */
    countLine = countLine + 1;
    int Shelf = countLine / 100;

    /* Printing the slot position and the shelf number in the warehouse */
    if ((structBuffer.flag == 1)) {
      print_NumToSlotPosition(countLine);
      printf(" Shelf: %d", Shelf);
    }

  }

  fclose(filePtr);

  return 0;
}

/**
 * It reads a binary file and prints the information of a specific ID
 * 
 * @return the value 0.
 */
int batchInfo() {

  /* Opening the file warehouse.dat in binary mode for reading and writing. */
  FILE * filePtr = fopen("warehouse.dat", "rb+");
  SLOT structBuffer;

  int userInputId;
  int countLine = 0;

  /* Asking the user to input an ID number. */
  printf("ID: ");
  scanf("%d", & userInputId);
  getchar();

  /* Opening a file and checking if it is NULL. If it is NULL, it will print an error message and exit. */
  if (filePtr == NULL) {
    printf("Error opening binary file\n");
    return 0;
  }

  /* Reading the file and printing the slot position and shelf number. */
  while (fread( & structBuffer, sizeof(SLOT), 1, filePtr)) {
    if (structBuffer.lote.id == userInputId) {
      leSlot( & structBuffer);

      countLine = countLine + 1;
      int Shelf = countLine / 100;

      print_NumToSlotPosition(countLine);
      printf(" Shelf: %d", Shelf);

      break;
    }

    /* Printing the shelf number and slot position. */

  }

  fclose(filePtr);

  return 0;
}

void printInputShelf(FILE * filePtr, SLOT structBuffer, int inputShelf, char inputStoreTempVar) {
  int currentRow = 0;
  int countAllCharParser = 0;

  printf("\n\n -----WAREHOUSE-----\n");
  printf(" 0 1 2 3 4 5 6 7 8 9");

  for (countAllCharParser = 0; fread( & structBuffer, sizeof(SLOT), 1, filePtr); countAllCharParser++) {

    if (inputShelf == 0) {
      if ((countAllCharParser > 89)) {
        break;
      }
    }

    if (inputShelf == 1) {

      if (countAllCharParser < 90) {
        continue;
      } else if ((countAllCharParser > 179)) {
        break;
      }
    }

    if (inputShelf == 2) {

      if (countAllCharParser < 180) {
        continue;
      } else if ((countAllCharParser > 269)) {
        break;
      }
    }

    if (inputShelf == 3) {

      if (countAllCharParser < 270) {
        continue;
      } else if ((countAllCharParser > 359)) {
        break;
      }
    }

    if (inputShelf == 4) {

      if (countAllCharParser < 360) {
        continue;
      } else if ((countAllCharParser > 449)) {
        break;
      }
    }

    if ((countAllCharParser % 9) == 0) {

      if (((currentRow % 10) == 0) && currentRow != 0) {
        printf("\n");
      }
      printf("\n");
      printf(" %d ", currentRow);
      currentRow += 1;

    }

    checkOccupancy( & structBuffer, & inputStoreTempVar);

    printf("%c ", inputStoreTempVar);

  }
}

/**
 * It reads the binary file, and prints out the contents of the file in a grid format
 * 
 * @return the number of slots that are occupied in the warehouse.
 */
int warehouseOccupancy() {

  /* Opening the file warehouse.dat in binary mode for reading and writing. */
  FILE * filePtr = fopen("warehouse.dat", "rb+");
  SLOT structBuffer;

  /* Declaring the variables that will be used in the program. */
  char inputStoreTemp = ' ';
  int userInputIntShelf;

  /* Asking the user to input the shelf number. */
  printf("Shelf: ");
  scanf("%d", & userInputIntShelf);
  getchar();

  /* Opening a file and checking if it is NULL. If it is NULL, it will print an error message and exit. */
  if (filePtr == NULL) {
    printf("Error opening binary file\n");
    return 0;
  }

  switch (userInputIntShelf) {
  case 0: //fazer função para isto tudo. usar   int shelf = printCurrentLine/10
    printInputShelf(filePtr, structBuffer, userInputIntShelf, inputStoreTemp);
    break;

  case 1:
    printInputShelf(filePtr, structBuffer, userInputIntShelf, inputStoreTemp);
    break;

  case 2:
    printInputShelf(filePtr, structBuffer, userInputIntShelf, inputStoreTemp);
    break;

  case 3:
    printInputShelf(filePtr, structBuffer, userInputIntShelf, inputStoreTemp);
    break;

  case 4:
    printInputShelf(filePtr, structBuffer, userInputIntShelf, inputStoreTemp);
    break;
  }
  return 0;
}

/*****************************************************************************************
 ************************************13 - 16 valores***************************************
 ******************************************************************************************/

int isIdInWarehouse(FILE * filePtrWarehouse, int ID) {
  filePtrWarehouse = fopen("warehouse.dat", "rb+");

  SLOT structBuffer;
  while (fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse)) {

    if ((structBuffer.lote.id) == ID) {
      return 1;
    }
  }
  return 0;

}

int saveTrayToWarehouse() {

  FILE * fpTray;
  FILE * filePtrWarehouse = fopen("warehouse.dat", "rb+");
  SLOT structBuffer;
  SLOT trayItemInput;

  char inputTrayName[100];
  char strToReadInput[60];
  int isIdRepeated = 0;

  getchar(); // Para apanhar o [enter]
  printf("Tray Filename: ");
  scanf("%s", inputTrayName);
  printf("\n");
  fpTray = fopen(inputTrayName, "r");

  if (fpTray == NULL) {
    printf("Error opening text file\n");
    return 0;
  }

  if (filePtrWarehouse == NULL) {
    printf("Error opening binary file\n");
    return 0;
  }

  int countWhenWritten = 0;
  while (fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse)) {
    if (structBuffer.flag == 1) {
      fwrite( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse);
      continue;
    }

    while (fgets(strToReadInput, sizeof(strToReadInput), fpTray)) {

      sscanf(strToReadInput, "%d %s %s %d %d", &
        trayItemInput.lote.id,
        trayItemInput.lote.destiny,
        trayItemInput.lote.date, &
        trayItemInput.lote.quantity, & trayItemInput.lote.type);

      isIdRepeated = isIdInWarehouse(filePtrWarehouse, trayItemInput.lote.id);

      if (isIdRepeated == 1) { //se o ID estiver no ficheiro
        printf("\nRepeated product Id: %d Discarting", trayItemInput.lote.id);
        continue;
      }

      if (isIdRepeated == 0) {
        countWhenWritten += 1;
        trayItemInput.flag = 1;
        fwrite( & trayItemInput, sizeof(SLOT), 1, filePtrWarehouse);
        printf("\nId: %d Tray: %d %d -> Slot: %d %d %d",
          trayItemInput.lote.id,
          countWhenWritten / 4,
          countWhenWritten % 4,
          countWhenWritten / 10, //row
          countWhenWritten % 10, //collum
          countWhenWritten / 100 //Shelf
        );

        break;
      }
    }

  }
  fclose(fpTray);
  fclose(filePtrWarehouse);

  return 0;
}

int swapBatch() {

  FILE * filePtrWarehouse = fopen("warehouse.dat", "rb+");
  SLOT structBuffer;

  SLOT structChosen;
  SLOT structToDisplace;

  int i;

  int inputID = 0;
  int inputRow = 0;
  int inputCollum = 0;
  int inputShelf = 0;

  int chosenPosition = 0;
  int positionIdFound = 0;

  if (filePtrWarehouse == NULL) {
    printf("Error opening binary file\n");
    return 0;
  }

  printf("Id: ");
  scanf("%d", & inputID);

  if (isIdInWarehouse(filePtrWarehouse, inputID) == 0) {
    printf("Batch Id not stored in warehouse");
    return 0;
  }

  printf("Row: ");
  scanf("%d", & inputRow);

  printf("Collum: ");
  scanf("%d", & inputCollum);

  printf("Shelf: ");
  scanf("%d", & inputShelf);

  chosenPosition = inputCollum + (inputRow * 10) + (inputShelf * 100);

  if (chosenPosition > 500) {
    printf("\nSuch position does not exist in the warehouse");
    return 0;
  }


  for (i = 1; fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse); i++) {
    if (structBuffer.lote.id == inputID) {
      structChosen = structBuffer;
      positionIdFound = i;
      break;
    }
  }

  
  printf("\n\n== Position found %d==\n\n", positionIdFound);

  printf("%d %s %s %d %d",
    structChosen.lote.id,
    structChosen.lote.destiny,
    structChosen.lote.date,
    structChosen.lote.quantity,
    structChosen.lote.type
  );


  for (i = 1; fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse); i++) {
    if (i == chosenPosition) {
      structToDisplace = structBuffer;
      //positionIdFound = i;
      break;
    }
  }

  printf("\n\n== Position found %d==\n\n", chosenPosition);

  printf("%d %s %s %d %d",
    structToDisplace.lote.id,
    structToDisplace.lote.destiny,
    structToDisplace.lote.date,
    structToDisplace.lote.quantity,
    structToDisplace.lote.type
  );



  FILE * filePtrTest = fopen("warehouse1.dat", "wb+");

  for (i = 0; fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse); i++) {

    if (i == chosenPosition) {
      fwrite( & structToDisplace, sizeof(SLOT), 1, filePtrTest);
      continue;
    } else if (i == positionIdFound) {
      fwrite( & structChosen, sizeof(SLOT), 1, filePtrTest);
      continue;
    }else{
      fwrite( & structBuffer, sizeof(SLOT), 1, filePtrTest);
    }
  }

  fclose(filePtrWarehouse);
  fclose(filePtrTest);

  return 0;
}
/*****************************************************************************************
 ************************************16 - 18 valores***************************************
 ******************************************************************************************/

typedef struct warehouseStatistics {
  int totalCartoes;
  int totalLivretes;
  int ocupado;
  int apperances;
  char destino[12];
}
CITYVALUES;

int estatisticas() {

  FILE * filePtrWarehouse = fopen("warehouse.dat", "rb+");
  SLOT structBuffer;
  CITYVALUES destinos[NUM_DISTRITOS_CONTINENTAL];

  int i;
  int index = 0;
  int isItRepeated;
  int positionFound = 0;

  int maxNumProduct = 0;
  int currentTotalNumProduct = 0;
  float histogramRatio = 0;

  for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) { //inicializar
    destinos[i].apperances = 0;
    destinos[i].totalCartoes = 0;
    destinos[i].totalLivretes = 0;
  }

  if (filePtrWarehouse == NULL) {
    printf("Error opening binary file\n");
    return 0;
  }

  while (fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse)) {
    isItRepeated = 0;
    if (structBuffer.flag == 0) {
      continue;
    }
    if (!(isnull(structBuffer.lote.destiny)) && (structBuffer.flag)) {

      for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
        if (!strcmp(destinos[i].destino, structBuffer.lote.destiny)) {
          positionFound = i;
          destinos[positionFound].apperances = destinos[positionFound].apperances + 1;

          if (structBuffer.lote.type == 1) { //cartoes
            destinos[positionFound].totalCartoes = destinos[positionFound].totalCartoes + structBuffer.lote.quantity;
            isItRepeated = 1;
            break;
          }

          if (structBuffer.lote.type == 2) { //livretes
            destinos[positionFound].totalLivretes = destinos[positionFound].totalLivretes + structBuffer.lote.quantity;
            isItRepeated = 1;
            break;
          }
        }
      }
      if (isItRepeated == 1) {
        continue;
      }

      strcpy(destinos[index].destino, structBuffer.lote.destiny);
      destinos[index].apperances = destinos[index].apperances + 1;
      destinos[index].ocupado = 1;

      if (structBuffer.lote.type == 1) { //cartoes
        destinos[index].totalCartoes = destinos[index].totalCartoes + structBuffer.lote.quantity;
      }

      if (structBuffer.lote.type == 2) { //livretes
        destinos[index].totalLivretes = destinos[index].totalLivretes + structBuffer.lote.quantity;
      }
      index = index + 1;

    }

  }

  fclose(filePtrWarehouse);

  for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
    if (destinos[i].ocupado == 1) {
      printf("%-12s  Total: %-5d     Cartao: %-5d     Livrete: %d\n",
        destinos[i].destino,
        destinos[i].apperances,
        destinos[i].totalCartoes,
        destinos[i].totalLivretes);
    }
  }

  for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
    if (destinos[i].ocupado == 1) {
      currentTotalNumProduct = destinos[i].totalCartoes + destinos[i].totalLivretes;
      if (currentTotalNumProduct > maxNumProduct) {
        maxNumProduct = currentTotalNumProduct;
      }
    }
  }
  histogramRatio = (maxNumProduct / 50);

  int j;
  for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
    if (destinos[i].ocupado == 1) {
      currentTotalNumProduct = destinos[i].totalCartoes + destinos[i].totalLivretes;
      printf("\n%-10s  Quantidade total: %-5d    :", destinos[i].destino, currentTotalNumProduct);
      for (j = 0; j < (currentTotalNumProduct / histogramRatio); j++) {
        printf("*");
      }
    }
  }
  return 0;

}

/**
 * It prints a menu
 */

void showMenu() {

  printf("\n\n1 - Show tray\n");

  printf("2 - List batches \n");
  printf("3 - Show batch info \n");
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

  FILE * filePtr;
  filePtr = fopen("warehouse.dat", "rb");
  if (filePtr == NULL) {
    printf("Error opening binary file\n");
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
      batchInfo();
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
      swapBatch();
      showMenu();
      break;
    case '7':
      estatisticas();
      showMenu();
      break;
    case '8':

      break;
    case 'e':
      fclose(filePtr);
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