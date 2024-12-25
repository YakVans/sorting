#include "common.h"
#include "input.h"
#include "output.h"
#include "sorting.h"

// 15 значащих цифр у double
int main()
{
    setlocale(LC_ALL, "Rus");

    Queue nums;
    declar_queue(&nums);
    if (input(&nums)) {
        return 1;
    }

    Queue sorted_nums2;
    declar_queue(&sorted_nums2);
    clock_t start2 = clock();
    quick_sort(&sorted_nums2, &nums);
    clock_t end2 = clock();
    printf("Время выполнения быстрой сортировки: %f\n", (float)(end2 - start2) / CLOCKS_PER_SEC);

    Queue sorted_nums1;
    declar_queue(&sorted_nums1);
    clock_t start1 = clock();
    select_sort(&sorted_nums1, &nums);
    clock_t end1 = clock();
    printf("Время выполнения сортировки выбором: %f\n", (float)(end1 - start1) / CLOCKS_PER_SEC);

    char o_filename[256];
    if (create_output(o_filename)) {
        return 4;
    }
    output(nums, o_filename);
    output(sorted_nums2, o_filename);
    puts("Числа записаны в файл.");

    return 0;
}

