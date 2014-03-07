#include "vm_lib.h"

#include <malloc.h>
#include <memory.h>


void parser(Commands *commands, Labels *labels, Errors *errors, FILE *input)
{
    int str_count = 0;
    int hlt = 0;
    while (!feof(input))
    {
        char *string = (char*) malloc(1000 * sizeof(char));
        char *word = (char*) malloc(1000 * sizeof(char));
        int i = 0;
        int j = 0;
        memset(word, '\0', 1000);
        memset(string, '\0', 1000);
        fgets(string, 1000, input);
        if (feof(input))
        {
            break;
        }
        str_count++;
        while (string[i] == ' ')
        {
            i++;
        }
        while ((is_letter(string[i])) || (is_number(string[i])))
        {
            word[j++] = toLower(string[i++]);
        }
        if (j == 0)
        {
            add_error(errors, INCOR_DEF_FUNC, str_count);
            free(string);
            free(word);
            continue;
        }
        if (string[i] == ':')
        {
            add_label(commands, word, str_count);
            label_init(labels, word);
        } else if ((string[i] == ';') || (string[i] == ' ') || (string[i] == '\r') || (string[i] == '\n'))
        {
            Opcode cmd = operation(word);
            int num = 0;
            int negative = 0;
            switch (cmd)
            {
            case LDC: case LD: case ST:
                while (string[i] == ' ') i++;
                if (string[i] == '-')
                {
                    negative = 1;
                    i++;
                }
                if (!is_number(string[i]))
                {
                    add_error(errors, INCOR_ARG, str_count);
                    free(word);
                    free(string);
                    continue;
                }
                while (is_number(string[i]))
                {
                    num = 10 * num + string[i] - '0';
                    i++;
                }
                if (negative)
                {
                    num = num * (-1);
                }
                add_command_number(commands, cmd, num, str_count);
                break;
            case SUB: case MOD: case ADD: case MUL: case DIV: case CMP:
                add_command_number(commands, cmd, 0, str_count); break;
            case HLT:
                add_command_number(commands, cmd, 0, str_count);
                hlt++;
                break;
            case JMP: case BR:
                while (string[i] == ' ') i++;
                if (!((is_letter(string[i])) || (is_number(string[i]))))
                {
                    add_error(errors, INCOR_LBL_ARG, str_count);
                    free(word);
                    free(string);
                    continue;
                }
                get_label(commands, string, i, cmd, str_count);
                break;
            case ERR:
                add_error(errors, UNKNOWN_FUNC, str_count);
                free(string);
                free(word);
                continue;
            case LBL: break;
            }
            free(word);
        }
        free(string);
    }
    if (hlt == 0)
    {
        add_error(errors, NO_HLT, 0);
    }
}
