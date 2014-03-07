#include "cmd_lbl.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>

Commands *create_commands()
{
    Commands *commands = (Commands *) malloc(sizeof(Commands));
    commands->head = NULL;
    commands->tail = NULL;
    return commands;
}

int commands_is_empty(Commands *commands)
{
    return (commands->head == NULL);
}

void add_command_number(Commands *commands, Opcode cmd, int num, int str_count)
{
    Command *command = (Command *) malloc(sizeof(Command));
    command->cmd = cmd;
    command->str_count = str_count;
    if ((cmd == LD) || (cmd == ST))
    {
        command->args.address = num;
    } else if (cmd == LDC)
    {
        command->args.number = num;
    } else
    {
        command->args.number = 0;
    }
    command->next = NULL;
    if (commands_is_empty(commands))
    {
        commands->head = command;
        commands->tail = command;
    } else
    {
        commands->tail->next = command;
        commands->tail = command;
    }
}

void add_command_label(Commands *commands, Opcode cmd, char *label, int str_count)
{
    Command *command = (Command *) malloc(sizeof(Command));
    command->cmd = cmd;
    command->args.label = label;
    command->str_count = str_count;
    command->next = NULL;
    if (commands_is_empty(commands))
    {
        commands->head = command;
        commands->tail = command;
    } else
    {
        commands->tail->next = command;
        commands->tail = command;
    }
}

void add_label(Commands *commands, char *label, int str_count)
{
    Command *command = (Command *) malloc(sizeof(Command));
    command->cmd = LBL;
    command->str_count = str_count;
    command->labeldef = label;
    command->next = NULL;
    if (commands_is_empty(commands))
    {
        commands->head = command;
        commands->tail = command;
    } else
    {
        commands->tail->next = command;
        commands->tail = command;
    }
}

void clean_commands(Commands *commands)
{
    while (commands->head != NULL)
    {
        Command *tmp = commands->head->next;
        free(commands->head);
        commands->head = tmp;
    }
}

void print_commands(Commands *commands)
{
    if (commands_is_empty(commands))
    {
        printf("is empty\n");
        return;
    }
    Command *tmp = commands->head;
    while (tmp != NULL)
    {
        switch (tmp->cmd)
        {
        case LBL:
            printf("/%s/\n", tmp->labeldef); break;
        case LDC:
            printf("[%d] <%d>\n", tmp->cmd, tmp->args.number); break;
        case LD: case ST:
            printf("[%d] <%d>\n", tmp->cmd, tmp->args.address); break;
        case JMP: case BR:
            printf("[%d] <%s>\n", tmp->cmd, tmp->args.label); break;
        case SUB: case MOD: case ADD: case MUL: case DIV: case CMP: case HLT:
            printf("[%d]\n", tmp->cmd); break;
        }
        tmp = tmp->next;
    }
}
