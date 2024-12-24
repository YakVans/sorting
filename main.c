#include "common.h"
#include "input.h"
#include "output.h"
#include "sorting.h"

// 15 значащих цифр у double
int main()
{
    setlocale(LC_ALL, "Rus"); //вывод русских букв
    Queue nums;
    declar_queue(&nums);
    input(&nums);
    print_queue(&nums);
    Queue sorted_nums1;
    declar_queue(&sorted_nums1);
    select_sort(&sorted_nums1, &nums);
    print_queue(&sorted_nums1);

    Queue sorted_nums2;
    declar_queue(&sorted_nums2);
    quick_sort(&sorted_nums2, &nums);
    print_queue(&sorted_nums2);
    return 0;
}

