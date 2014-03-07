#include "vm_lib.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>


void labels_identification(Commands *commands, Labels *labels, Errors *errors)
{
    int str_count = 0;
    if (labels_is_empty(labels) || commands_is_empty(commands))
    {
        return;
    }
    Command *command = commands->head;
    while (command != NULL)
    {
        str_count++;
        if (command->cmd == LBL)
        {
            Label *tmp = labels->head;
            while (strcmp(tmp->label, command->labeldef))
            {
                tmp = tmp->next;
            }
            if (command->next->cmd == LBL)
            {
                add_error(errors, INCOR_LBL_DEF, command->next->str_count);
            }
            tmp->command = command->next;
        }
        command = command->next;
    }
}
