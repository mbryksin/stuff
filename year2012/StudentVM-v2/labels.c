#include "cmd_lbl.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>

Labels *create_labels()
{
    Labels *labels = (Labels *) malloc(sizeof(Labels));
    labels->head = NULL;
    labels->tail = NULL;
    return labels;
}

int labels_is_empty(Labels *labels)
{
    return (labels->head == NULL);
}

void label_init(Labels *labels, char *string)
{
    Label *label = (Label *) malloc(sizeof(Label));
    label->label = string;
    label->next = NULL;
    if (labels_is_empty(labels))
    {
        labels->head = label;
        labels->tail = label;
    } else
    {
        labels->tail->next = label;
        labels->tail = label;
    }
}

void clean_labels(Labels *labels)
{
    while (labels->head != NULL)
    {
        Label *tmp = labels->head->next;
        free(labels->head);
        labels->head = tmp;
    }
}

void print_labels(Labels *labels)
{
    if (labels_is_empty(labels))
    {
        printf("no labels\n");
        return;
    }
    Label *tmp = labels->head;
    while (tmp != NULL)
    {
        printf(":{%s} [%d]\n", tmp->label, tmp->command->cmd);
        tmp = tmp->next;
    }
}
