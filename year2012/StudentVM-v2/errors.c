#include "errors.h"

#include <malloc.h>
#include <stdio.h>

Errors *create_errors()
{
    Errors *errors = (Errors *) malloc(sizeof(Errors));
    errors->head = NULL;
    errors->tail = NULL;
    return errors;
}

int errors_exist(Errors *errors)
{
    return (!(errors->head == NULL));
}

void add_error(Errors *errors, Errcode errcode, int str_count)
{
    Error *error = (Error *) malloc(sizeof(Error));
    error->errcode = errcode;
    error->str_count = str_count;
    error->next = NULL;
    if (errors_exist(errors))
    {
        errors->tail->next = error;
        errors->tail = error;
    } else
    {
        errors->head = error;
        errors->tail = error;
    }
}

void clean_errors(Errors *errors)
{
    while (errors->head != NULL)
    {
        Error *tmp = errors->head->next;
        free(errors->head);
        errors->head = tmp;
    }
}

void print_errors(Errors *errors)
{
    if (!errors_exist(errors))
    {
        return;
    }
    Error *tmp = errors->head;
    while (tmp != NULL)
    {
        fprintf(stderr, "[%d]:(ERROR %d) ", tmp->str_count, tmp->errcode);
        switch (tmp->errcode)
        {
        case INCOR_DEF_FUNC:
            fprintf(stderr, "incorrect function defenition\n"); break;
        case UNKNOWN_FUNC:
            fprintf(stderr, "unknown function\n"); break;
        case INCOR_ARG:
            fprintf(stderr, "incorrect argument\n"); break;
        case INCOR_LBL_ARG:
            fprintf(stderr, "incorrect label argument\n"); break;
        case NO_HLT:
            fprintf(stderr, "no 'HLT' function\n"); break;
        case INCOR_LBL_DEF:
            fprintf(stderr, "incorrect label defenition\n"); break;
        case NO_PARAM:
            fprintf(stderr, "no enough parameters to do operation\n"); break;
        case STACK_EMPT:
            fprintf(stderr, "at the end of program stack is empty\n"); break;
        case NO_LABEL:
            fprintf(stderr, "no such label\n"); break;
        }
        tmp = tmp->next;
    }
}
