#ifndef VM_LIB_H
#define VM_LIB_H

#include "cmd_lbl.h"
#include "stack_memory.h"
#include "errors.h"
#include <stdio.h>

char toLower(char x);
Opcode operation(char *word);
int is_letter(char x);
int is_number(char x);
void get_label(Commands *commands, char *string, int i, Opcode cmd, int str_count);

void parser(Commands *commands, Labels *labels, Errors *errors, FILE *input);
void labels_identification(Commands *commands, Labels *labels, Errors *errors);
void interpreter(Commands *commands, Labels *labels, Errors *errors);


#endif // VM_LIB_H
