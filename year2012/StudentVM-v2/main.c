//by Matvey Bryksin
//February 2013
//Student VM with assembly language

#include "vm_lib.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(void)
{
    Commands *commands = create_commands();
    Labels *labels = create_labels();
    Errors *errors = create_errors();
    char filename[] = "tasks/fibonachi.svm";
    FILE *file = fopen(filename,"r");
    fprintf(stdout, "#Wellcome to Student VM, user!\n");
    fprintf(stdout, "#You start \"%s\" program!\n", filename);
    parser(commands, labels, errors, file);
    fclose(file);
    if (!errors_exist(errors))
    {
        print_commands(commands);
        labels_identification(commands, labels, errors);
        if (!errors_exist(errors))
        {
            print_labels(labels);
            interpreter(commands, labels, errors);
        }
    }
    print_errors(errors);
    clean_commands(commands);
    clean_labels(labels);
    clean_errors(errors);
    printf("#Goodbye, user!\n");
    return 0;
}
