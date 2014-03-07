#ifndef CMD_LBL_H
#define CMD_LBL_H

typedef enum
{
    LDC = 101,
    LD = 111,
    ST = 102,

    SUB = 103,
    ADD = 113,
    MUL = 123,
    DIV = 133,
    MOD = 143,
    CMP = 153,


    JMP = 104,
    BR = 114,

    HLT = 201,

    LBL = 301,
    ERR = 401
}Opcode;

typedef struct Command
{
    Opcode cmd;
    int str_count;
    union
    {
        int number;
        int address;
        char *label;
    }args;
    char* labeldef;
    struct Command *next;
}Command;

typedef struct Commands
{
    Command *head;
    Command *tail;
} Commands;

Commands *create_commands();
void print_commands(Commands *commands);
void clean_commands(Commands *commands);
int commands_is_empty(Commands *commands);
void add_command_number(Commands *commands, Opcode cmd, int num, int str_count);
void add_command_label(Commands *commands, Opcode cmd, char *label, int str_count);
void add_label(Commands *commands, char *label, int str_count);

/**/

typedef struct Label
{
    char *label;
    struct Label *next;
    Command *command;
} Label;

typedef struct Labels
{
    Label *head;
    Label *tail;
} Labels;

Labels *create_labels();
int labels_is_empty(Labels *labels);
void label_init(Labels *labels, char *string);
void clean_labels(Labels *labels);
void print_labels(Labels *labels);
#endif // CMD_LBL_H
