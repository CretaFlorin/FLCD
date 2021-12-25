#include <iostream>
#include "SymbolTable.h"
#include "Scanner.h"
#include "FiniteAutomata.h"
#include "DescendentRecursiveParser.h"

int main()
{
    // Scanner Scn("files/tokens.in", "temp");

    // Scn.scan("files/p3.txt");

    // Scn.writePIF();
    // Scn.writeSymbolTable();

    // Scn.details();
    
    // FiniteAutomata FA("files/FA.in");

    // FA.details();

    // cout << "010\n" << FA.verify("010") << endl << endl;
    // cout << "1\n" << FA.verify("1") << endl << endl;
    // cout << "0001\n" << FA.verify("0001") << endl << endl;
    // cout << "01100\n" << FA.verify("01100") << endl << endl;
    // cout << "10##0##\n" << FA.verify("10##0##") << endl << endl;
    // cout << "0#01#0#\n" << FA.verify("0#01#0#");

    Grammar G("files/G1.in");

    // G.details();

    DescendentRecursiveParser Parser(G);
    
    // Parser.test();    
    Parser.parse("aacbb");


    return 0;
}
