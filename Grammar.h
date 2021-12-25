#include <string>
#include <vector>

using namespace std;

class Grammar
{
private:
    enum ElementType
    {
        NON_TERMINAL,
        TERMINAL,
        TRANSFORMATION,
        START_SYMBOL
    };
    vector<string> Non_Terminals;
    vector<string> Terminals;
    vector<pair<string, string>> Transformations;
    string Start_Symbol;

public:
    void details();

    void print_Non_Terminals();
    void print_Terminals();
    void print_Transformations();
    void print_Transformations_Of();

    // GETTERS & SETTERS

    vector<string> get_Non_Terminals() { return this->Non_Terminals; }
    vector<string> get_Terminals() { return this->Terminals; }
    vector<pair<string, string>> get_Transformations() { return this->Transformations; }
    string get_Start_Symbol() { return this->Start_Symbol; }


    // constructor
    Grammar(string GrammarElementsPath);
};