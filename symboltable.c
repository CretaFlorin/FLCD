#include <stdlib.h>
#include <stdio.h>
#include "SymbolTable.h"


SymbolTable* CreateSymbolTable(int dim)
{
    SymbolTable* ht = (SymbolTable*)malloc(sizeof(SymbolTable));
    ht->T = (SLL**)malloc(dim * sizeof(SLL*));     
    ht->m = dim;                                     
    int i = 0;
    for(i; i < ht->m; i++)                          
        ht->T[i] = createSLL();
    return ht;                                    
}


int Hash(SymbolTable* ht, int key)
{
    return key % ht->m;                              
}


void printSymbolTable(SymbolTable* ht)
{
    printf("--- SymbolTable ---\n");
    int i = 0;
    for(i; i < ht->m; i++)
    {
        printf("%d: ", i);
        print(ht->T[i]);
    }
}


void addKey(SymbolTable* ht, int key)
{
    addToEnd(ht->T[Hash(ht, key)], key);
}


void removeKey(SymbolTable* ht, int key)
{
    removeElement(ht->T[Hash(ht, key)], key);
}


int searchKey(SymbolTable* ht, int key)
{
    return search(ht->T[Hash(ht, key)], key);
}
