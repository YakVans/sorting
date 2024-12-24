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
                puts("����������� ������� ����� --. ��������� �������: --rfile [filename], --file [filename]. ������ �������� ������ ������� ����� ����� � ����������. ������ �������� ������ ����� ������-���� ����� �����.");
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
            if (pos_in_o_filename == 255) { // ����� �������� ������ ����� ������������ ����� o_filename �� \n ' ' ������
                puts("������� ������� ��� �����. ������� ��� �� ������ 255 ��������.");
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
        puts("������ �������� �����.");
        return 3;
    }
    fclose(file);
    return 0;
}

void output(Queue q, char *o_filename)
{
    FILE *file = fopen(o_filename, "a");
    if (file == NULL) {
        puts("������ �������� �����.");
        return;
    }

    if (q.BegQ == NULL) {
        puts("������� �����.");
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
