#include "common.h"


void print_queue(Queue *q) {
    Elem *current = q->BegQ;
    while (current != NULL) {
        printf("%lf ", current->inf);
        current = current->link;
    }
    printf("\n");
}

int create_output(char *o_filename)
{
    int c_symb;

    char output_filename_pattern[8] = "--file ";
    int pos_in_output_filename_pattern = 0;
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
                puts("Неизвестная команда после --. Возможные команды: --rfile [filename], --file [filename]. Первая возможна вместо ручного ввода чисел с клавиатуры. Вторая возможна только после какого-либо ввода чисел.");
                return 1;
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
                puts("Слишком длинное имя файла. Вводите имя не больше 255 символов.");
                return 2;
            }
            else {
                o_filename[pos_in_o_filename++] = c_symb;
            }
        }
    }
    o_filename[pos_in_o_filename] = '\0';
    FILE *file = fopen(o_filename, "w");

    if (file == NULL) {
        puts("Ошибка открытия файла.");
        return 3;
    }
    fclose(file);
    return 0;
}

void output(Queue q, char *o_filename)
{
    FILE *file = fopen(o_filename, "a");
    if (file == NULL) {
        puts("Ошибка открытия файла.");
        return;
    }

    if (q.BegQ == NULL) {
        puts("Очередь пуста.");
        fclose(file);
        return;
    }

    Elem *num = q.BegQ;
    while (num != NULL) {
        fprintf(file, "%lf ", num->inf);
        num = num->link;
    }
    fprintf(file, "\n");
    fclose(file);
}
