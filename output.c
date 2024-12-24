#include "common.h"


void print_queue(Queue *q) {
    Elem *current = q->BegQ;
    while (current != NULL) {
        printf("%lf ", current->inf);
        current = current->link;
    }
    printf("\n");
}

int output(Queue q)
{
    int c_symb;

    char output_filename_pattern[7] = "--file ";
    int pos_in_output_filename_pattern = 0;
    char o_filename[256];
    int pos_in_o_filename = 0;

    while ((c_symb = getc(stdin)) != EOF && c_symb != '\n') {
        if (pos_in_output_filename_pattern == 0) {
            if (c_symb == ' ') {
                continue;
            }
            else if (c_symb == '-') {
                pos_in_output_filename_pattern++;
            }
            else {
                break;
            }
        }
        else if (pos_in_output_filename_pattern < 7) {
            if (c_symb == output_filename_pattern[pos_in_output_filename_pattern++]) {
                continue;
            }
            else {
                return 1; // не то после --
            }
        }
        else if (pos_in_output_filename_pattern == 7) {
            if (c_symb == ' ') {
                continue;
            }
            else {
                o_filename[pos_in_o_filename++] = c_symb;
                pos_in_output_filename_pattern++;
            }
        }
        else {
            if (pos_in_o_filename == 255) { // нужно добавить случай когда пользователь после o_filename до \n ' ' вводит
                return 2; //слишком длинное имя файла
            }
            else {
                o_filename[pos_in_o_filename++] = c_symb;
            }
        }
    }
    o_filename[pos_in_o_filename] = '\0';
    FILE *file = fopen(o_filename, "w");

    if (file == NULL) {
        return 3; //ошибка открытия файла
    }


    Elem *num = q.BegQ;
    while (num->link != NULL) {
        fprintf(file, "%lld ", num->inf);
        num = num->link;
    }
    fprintf(file, "%lld\n", num->inf);
    fclose(file);
}
