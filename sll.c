#include <stdlib.h>
#include <stdio.h>
#include "sll.h"


node* createNode(int val)
{
    node* n;
    n = (node*)malloc(sizeof(node));
    n->val= val;
    n->next = NULL;
    return n;
}

SLL* createSLL()
{
    SLL* l;
    l = (SLL*)malloc(sizeof(SLL));
    l->head = NULL;
    return l;
}



int isEmpty(SLL* l)
{
    if (l->head == NULL)
        return 1;
    return 0;
}


void addToEnd(SLL* l, int val)
{
    if(isEmpty(l))
    {
        l->head = createNode(val);
        return;
    }

    node* aux = l->head;
    while(aux->next != NULL)
        aux = aux->next;

    node* n = createNode(val);
    aux->next = n;
}


void removeFirst(SLL* l)
{
    if(isEmpty(l))
        return;

    node* first = l->head;
    l->head = l->head->next;
    free(first);
}

void removeElement(SLL* l, int val)
{
    if(isEmpty(l))
        return;

    if(l->head->val == val)
    {
        removeFirst(l);
        return;
    }

    node* aux = l->head;
    while(1)
    {
        if(aux->next == NULL)
            return;
        if(aux->next->val == val) 
        {
            node* temp = aux->next->next;
            free(aux->next);
            aux->next = temp;
            return;
        }
        aux = aux->next;
    }    
}


int search(SLL* l, int val)
{
    node* aux = l->head;
    while(aux != NULL)
    {
        if(aux->val == val)
            return 1;
        aux = aux->next;
    }
    return 0;
}



void print(SLL* l)
{
    node* aux = l->head;
    while(aux != NULL)
    {
        printf("%d ", aux->val);
        aux = aux->next;
    }
    printf("\n");
}