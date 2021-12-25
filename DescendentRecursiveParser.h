#include "Grammar.h"
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

class DescendentRecursiveParser
{
private:
    enum State
    {
        NORMAL, // q
        BACK,   // b
        FINAL,  // f
        ERROR   // e
    };
    State state;
    int i; //position of current symbol in input sequence
    vector<string> working_stack;
    stack<string> input_stack;
    map<string, vector<pair<string, string>>> rules;
    Grammar *grammar;

    string stack_toString(stack<string>);
    string state_toString(State);
    string vector_toString(vector<string> vct);


    bool isNonTerminal(string);

    void Success();
    void Expand();
    void Advance();
    void MomentaryInsuccess();
    void Back();
    void AnotherTry();
    void BuildStringOfProd(vector<string>);

public:
    void details();

    // constructor
    DescendentRecursiveParser(Grammar grammar);

    void parse(string word);
    void test();
};