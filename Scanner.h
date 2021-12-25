#include <string>
#include <vector>
#include "SymbolTable.h"

using namespace std;

class Scanner {
    private:
        enum TokenType {
            Separator,
            Operator,
            ReservedWord,
            Constant,
            Identifier
        };
        vector<string> Operators;                 
        vector<string> Separators;
        vector<string> ReservedWords;
        vector<pair<string, TokenType>> PIF;
        string WorkingFolder;
        SymbolTable St;

    public:
    
    void details();

    // constructor
    Scanner(string TokenPath, string WorkingFolder);

    void writePIF();
    void writeSymbolTable();

    void scan(string ProgramPath);
};