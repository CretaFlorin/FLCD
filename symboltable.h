#pragma once

#include <vector>
#include <utility>
#include <string>

using namespace std;

typedef string TKey;
#define NULL_TKEY -111111
#define NULL_POSITION -111111

struct SLLNode {
	TKey data;
	SLLNode* next;
};

struct SLL {
	SLLNode* root;
};


class SymbolTable {
    private:
        SLL* T;                 // The table
        int m;                  // The capacity
        int dim;                // The number of keys in the table
    public:    int hash(TKey) const;   // The hash function

    public:

    void details();

    // constructor
    SymbolTable(int cap);

    // adds a new key to the SymbolTable if it doesn't exist already
    // returns the position of the new key 
    int add(TKey k);

	// returns the position of the key or NULL_POSITION if the key doesn't exist
    int search(TKey k) const;

	// removes a key from the SymbolTable
	// returns the position of the key or NULL_POSITION if the key doesn't exist
    int remove(TKey k);

    //verifies if the SymbolTable is empty
    bool isEmpty() const;

};
