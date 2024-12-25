#include "common.h"
#include "input.h"

int processing_c_symb(char c_symb, int *num_sign_dig, int *num_zero_dig, int *minus_was, int *dot_was, char *curr_num, int *num_of_last_digit, Queue *nums)
{
    if (isdigit(c_symb)) {
        if (*num_of_last_digit+1 - *dot_was - *minus_was == DOUBLE_MAX_DIGIT+1) {
            return 1;
        }
        if (c_symb == '0') {
            if (*num_sign_dig != 0) {
                *num_zero_dig += 1;
            }
        }
        else {
            *num_sign_dig += *num_zero_dig + 1;
            *num_zero_dig = 0;
        }
        if (*num_sign_dig > 15) {
            return 7;
        }
        curr_num[*num_of_last_digit] = c_symb;
        *num_of_last_digit += 1;
    }
    else if (c_symb == '-') {
        if (*minus_was) {
            return 2;
        }
        if (*num_of_last_digit != 0) {
            return 3;
        }
        curr_num[*num_of_last_digit] = '-';
        *num_of_last_digit += 1;
        *minus_was = 1;
    }
    else if (c_symb == '.' || c_symb == ',') {
        if (*dot_was) {
            return 4;
        }

        if (*num_of_last_digit == 0 || (*num_of_last_digit == 1 && *minus_was)) {
            return 5;
        }
        curr_num[*num_of_last_digit] = ',';
        *num_of_last_digit += 1;
        *dot_was = 1;
    }
    else if (c_symb == ' ' || c_symb == '\n') {
        if (*num_of_last_digit == 0 && nums->BegQ == NULL && c_symb == '\n') {
            return 6;
        }
        if (*num_of_last_digit != 0) {
            if (curr_num[*num_of_last_digit-1] == '-') {
                return 3;
            }
            if (curr_num[*num_of_last_digit-1] == ',') {
                return 8;
            }
            add_to_queue(nums, strtod(curr_num, 0));

            memset(curr_num, '\0', DOUBLE_MAX_DIGIT+3);
            *num_of_last_digit = 0;
            *dot_was = 0;
            *minus_was = 0;
            *num_sign_dig = 0;
            *num_zero_dig = 0;
            if (c_symb == '\n') {
                return 0;
            }
        }
    }
    else {
        return 9;
    }
    return 0;
}

int input(Queue *nums)
{
    setlocale(LC_ALL, "Rus");
    int c_symb;

    char input_filename_pattern[9] = "--rfile ";
    int pos_in_input_filename_pattern = 0;
    char r_filename[256];
    int pos_in_r_filename = 0;

    while ((c_symb = getc(stdin)) != '\n') {
        if (pos_in_input_filename_pattern == 0) {
            if (c_symb == ' ') {
                continue;
            }
            else if (c_symb == '-') {
                pos_in_input_filename_pattern++;
            }
            else {
                break;
            }
        }
        else if (pos_in_input_filename_pattern == 1) {
            if (c_symb == input_filename_pattern[pos_in_input_filename_pattern++]) {
                continue;
            }
            else if (isdigit(c_symb)) {
                break;
            }
            else {
                puts("Неизвестная команда после --. Возможные команды: --rfile [filename], --file [filename]. Первая возможна вместо ручного ввода чисел с клавиатуры. Вторая возможна только после какого-либо ввода чисел.");
                return 1;
            }
        }
        else if (pos_in_input_filename_pattern < 8) {
            if (c_symb == input_filename_pattern[pos_in_input_filename_pattern++]) {
                continue;
            }
            else {
                puts("Неизвестная команда после --. Возможные команды: --rfile [filename], --file [filename]. Первая возможна вместо ручного ввода чисел с клавиатуры. Вторая возможна только после какого-либо ввода чисел.");
                return 1;
            }
        }
        else if (pos_in_input_filename_pattern == 8) {
            if (c_symb == ' ') {
                continue;
            }
            else {
                r_filename[pos_in_r_filename++] = c_symb;
                pos_in_input_filename_pattern++;
            }
        }
        else {
            if (pos_in_r_filename == 255) { // нужно добавить случай когда пользователь после r_filename до \n ' ' вводит
                puts("Слишком длинное имя файла. Вводите имя не больше 255 символов.");
                return 2;
            }
            else {
                r_filename[pos_in_r_filename++] = c_symb;
            }
        }
    }
    r_filename[pos_in_r_filename] = '\0';
    int is_input_from_file = (pos_in_input_filename_pattern == 9);
    FILE *rfile = fopen(r_filename, "r");

    if (is_input_from_file && rfile == NULL) {
        puts("Ошибка открытия файла.");
        return 3;
    }

    int curr_num_of_num = 0;
    char curr_num[DOUBLE_MAX_DIGIT+3];
    memset(curr_num, '\0', DOUBLE_MAX_DIGIT+3);
    int num_of_last_digit = 0;
    int dot_was = 0;
    int minus_was = 0;
    int num_sign_dig = 0;
    int num_zero_dig = 0;

    if (pos_in_input_filename_pattern == 2) {
        minus_was = 1;
        curr_num[0] = '-';
        num_of_last_digit = 1;
    }
    int error = 0;

    if (is_input_from_file == 0) {
        do {
            error = processing_c_symb(c_symb, &num_sign_dig, &num_zero_dig, &minus_was, &dot_was, curr_num, &num_of_last_digit, nums);
            if (error != 0 || c_symb == '\n') {
                break;
            }
        } while ((c_symb = getc(stdin)) != EOF);
    }
    else {
        while ((c_symb = getc(rfile)) != EOF) {
            error = processing_c_symb(c_symb, &num_sign_dig, &num_zero_dig, &minus_was, &dot_was, curr_num, &num_of_last_digit, nums);
            if (error != 0 || c_symb == '\n') {
                break;
            }
        }
    }
    fclose(rfile);

    switch (error)
    {
    case 1:
        printf("Слишком много цифр в числе (более %d)\n", DOUBLE_MAX_DIGIT);
        break;
    case 2:
        puts("В числе не может быть более 1 минуса.");
        break;
    case 3:
        puts("Минус может стоять только в начале числа.");
        break;
    case 4:
        puts("В числе не может быть более 1 точки.");
        break;
    case 5:
        puts("Точка не может стоять в начале числа.");
        break;
    case 6:
        puts("Вы ввели пустую строку.");
        break;
    case 7:
        printf("Слишком много значащих цифр (больше %d). Невозможна корректная сортировка\n", 15);
        break;
    case 8:
        puts("Точка не может стоять в конце числа.");
        break;
    case 9:
        puts("В строке есть запрещенные символы. Все разрешенные символы: '1234567890 '.");
        break;
    }
    if (error > 0) {
        return 4; // ошибка уже выведена
    }
    return 0;
}
