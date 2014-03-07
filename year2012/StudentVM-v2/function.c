#include "vm_lib.h"

#include "string.h"
#include "malloc.h"

Opcode operation(char *word)
{
    if (!strcmp(word, "ldc"))
        return LDC;
    if (!strcmp(word, "sub"))
        return SUB;
    if (!strcmp(word, "hlt"))
        return HLT;
    if (!strcmp(word, "ld"))
        return LD;
    if (!strcmp(word, "st"))
        return ST;
    if (!strcmp(word, "add"))
        return ADD;
    if (!strcmp(word, "mul"))
        return MUL;
    if (!strcmp(word, "div"))
        return DIV;
    if (!strcmp(word, "mod"))
        return MOD;
    if (!strcmp(word, "cmp"))
        return CMP;
    if (!strcmp(word, "jmp"))
        return JMP;
    if (!strcmp(word, "br"))
        return BR;
    if (!strcmp(word, "hlt"))
        return HLT;
    return ERR;
}

int is_letter(char x)
{
    return ((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z'));
}
int is_number(char x)
{
    return ((x >= '0') && (x <= '9'));
}

void get_label(Commands *commands, char *string, int i, Opcode cmd, int str_count)
{
    int j = 0;
    char *label = (char*) malloc(1000 * sizeof(char));
    memset(label, '\0', 1000);
    while ((is_letter(string[i])) || (is_number(string[i])))
    {
        label[j] = toLower(string[i]);
        i++;
        j++;
    }
    add_command_label(commands, cmd, label, str_count);
}

char toLower(char x)
{
    if ((x >= 'A') && (x <= 'Z'))
    {
        x = x + ('a' - 'A');
    }
    return x;
}
