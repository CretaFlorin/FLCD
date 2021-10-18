#ifndef SymbolTable_h
#define SymbolTable_h
#include "sll.h"


typedef struct SymbolTable {
    SLL** T;  
    int m;     
} SymbolTable;


SymbolTable* CreateSymbolTable(int dim);

int Hash(SymbolTable* ht, int key);

void printSymbolTable(SymbolTable* ht);


void addKey(SymbolTable* ht, int key);

void removeKey(SymbolTable* ht, int key);

int searchKey(SymbolTable* ht, int key);


#endif // SymbolTable_h
