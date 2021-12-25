#include <iostream>
#include "SymbolTable.h"


string SymbolTable::details()
{
    string result = "";
	result += "--------------- SymbolTable ----------------\n";
	result += "Capacity: " + to_string(this->m) + "\n";
	result += "Dimension: " + to_string(this->dim) + "\n";
	result += "The Table: \n";
	for (int i = 0; i < this->m; i++)
	{
		result += "T[" + to_string(i) + "]: ";
		SLLNode* aux = this->T[i].root;
        while(aux != NULL)
        {
            result += aux->data;
            if(aux->next != NULL)
                result +=  " -> ";
            aux = aux->next;
        }
		result += "\n";
	}

	result += "\n";

    return result;
}


SymbolTable::SymbolTable(int cap)
{
    this->m = cap;
    this->dim = 0;
    this->T = (SLL*)malloc(cap * sizeof(SLL));
    for(int i = 0; i < cap; i++)
        this->T[i].root = NULL;
}


// djb2
int SymbolTable::hash(TKey key) const
{
    int h = 5381;

    for (int i = 0; i <= key.length(); i++)
        h = ((h << 5) + h) + key[i];
    
    return std::abs(h) % this->m;
}



int SymbolTable::add(TKey key) 
{
    int position = this->hash(key);

    if(this->search(key) != NULL_POSITION)
        return position;

    SLLNode* aux = this->T[position].root;

    SLLNode* newNode = new SLLNode;
    newNode->data = key;
    newNode->next = aux;

    this->T[position].root = newNode;

    this->dim++;
    return position;
}

int SymbolTable::remove(TKey key) 
{
    if(this->search(key) == NULL_POSITION)
        return NULL_POSITION;

    int position = this->hash(key);

    SLLNode* aux = this->T[position].root;
    SLLNode* next;

    if(aux->data == key)
    {
        next = aux->next;
        free(aux);
        this->T[position].root = next;
    }
    else
    {
        while(aux->next->data != key)
            aux = aux->next;
        next = aux->next->next;
        free(aux->next);
        aux->next = next;
    }

    this->dim++;
    return position;
}


int SymbolTable::search(TKey key) const 
{
    int position = this->hash(key);
    SLLNode* aux = this->T[position].root;

    while(aux != NULL)
    {
        if(aux->data == key)
            return position;
        aux = aux->next;
    }

    return NULL_POSITION;
}


int SymbolTable::positionInChain(TKey key) const
{
    int position = this->hash(key);
    int pos = 0;
    SLLNode* aux = this->T[position].root;

    while(aux != NULL)
    {
        if(aux->data == key)
            return pos;
        aux = aux->next;
        pos++;
    }

    return NULL_POSITION;
}


bool SymbolTable::isEmpty() const {
	return this->dim == 0;
}

