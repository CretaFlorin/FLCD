#include <iostream>
#include "SymbolTable.h"


void SymbolTable::details()
{
	cout << "--------------- SymbolTable ----------------\n";
	cout << "Capacity: " << this->m << endl;
	cout << "Dimension: " << this->dim << endl;
	cout << "The Table: \n";
	for (int i = 0; i < this->m; i++)
	{
		cout << "T[" << i << "]: ";
		SLLNode* aux = this->T[i].root;
        while(aux != NULL)
        {
            cout << aux->data;
            if(aux->next != NULL)
                cout << " -> ";
            aux = aux->next;
        }
		cout << "\n";
	}

	cout << endl;
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


bool SymbolTable::isEmpty() const {
	return this->dim == 0;
}

