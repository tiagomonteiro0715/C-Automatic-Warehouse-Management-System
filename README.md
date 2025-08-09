# Automatic Warehouse Management System

Final Project from the class "Microprocessor programming"

Final project grade of 17 out of 20

This project is a C-based Automatic Warehouse Management System designed to handle inventory lots in a warehouse. 

It manages storage slots, tracks product information such as lot ID, destination, expiration date, quantity, and product type, and provides tools for visualizing the warehouse trays.

### Features

- Representation of warehouse lots with detailed attributes (ID, destination, expiration date, quantity, product type).

- Management of warehouse slots and occupancy status.

- Functions to convert product type codes to meaningful names.

- Display functionality to visualize warehouse trays from data files.

- Reading and parsing tray data from text files to monitor warehouse state.

### Main Functions

- convertNumToType(int num, int fullName): Converts numerical codes to product types.

- leLote(loteCompleto lot): Prints details of a lot.

- leSlot(slot s): Prints details of a slot if occupied.

- checkOccupancy(slot s): Returns occupancy symbol for a slot.

- print_NumToSlotPosition(int num): Converts a number to a slot position in a 10x10 grid.

- showTray(char* filename): Reads and displays tray data from a file.

### Requirements

    C Compiler (e.g., gcc)

### Usage

    Compile the program:
```
gcc -o warehouse final.c
```
Run the executable:
```
    ./warehouse
```

### File Format

warehouse.dat files should contain:

        Slot number

        Lot ID

        Destination

        Expiration date

        Quantity

        Product type (numerical code)

### Author

Tiago Monteiro

- GitHub: @tiagomonteiro0715
- LinkedIn: [Tiago Monteiro](https://www.linkedin.com/in/tiago-monteiro-/)
