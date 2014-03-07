#ifndef ERRORS_H
#define ERRORS_H

typedef enum
{
    UNKNOWN_FUNC = 47,
    INCOR_DEF_FUNC = 14,
    INCOR_ARG = 61,
    INCOR_LBL_ARG = 43,
    NO_HLT = 93,

    INCOR_LBL_DEF = 23,

    NO_PARAM = 59,
    STACK_EMPT = 75,
    NO_LABEL = 33
} Errcode;

typedef struct Error
{
    int str_count;
    Errcode errcode;
    struct Error *next;
} Error;

typedef struct Errors
{
    Error *head;
    Error *tail;
} Errors;

Errors *create_errors();
int errors_exist(Errors *errors);
void add_error(Errors *errors, Errcode errcode, int str_count);
void clean_errors(Errors *errors);
void print_errors(Errors *errors);

#endif // ERRORS_H
