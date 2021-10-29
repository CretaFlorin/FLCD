#include <iostream>
#include "symboltable.h"


int main()
{
    SymbolTable St = SymbolTable(13); 

    St.add("haha");
    St.add("ahah");
    St.add("hhaa");
    St.add("abcdefgh");
    St.add("a");
    St.add("bb");
    St.add("t");
    St.add("er");
    St.add("et");
    St.add("tert");
    St.add("teurt");
    St.add("teirt");
    St.add("tert");
    St.add("aa");
    St.add("aa");
    St.add("aa");

    St.remove("a");
    St.remove("tert");

    St.details();

    return 0;
}
