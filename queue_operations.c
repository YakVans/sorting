#include "common.h"
#include "queue_operations.h"

void declar_queue(Queue *Q)
{
    Q->BegQ = NULL;
    Q->EndQ = NULL;
}

void add_to_queue(Queue *Q, double num) {
    Elem *new_elem = (Elem *)malloc(sizeof(Elem));
    new_elem->inf = num;
    new_elem->link = NULL;

    if (Q->EndQ != NULL) {
        Q->EndQ->link = new_elem;
    }
    else {
        Q->BegQ = new_elem;
    }
    Q->EndQ = new_elem;
}

void free_queue(Queue *Q) {
    Elem *current = Q->BegQ;
    while (current != NULL) {
        Elem *temp = current;
        current = current->link;
        free(temp);
    }
    Q->BegQ = NULL;
    Q->EndQ = NULL;
}
