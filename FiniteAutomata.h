#include <string>
#include <vector>

using namespace std;

class FiniteAutomata {
    private:
        enum ElementType {
            STATE,
            INITIAL_STATE,
            FINAL_STATE,
            ALPHABET,
            TRANSITION
        };
        vector<string> States;                 
        string InitialState;
        vector<string> FinalStates;
        vector<string> Alphabet;
        vector<pair<pair<string, char>, string>> Transitions;

    public:
    
    void details();

    // constructor
    FiniteAutomata(string FAElementsPath);

    bool verify(string word);
};