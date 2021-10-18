#include <stdio.h>
#include <stdlib.h>
#include "symboltable.h"


int main()
{
    SymbolTable* St = CreateSymbolTable(8); 

    addKey(St, 16);
    addKey(St, 11);
    addKey(St, 22);
    addKey(St, 6);
    addKey(St, 27);
    addKey(St, 19);
    printSymbolTable(St);

    removeKey(St, 19);
    printSymbolTable(St);

    printf("%d", searchKey(St, 19));

    return 0;
}
