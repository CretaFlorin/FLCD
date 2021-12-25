#include "FiniteAutomata.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void FiniteAutomata::details()
{
    cout << "M = (Q, Sigma, Ro, " << this->InitialState << ", F)\n";

    cout << "Q = {";
    for (int i = 0; i < this->States.size() - 1; i++)
        cout << this->States[i] << ", ";
    cout << this->States[this->States.size() - 1];
    cout << "}\n";

    cout << "Sigma = {";
    for (int i = 0; i < this->Alphabet.size() - 1; i++)
        cout << this->Alphabet[i] << ", ";
    cout << this->Alphabet[this->Alphabet.size() - 1];
    cout << "}\n";

    for (auto transition : this->Transitions)
        cout << "Ro(" << transition.first.first << ", " << transition.first.second << ") = " << transition.second << "\n";

    cout << "F = {";
    for (int i = 0; i < this->FinalStates.size() - 1; i++)
        cout << this->FinalStates[i] << ", ";
    cout << this->FinalStates[this->FinalStates.size() - 1];
    cout << "}\n";
}

FiniteAutomata::FiniteAutomata(string FAElementsPath)
{
    ifstream fin(FAElementsPath);

    ElementType type;
    string element;

    while (getline(fin, element))
    {
        if (element == "STATES")
            type = ElementType::STATE;
        else if (element == "INITIAL_STATE")
            type = ElementType::INITIAL_STATE;
        else if (element == "ALPHABET")
            type = ElementType::ALPHABET;
        else if (element == "TRANSITIONS")
            type = ElementType::TRANSITION;
        else if (element == "FINAL_STATES")
            type = ElementType::FINAL_STATE;
        else
        {
            if (type == ElementType::STATE)
                this->States.push_back(element);
            if (type == ElementType::INITIAL_STATE)
                this->InitialState = element;
            if (type == ElementType::ALPHABET)
                this->Alphabet.push_back(element);
            if (type == ElementType::TRANSITION)
            {
                string state1 = element.substr(0, element.find(','));
                element.erase(0, element.find(',') + 1);

                string weigth = element.substr(0, element.find(','));
                string state2 = element.erase(0, element.find(',') + 1);

                this->Transitions.push_back(make_pair(make_pair(state1, weigth[0]), state2));
            }
            if (type == ElementType::FINAL_STATE)
                this->FinalStates.push_back(element);
        }
    }
}

bool FiniteAutomata::verify(string word)
{
    string currentState = this->InitialState;
    char character;

    while (word.size() > 0)
    {
        character = word[0];
        word = word.substr(1, word.size());

        bool found = false;
        for (auto transition : this->Transitions)
        {
            if (transition.first.first == currentState && transition.first.second == character)
            {
                cout << currentState;
                currentState = transition.second;
                found = true;

                break;
            }
        }
        if(found == false)
            return false;

        cout  << " -> " << character << " -> " << currentState << endl;
    }

    for (auto state : this->FinalStates)
        if (currentState == state)
            return true;

    return false;
}
