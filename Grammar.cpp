#include "Grammar.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void Grammar::details()
{
    cout << "G = (N, Sigma, P, " << this->Start_Symbol << ")\n";

    cout << "N = {";
    this->print_Non_Terminals();
    cout << "}\n";

    cout << "Sigma = {";
    this->print_Terminals();
    cout << "}\n";

    cout << "P:\n";
    this->print_Transformations();
}

void Grammar::print_Non_Terminals()
{
    for (int i = 0; i < this->Non_Terminals.size() - 1; i++)
        cout << this->Non_Terminals[i] << ", ";
    cout << this->Non_Terminals[this->Non_Terminals.size() - 1];
}

void Grammar::print_Terminals()
{
    for (int i = 0; i < this->Terminals.size() - 1; i++)
        cout << this->Terminals[i] << ", ";
    cout << this->Terminals[this->Terminals.size() - 1];
}

void Grammar::print_Transformations()
{
    for (auto transformation : this->Transformations)
        cout << transformation.first << " -> " << transformation.second << "\n";
}

Grammar::Grammar(string GrammarElementsPath)
{
    ifstream fin(GrammarElementsPath);

    ElementType type;
    string element;

    while (getline(fin, element))
    {
        if (element == "NON_TERMINAL")
            type = ElementType::NON_TERMINAL;
        else if (element == "TERMINAL")
            type = ElementType::TERMINAL;
        else if (element == "RULES")
            type = ElementType::TRANSFORMATION;
        else if (element == "START")
            type = ElementType::START_SYMBOL;
        else
        {
            if (type == ElementType::NON_TERMINAL)
                this->Non_Terminals.push_back(element);
            if (type == ElementType::TERMINAL)
                this->Terminals.push_back(element);
            if (type == ElementType::START_SYMBOL)
                this->Start_Symbol = element;
            if (type == ElementType::TRANSFORMATION)
            {
                string terminal = element.substr(0, element.find(" -> "));
                string transformation_output = element.erase(0, element.find(" -> ") + 4);
                this->Transformations.push_back(make_pair(terminal, transformation_output));
            }
        }
    }
}
