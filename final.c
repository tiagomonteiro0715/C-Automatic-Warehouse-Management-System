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
  unsigned int id;//4 bytes
  char destiny[MAX_DESTINY_STR];//30 bytes
  char date[MAX_DATE_STR];//12 bytes
  unsigned int quantity;//4 bytes
  unsigned int type;//4 bytes
}LOTE;

typedef struct slot {
  LOTE;//4 bytes
  unsigned int flag;//0 - livre || 1 - ocupado
}SLOT;

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

void le_lote(SLOT * ptr) {
  printf("\n\n id: %u destiny:%s date:%s quantity:%u type:%u",
    ( * ptr).id,
    ( * ptr).destiny,
    ( * ptr).date,
    ( * ptr).quantity,
    ( * ptr).type
  );
}

void le_slot(SLOT * ptr) {
  le_lote(ptr);
  printf(" flag:%u\n",
    ( * ptr).flag

  );
}
//-----------------------------------------------------------------------------------------------------------

int showTray(bool override) {
  char inputTray[100];
  int testingVar;
  FILE * fp;
  char str[60];
  int i = 0;

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

  FILE * fp = fopen("warehouse.dat", "rb+");
  SLOT slot;
  if (fp == NULL) {
    printf("Error opening text file\n");
    exit(1);
  }

	while(fread(&slot, sizeof(SLOT), 1, fp)){
		le_slot(&slot);
  }

  fclose(fp);
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


    //https://www.geeksforgeeks.org/how-to-avoid-structure-padding-in-c/
     //https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/
     //https://www.javatpoint.com/structure-padding-in-c
     //https://www.educba.com/structure-padding-in-c/

/*
void reading(){
  FILE * fp = fopen("warehouse.dat", "rb");

  if (fp == NULL) {
    printf("Error opening text file\n");
    exit(1);
  }

  LOTE * buff = malloc(sizeof(LOTE));

  while (1) {
    fread(&buff, sizeof(buff), 1, fp);
    if(feof(fp)) {
      break;
    }

    printf("\nid: %u", buff->id);
    printf("\ndestiny: %s", buff->destiny);
    printf("\ndate: %s", buff->date);
    printf("\nquantity: %u", buff->quantity);
    printf("\ntype: %u", buff->type);
    printf("\n");
  }
  printf("\nFinished\n");

  free(buff); 

  fclose(fp);

}
*/
/*
  while (1) {
    fread(&book, sizeof(book), 1, fp);
    if(feof(fp)) {
      break;
    }

    printf("\nTitle: %s", book.title);
    printf("\nAuthor: %s", book.author);
    printf("\nPublisher: %s", book.publisher);
    printf("\nPrice: %.2f", book.price);
    printf("\n");
  }
  printf("\nFinished\n");

  fclose(fp);
  return 0;
}
*/

/*
void reading(){
  FILE * fp = fopen("warehouse.dat", "rb");

  if (fp == NULL) {
    printf("Error opening text file\n");
    exit(1);
  }
  LOTE * buff = malloc(sizeof(LOTE));
  size_t varTest;

    fread(&buff->id, sizeof(buff->id), 1, fp);
    fread(&buff->destiny, sizeof(buff->destiny), 1, fp);
    fread(&buff->date, sizeof(buff->date), 1, fp);
    fread(&buff->quantity, sizeof(buff->quantity), 1, fp);
    fread(&buff->type, sizeof(buff->type), 1, fp);
    printf("%u %s %s %u %u\n", buff->id, buff->destiny, buff->date, buff->quantity, buff->type);

  //free(buff); free whatever you allocated after finished using them 

  //fclose(fp);

//}
*/