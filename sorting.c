#include "common.h"
#include "queue_operations.h"

void select_sort(Queue *sorted_nums, Queue *nums) {
    Queue temp_queue;
    declar_queue(&temp_queue);

    // Копируем элементы из nums во временную очередь
    Elem *current = nums->BegQ;
    while (current != NULL) {
        add_to_queue(&temp_queue, current->inf);
        current = current->link;
    }

    while (temp_queue.BegQ != NULL) {
        // Ищем минимальный элемент
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

        // Удаляем минимальный элемент из temp_queue
        if (min_prev == NULL) {
            temp_queue.BegQ = min_elem->link; // Минимальный элемент был первым
        } else {
            min_prev->link = min_elem->link; // Ставим ссылку на следующий элемент
        }

        if (temp_queue.EndQ == min_elem) {
            temp_queue.EndQ = min_prev; // Обновляем конец очереди
        }

        // Добавляем найденный минимальный элемент в отсортированную очередь
        add_to_queue(sorted_nums, min_elem->inf);

        // Освобождаем память для минимального элемента
        free(min_elem);
    }

    free_queue(&temp_queue); // Освобождаем временную очередь
}

void quick_sort(Queue *sorted_nums, Queue *nums) {
    if (nums->BegQ == NULL || nums->BegQ->link == NULL) {
        // Если очередь пустая или содержит один элемент, просто копируем в sorted_nums
        if (nums->BegQ != NULL) {
            add_to_queue(sorted_nums, nums->BegQ->inf);
        }
        return;
    }

    double pivot = nums->BegQ->inf; // Опорный элемент
    Queue less, greater;
    declar_queue(&less);
    declar_queue(&greater);

    Elem *current = nums->BegQ->link; // Начинаем со второго элемента
    while (current != NULL) {
        if (current->inf < pivot) {
            add_to_queue(&less, current->inf);
        } else {
            add_to_queue(&greater, current->inf);
        }
        current = current->link;
    }

    quick_sort(sorted_nums, &less);
    add_to_queue(sorted_nums, pivot); // Добавляем опорный элемент
    quick_sort(sorted_nums, &greater);

    // Освобождаем память для очередей less и greater
    free_queue(&less);
    free_queue(&greater);
}

