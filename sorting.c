#include "common.h"
#include "queue_operations.h"

void select_sort(Queue *sorted_nums, Queue *nums) {
    Queue temp_queue;
    declar_queue(&temp_queue);

    Elem *current = nums->BegQ;
    while (current != NULL) {
        add_to_queue(&temp_queue, current->inf);
        current = current->link;
    }

    while (temp_queue.BegQ != NULL) {
        Elem *min_prev = NULL;
        Elem *min_elem = temp_queue.BegQ;
        Elem *prev = temp_queue.BegQ;

        while (prev->link != NULL) {
            if (prev->link->inf < min_elem->inf) {
                min_elem = prev->link;
                min_prev = prev;
            }
            prev = prev->link;
        }

        if (min_prev == NULL) {
            temp_queue.BegQ = min_elem->link;
        }
        else {
            min_prev->link = min_elem->link;
        }

        if (temp_queue.EndQ == min_elem) {
            temp_queue.EndQ = min_prev;
        }

        add_to_queue(sorted_nums, min_elem->inf);

        free(min_elem);
    }

    free_queue(&temp_queue);
}

void quick_sort(Queue *sorted_nums, Queue *nums) {
    if (nums->BegQ == NULL || nums->BegQ->link == NULL) {
        if (nums->BegQ != NULL) {
            add_to_queue(sorted_nums, nums->BegQ->inf);
        }
        return;
    }

    double p = nums->BegQ->inf;
    Queue less;
    declar_queue(&less);
    Queue greater;
    declar_queue(&greater);

    Elem *current = nums->BegQ->link;
    while (current != NULL) {
        if (current->inf < p) {
            add_to_queue(&less, current->inf);
        } else {
            add_to_queue(&greater, current->inf);
        }
        current = current->link;
    }

    quick_sort(sorted_nums, &less);
    add_to_queue(sorted_nums, p);
    quick_sort(sorted_nums, &greater);

    free_queue(&less);
    free_queue(&greater);
}

