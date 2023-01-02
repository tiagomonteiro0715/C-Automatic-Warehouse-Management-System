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
  int flag; //0 - livre || 1 - occupied
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

  /* Opening the file and checking if it is null. */
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
  FILE * filePtr = fopen("warehouse.dat", "rb+");
  SLOT structBuffer;

  int countLine = 0;

  /* Opening a file and checking if it is null. */
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

  /* Opening a file and checking if it is null. */
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

/**
 * It reads the file, and prints the contents of the file to the screen.
 * 
 * @param filePtr pointer to the file
 * @param structBuffer a struct that holds the data from the file
 * @param inputShelf 0-4
 * @param inputStoreTempVar This is a char variable that is used to store the value of the slot's
 * occupancy.
 */
void printInputShelf(FILE * filePtr, SLOT structBuffer, int inputShelf, char inputStoreTempVar) {
  int currentRow = 0;
  int countAllCharParser = 0;

  printf("\n\n -----WAREHOUSE-----\n");
  printf(" 0 1 2 3 4 5 6 7 8 9");

  /* The above code is parsing the file and printing the contents of the file. */
  for (countAllCharParser = 0; fread( & structBuffer, sizeof(SLOT), 1, filePtr); countAllCharParser++) {

    /* Checking if the inputShelf is 0, and if it is, it is checking if the countAllCharParser is greater
    than 89. If it is, it breaks. */
    if (inputShelf == 0) {
      if ((countAllCharParser > 89)) {
        break;
      }
    }

    /* Checking if the inputShelf is 1, and if it is, it is checking if the countAllCharParser is less than
    90. If it is, it continues. If it is not, it checks if the countAllCharParser is greater than 179.
    If it is, it breaks. If it is not, it does nothing. */
    if (inputShelf == 1) {

      if (countAllCharParser < 90) {
        continue;
      } else if ((countAllCharParser > 179)) {
        break;
      }
    }

    /* Checking if the inputShelf is 2, and if it is, it is checking if the countAllCharParser is less than
    180. If it is, it continues. If it is not, it checks if the countAllCharParser is greater than 269.
    If it is, it breaks. If it is not, it continues. */
    if (inputShelf == 2) {

      if (countAllCharParser < 180) {
        continue;
      } else if ((countAllCharParser > 269)) {
        break;
      }
    }

    /* Checking if the inputShelf is 3, and if it is, it is checking if the countAllCharParser is less than
    270, and if it is, it continues. If it is not, it checks if the countAllCharParser is greater than
    359, and if it is, it breaks. */
    if (inputShelf == 3) {

      if (countAllCharParser < 270) {
        continue;
      } else if ((countAllCharParser > 359)) {
        break;
      }
    }

    /* Checking if the inputShelf is 4, and if it is, it is checking if the countAllCharParser is less than
    360. If it is, it continues. If it is not, it checks if the countAllCharParser is greater than 449.
    If it is, it breaks. If it is not, it continues. */
    if (inputShelf == 4) {

      if (countAllCharParser < 360) {
        continue;
      } else if ((countAllCharParser > 449)) {
        break;
      }
    }

    /* Printing the row number. */
    if ((countAllCharParser % 9) == 0) {

      /* Printing a new line every 10 rows. */
      if (((currentRow % 10) == 0) && currentRow != 0) {
        printf("\n");
      }
      /* Printing the current row number. */
      printf("\n");
      printf(" %d ", currentRow);
      currentRow += 1;

    }

    /* Checking the occupancy of the structBuffer and inputStoreTempVar. */
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

  /* Printing the input shelf. */
  switch (userInputIntShelf) {
  case 0:
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

/**
 * It opens a file, reads a record, compares the record's ID to the ID passed to the function, and
 * returns 1 if the IDs match, or 0 if they don't
 * 
 * @param filePtrWarehouse pointer to the warehouse file
 * @param ID
 * 
 * @return the value of the variable "structBuffer.lote.id"
 */
int isIdInWarehouse(FILE * filePtrWarehouse, int ID) {

  /* Opening the file warehouse.dat in read and write mode. */
  filePtrWarehouse = fopen("warehouse.dat", "rb+");

  /* Reading the file and checking if the ID is in the file. */
  SLOT structBuffer;
  while (fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse)) {

    /* Checking if the ID of the lote is the same as the ID of the lote that is being searched for. */
    if ((structBuffer.lote.id) == ID) {
      return 1;
    }
  }
  return 0;
}

/**
 * It reads a text file with a list of products and writes them to a binary file
 * 
 * @return the value 0.
 */
int saveTrayToWarehouse() {

  /* Opening the file warehouse.dat and reading it into a buffer. */
  FILE * fpTray;
  FILE * filePtrWarehouse = fopen("warehouse.dat", "rb+");
  SLOT structBuffer;
  SLOT trayItemInput;

  /* Declaring a variable of type char and assigning a value to it. */
  char inputTrayName[100];
  char strToReadInput[60];
  int isIdRepeated = 0;

  /* Opening the file for reading. */
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

  /* Reading the file and writing it to another file. */
  int countWhenWritten = 0;
  while (fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse)) {

    /* Writing the structBuffer to the filePtrWarehouse. */
    if (structBuffer.flag == 1) {
      fwrite( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse);
      continue;
    }

    /* Reading the file and writing it to another file. */
    while (fgets(strToReadInput, sizeof(strToReadInput), fpTray)) {

      /* Reading the input from the file and storing it in the struct. */
      sscanf(strToReadInput, "%d %s %s %d %d", &
        trayItemInput.lote.id,
        trayItemInput.lote.destiny,
        trayItemInput.lote.date, &
        trayItemInput.lote.quantity, & trayItemInput.lote.type);

      /* Checking if the ID is repeated in the file. */
      isIdRepeated = isIdInWarehouse(filePtrWarehouse, trayItemInput.lote.id);
      if (isIdRepeated == 1) { //se o ID estiver no ficheiro
        printf("\nRepeated product Id: %d Discarting", trayItemInput.lote.id);
        continue;
      }

      /* Checking if the id is repeated. If it is not repeated, it will write the trayItemInput to the file. */
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
  /* Closing the file pointers. */
  fclose(fpTray);
  fclose(filePtrWarehouse);

  return 0;
}

/**
 * It's supposed to swap two slots in a binary file
 * 
 * @return the value 0.
 */
int swapBatch() {

  /* Declaring variables and opening the file. */
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

  /* Checking if the inputID is in the warehouse. */
  printf("Id: ");
  scanf("%d", & inputID);
  if (isIdInWarehouse(filePtrWarehouse, inputID) == 0) {
    printf("Batch Id not stored in warehouse");
    return 0;
  }

  /* Asking the user to input the row, collum and shelf. */
  printf("Row: ");
  scanf("%d", & inputRow);

  printf("Collum: ");
  scanf("%d", & inputCollum);

  printf("Shelf: ");
  scanf("%d", & inputShelf);

  /* Checking if the position is greater than 500. */
  chosenPosition = inputCollum + (inputRow * 10) + (inputShelf * 100);
  if (chosenPosition > 500) {
    printf("\nSuch position does not exist in the warehouse");
    return 0;
  }

  /* Reading the file and storing the data in a buffer. */
  for (i = 0; fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse); i++) {
    if (structBuffer.lote.id == inputID) {
      structChosen = structBuffer;
      positionIdFound = i;
    }

    if (i == chosenPosition) {
      structToDisplace = structBuffer;
    }
  }

  /* Checking if the user has chosen the same position as the one found. If so, it will print a message
  and return 0. If not, it will print a message. */
  if (chosenPosition == positionIdFound) {
    printf("\nYou choose with same slots. Please try again");
    return 0;
  } else {
    printf("\n\n Switch slot (%d %s %s %d %d) with slot (%d %s %s %d %d) \n\n",
      structChosen.lote.id,
      structChosen.lote.destiny,
      structChosen.lote.date,
      structChosen.lote.quantity,
      structChosen.lote.type,

      structToDisplace.lote.id,
      structToDisplace.lote.destiny,
      structToDisplace.lote.date,
      structToDisplace.lote.quantity,
      structToDisplace.lote.type);
  }

  /* Reading the file and writing it back to the file. */
  while (fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse)) {

    /* Writing the structBuffer to the filePtrWarehouse. */
    fwrite( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse);
    if (i == chosenPosition) {
      fwrite( & structChosen, sizeof(SLOT), 1, filePtrWarehouse);
    } else if (i == positionIdFound) {
      fwrite( & structToDisplace, sizeof(SLOT), 1, filePtrWarehouse);
    } else {
      fwrite( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse);
    }

    i = i + 1;
  }

  /* Opening a file and reading the data from it. */
  fclose(filePtrWarehouse);

  return 0;
}
/*****************************************************************************************
 ************************************16 - 18 valores***************************************
 ******************************************************************************************/

/**
 * CITYVALUES is a type that contains a bunch of integers and a character array.
 * @property {int} totalcards - The number of cards that are in the warehouse to the destiny
 * @property {int} totalBooklets - The total number of booklets that will be sent to the city.
 * @property {int} occupied - Indicating that this city has cards and booklets to send to a city
 * @property {int} apperances - How many times the city has appeared in the warehouse.
 * @property {char} finalDestiny - The name of the city to be sent
 */
typedef struct warehouseStatistics {
  int totalcards;
  int totalBooklets;
  int occupied;
  int apperances;
  char finalDestiny[12];
}
CITYVALUES;

/**
 * It reads a binary file and prints some statistics about it
 * 
 * @return the number of products in the warehouse.
 */
int estatisticas() {

  /* Opening a file, creating a structure, and creating an array of structures. */
  FILE * filePtrWarehouse = fopen("warehouse.dat", "rb+");
  SLOT structBuffer;
  CITYVALUES finalDestinys[NUM_DISTRITOS_CONTINENTAL];

  /* Declaring the variables that will be used in the program. */
  int i;
  int index = 0;
  int isItRepeated;
  int positionFound = 0;

  int maxNumProduct = 0;
  int currentTotalNumProduct = 0;
  float histogramRatio = 0;

  /* Initializing the array of structs. */
  for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
    finalDestinys[i].apperances = 0;
    finalDestinys[i].totalcards = 0;
    finalDestinys[i].totalBooklets = 0;
  }

  if (filePtrWarehouse == NULL) {
    printf("Error opening binary file\n");
    return 0;
  }

  /* Reading a file and storing the data in an array of structs. */
  while (fread( & structBuffer, sizeof(SLOT), 1, filePtrWarehouse)) {
    isItRepeated = 0;

    /* Checking if the flag is set to 0. If it is, it will skip the rest of the code and go to the next
    iteration of the loop. */
    if (structBuffer.flag == 0) {
      continue;
    }

    /* Reading the file and storing the data in an array of structs. */
    if (!(isnull(structBuffer.lote.destiny)) && (structBuffer.flag)) {

      /* Checking if the finalDestiny is already in the array. If it is, it increments the apperances and
      adds the quantity to the totalcards or totalBooklets. */
      for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
        if (!strcmp(finalDestinys[i].finalDestiny, structBuffer.lote.destiny)) {
          positionFound = i;
          finalDestinys[positionFound].apperances = finalDestinys[positionFound].apperances + 1;

          /* Checking if the type of the lot is 1, if it is, it is adding the quantity of the lot to the
          totalcards of the finalDestinys array. */
          if (structBuffer.lote.type == 1) { //cartoes
            finalDestinys[positionFound].totalcards = finalDestinys[positionFound].totalcards + structBuffer.lote.quantity;
            isItRepeated = 1;
            break;
          }

          /* Checking if the type of the structBuffer is 2, if it is, it is adding the quantity of the
          structBuffer to the totalBooklets of the finalDestinys. */
          if (structBuffer.lote.type == 2) { //livretes
            finalDestinys[positionFound].totalBooklets = finalDestinys[positionFound].totalBooklets + structBuffer.lote.quantity;
            isItRepeated = 1;
            break;
          }
        }
      }
      /* Checking if the number is repeated. If it is, it will continue to the next number. */
      if (isItRepeated == 1) {
        continue;
      }

      /* Adding the data to the array of structs. */
      strcpy(finalDestinys[index].finalDestiny, structBuffer.lote.destiny);
      finalDestinys[index].apperances = finalDestinys[index].apperances + 1;
      finalDestinys[index].occupied = 1;

      /* Adding the quantity of cards and booklets to the finalDestinys array. */
      if (structBuffer.lote.type == 1) {
        finalDestinys[index].totalcards = finalDestinys[index].totalcards + structBuffer.lote.quantity;
      }

      if (structBuffer.lote.type == 2) {
        finalDestinys[index].totalBooklets = finalDestinys[index].totalBooklets + structBuffer.lote.quantity;
      }
      index = index + 1;

    }

  }

  fclose(filePtrWarehouse);

  /* Printing the finalDestinys array. */
  for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
    if (finalDestinys[i].occupied == 1) {
      printf("%-12s  Total: %-5d     Cartao: %-5d     Livrete: %d\n",
        finalDestinys[i].finalDestiny,
        finalDestinys[i].apperances,
        finalDestinys[i].totalcards,
        finalDestinys[i].totalBooklets);
    }
  }

  /* Printing a histogram of the number of products in each final destination. */
  for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
    if (finalDestinys[i].occupied == 1) {
      currentTotalNumProduct = finalDestinys[i].totalcards + finalDestinys[i].totalBooklets;
      if (currentTotalNumProduct > maxNumProduct) {
        maxNumProduct = currentTotalNumProduct;
      }
    }
  }
  histogramRatio = (maxNumProduct / 50);

  for (i = 0; i < NUM_DISTRITOS_CONTINENTAL; i++) {
    /* Printing the histogram. */
    if (finalDestinys[i].occupied == 1) {
      currentTotalNumProduct = finalDestinys[i].totalcards + finalDestinys[i].totalBooklets;
      printf("\n%-10s  Quantidade total: %-5d    :", finalDestinys[i].finalDestiny, currentTotalNumProduct);
      /* Printing out each line of astericks. */
      for (int j = 0; j < (currentTotalNumProduct / histogramRatio); j++) {
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