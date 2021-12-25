#include "Scanner.h"
#include <fstream>
#include <iostream>
#include <streambuf>
#include <iomanip>

#define INITIAL_CAPACITY 13


using namespace std;


void Scanner::details()
{
    cout << "--------------- Scanner ---------------\n";
    cout << "OPERATORS:\n";
    for(int i = 0; i < this->Operators.size(); i++)
        cout << "'" << this->Operators[i] << "'\n";

    cout << "SEPARATORS:\n";
    for(int i = 0; i < this->Separators.size(); i++)
        if(this->Separators[i] != "\n")
            cout << "'" << this->Separators[i] << "'\n";
        else 
            cout << "'\\n'\n";

    cout << "RESERVED WORDS:\n";
    for(int i = 0; i < this->ReservedWords.size(); i++)
        cout << "'" << this->ReservedWords[i] << "'\n";

    cout << "---- PIF ----\n";
    for(int i = 0; i < this->PIF.size(); i++)
    {
        cout << "'" << this->PIF[i].first << "' - ";
        switch (PIF[i].second)
        {
            case TokenType::Constant :
                cout << "Constant\n";
                break;
            case TokenType::Identifier :
                cout << "Identifier\n";
                break;
            case TokenType::Operator :
                cout << "Operator\n";
                break;
            case TokenType::Separator :
                cout << "Separator\n";
                break;
            case TokenType::ReservedWord :
                cout << "ReservedWord\n";
                break;
            default:
                break;
        }
    }
        
}


Scanner::Scanner(string TokenPath, string WorkingFolder)
{
    this->St = SymbolTable(INITIAL_CAPACITY);
    this->WorkingFolder = WorkingFolder;
    ifstream fin(TokenPath);
    
    TokenType type;
    string token;

    this->Separators.push_back("\n");

    while(getline(fin, token))
    {
        if(token == "OPERATORS")
            type = TokenType::Operator;
        else if(token == "SEPARATORS")
            type = TokenType::Separator;
        else if(token == "RESERVED")
            type = TokenType::ReservedWord;
        else 
        {
            if(type == TokenType::Operator)
                this->Operators.push_back(token);
            if(type == TokenType::Separator)
                this->Separators.push_back(token);
            if(type == TokenType::ReservedWord)
                this->ReservedWords.push_back(token);
        }
    }
}

void Scanner::scan(string ProgramPath) 
{
    ifstream fin(ProgramPath);

    string program((istreambuf_iterator<char>(fin)),
                istreambuf_iterator<char>());
    

    size_t pos = 0;
    size_t min_pos;
    pair<string, TokenType> min_token;
    string token;

    while (program.length()) {
        min_pos = program.size() + 1;

        for(string separator : this->Separators)
        {
            pos = program.find(separator);
            if(pos < min_pos)
            {
                min_pos = pos;
                min_token = make_pair(separator, TokenType::Separator);
            }
        }

        for(string op : this->Operators)
        {
            pos = program.find(op);
            if(pos < min_pos)
            {
                min_pos = pos;
                min_token = make_pair(op, TokenType::Operator);
            }
        }
               
        for(string rw : this->ReservedWords)
        {
            pos = program.find(rw);
            if(pos < min_pos)
            {
                min_pos = pos;
                min_token = make_pair(rw, TokenType::ReservedWord);
            }
        }

        token = program.substr(0, min_pos);

        if(token.length())
        {
            if(token[0] == '"'  ||  (token[0] <= '9' && token[0] >= '0'))
                this->PIF.push_back(make_pair(token, TokenType::Constant));
            else
                this->PIF.push_back(make_pair(token, TokenType::Identifier));
            this->St.add(token);
        }   

        if(min_token.first != "\n" && min_token.first != " ")
            this->PIF.push_back(min_token);

        program.erase(0, min_pos + min_token.first.length());
    }
}

string fit(string token, int capacity)
{
    string adaos = "";
    for(int i = 1; i <= capacity - token.length(); i++)
        adaos += " ";
    return token + adaos;
}

void Scanner::writePIF()
{
    ofstream fout(WorkingFolder + "/PIF.out");

    int max_length_token = 0;
    for(auto token_type : this->PIF)
        max_length_token = max(max_length_token, int(token_type.first.length()));

    for(auto token_type : this->PIF)
    {
        switch (token_type.second)
        {
            case TokenType::Separator :
                fout << fit(token_type.first, max_length_token) << " - NULL\n";
                break;
            case TokenType::Operator :
                fout << fit(token_type.first, max_length_token) << " - NULL\n";
                break;
            case TokenType::ReservedWord :
                fout << fit(token_type.first, max_length_token) << " - NULL\n";
                break; 
            case TokenType::Constant :
                fout << fit(token_type.first, max_length_token) << " - " << "(const) (" << this->St.search(token_type.first) << ", " << this->St.positionInChain(token_type.first) << ")" << endl;
                break; 
            case TokenType::Identifier :
                fout << fit(token_type.first, max_length_token) << " - " << "(id) (" << this->St.search(token_type.first) << ", " << this->St.positionInChain(token_type.first) << ")" << endl;
                break;
            default:
                break;
        }
    }
}

void Scanner::writeSymbolTable()
{
    ofstream fout(WorkingFolder + "/SymbolTable.out");
    fout << this->St.details();
}