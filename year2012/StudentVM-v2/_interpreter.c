#include "vm_lib.h"

#include <stdio.h>
#include <string.h>

void load_constant(Stack *stack, int value)
{
    push(stack, value);
}

void load(Memory *memory, Stack *stack, int address)
{
    int x = 0;
    x = memory->array[address];
    push(stack, x);
}

void hlt(Stack *stack, Errors *errors)
{
    if (stack_is_empty(stack))
    {
        add_error(errors, STACK_EMPT, 0);
        return;
    }
    if (errors_exist(errors))
    {
        return;
    }
    fprintf(stdout, "Program finished with number: %d\n", pop(stack));
}

Command *next_command(Labels *labels, Command *ip)
{
    Label *tmp = labels->head;
    while (tmp != NULL)
    {
        if (!strcmp(tmp->label, ip->args.label))
        {
            break;
        } else
        {
            tmp = tmp->next;
        }
    }
    return tmp->command;
}

/**/

void interpreter(Commands *commands, Labels *labels, Errors *errors)
{
    Stack *stack = create_stack();
    Memory *memory = create_memory();
    Command *ip = commands->head;
    while (ip != NULL)
    {
        switch (ip->cmd)
        {
            case LD:
                //fprintf(stderr, "#LD#\n");
                load(memory, stack, ip->args.address);
                ip = ip->next;
                break;
            case ST:
                //fprintf(stderr, "#ST#\n");
                if (stack_is_empty(stack))
                {
                    add_error(errors, NO_PARAM, ip->str_count);
                } else
                {
                    int x = 0;
                    x = pop(stack);
                    memory->array[ip->args.address] = x;
                }
                ip = ip->next;
                break;
            case LBL:
                //fprintf(stderr, "#LBL#\n");
                ip = ip->next;
                break;
            case BR:
                //fprintf(stderr, "#BR#\n");
                if (stack_is_empty(stack))
                {
                    add_error(errors, NO_PARAM, ip->str_count);
                    clean_memory(memory);
                    destroy(stack);
                    return;
                } else if (pop(stack) == 0)
                {
                    ip = ip->next;
                } else
                {
                    Label *tmp = labels->head;
                    while (tmp != NULL)
                    {
                        if (!strcmp(tmp->label, ip->args.label))
                        {
                            ip = tmp->command;
                            break;
                        } else
                        {
                            tmp = tmp->next;
                        }
                    }
                    if (tmp == NULL)
                    {
                        add_error(errors, NO_LABEL, ip->str_count);
                        clean_memory(memory);
                        destroy(stack);
                        return;
                    }
                }
                break;
            case JMP:
            {
                //fprintf(stderr, "#JMP#\n");
                Label *tmp = labels->head;
                while (tmp != NULL)
                {
                    if (!strcmp(tmp->label, ip->args.label))
                    {
                        ip = tmp->command;
                        break;
                    } else
                    {
                        tmp = tmp->next;
                    }
                }
                if (tmp == NULL)
                {
                    add_error(errors, NO_LABEL, ip->str_count);
                    clean_memory(memory);
                    destroy(stack);
                    return;
                }
                break;
            }
            case LDC:
                //fprintf(stderr, "#LDC#\n");
                load_constant(stack, ip->args.number);
                ip = ip->next;
                break;
            case SUB:
                //fprintf(stderr, "#SUB#\n");
                if (stack_is_empty(stack))
                {
                    add_error(errors, NO_PARAM, ip->str_count);
                } else
                {
                    int b = pop(stack);
                    if (stack_is_empty(stack))
                    {
                        add_error(errors, NO_PARAM, ip->str_count);
                    } else
                    {
                        int a = pop(stack);
                        push(stack, a - b);
                    }
                }
                ip = ip->next;
                break;
            case ADD:
                //fprintf(stderr, "#ADD#\n");
                if (stack_is_empty(stack))
                {
                    add_error(errors, NO_PARAM, ip->str_count);
                } else
                {
                    int b = pop(stack);
                    if (stack_is_empty(stack))
                    {
                        add_error(errors, NO_PARAM, ip->str_count);
                    } else
                    {
                        int a = pop(stack);
                        push(stack, a + b);
                    }
                }
                ip = ip->next;
                break;
            case MUL:
                //fprintf(stderr, "#MUL#\n");
                if (stack_is_empty(stack))
                {
                    add_error(errors, NO_PARAM, ip->str_count);
                } else
                {
                    int b = pop(stack);
                    if (stack_is_empty(stack))
                    {
                        add_error(errors, NO_PARAM, ip->str_count);
                    } else
                    {
                        int a = pop(stack);
                        push(stack, a * b);
                    }
                }
                ip = ip->next;
                break;
            case MOD:
                //fprintf(stderr, "#MOD#\n");
                if (stack_is_empty(stack))
                {
                    add_error(errors, NO_PARAM, ip->str_count);
                } else
                {
                    int b = pop(stack);
                    if (stack_is_empty(stack))
                    {
                        add_error(errors, NO_PARAM, ip->str_count);
                    } else
                    {
                        int a = pop(stack);
                        push(stack, a % b);
                    }
                }
                ip = ip->next;
                break;
            case DIV:
                //fprintf(stderr, "#DIV#\n");
                if (stack_is_empty(stack))
                {
                    add_error(errors, NO_PARAM, ip->str_count);
                } else
                {
                    int b = pop(stack);
                    if (stack_is_empty(stack))
                    {
                        add_error(errors, NO_PARAM, ip->str_count);
                    } else
                    {
                        int a = pop(stack);
                        push(stack, a / b);
                    }
                }
                ip = ip->next;
                break;
            case CMP:
                //fprintf(stderr, "#CMP#\n");
                if (stack_is_empty(stack))
                {
                    add_error(errors, NO_PARAM, ip->str_count);
                } else
                {
                    int b = pop(stack);
                    if (stack_is_empty(stack))
                    {
                        add_error(errors, NO_PARAM, ip->str_count);
                    } else
                    {
                        int a = pop(stack);
                        if (a > b)
                        {
                            push(stack, 1);
                        } else if (a < b)
                        {
                            push(stack, -1);
                        } else
                        {
                            push(stack, 0);
                        }
                    }
                }
                ip = ip->next;
                break;
            case HLT:
                //fprintf(stderr, "#HLT#\n");
                hlt(stack, errors);
                ip = NULL;
                break;
            default:
                ip = NULL;
                break;
        }
    }
    clean_memory(memory);
    destroy(stack);
}
