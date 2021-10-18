#ifndef sll_h
#define sll_h


typedef struct node {
    int val;
    struct node* next;
} node;

typedef struct SLL {
    struct node* head;
} SLL;



node* createNode(int val);

SLL* createSLL();

int isEmpty(SLL* l);


void addToEnd(SLL* l, int val);

void removeElement(SLL* l, int val);

int search(SLL* l, int val);


void print(SLL* l);


#endif // sll_h

