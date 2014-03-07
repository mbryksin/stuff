#include <stdio.h>
#include <malloc.h>
#include "string.h"

int main(void)
{
    printf("Hello World!\n");
    char *message = "CODE:64 VALUE:1\0";
    int ip = 0;
    int len = strlen(message) - 1;
    while (message[ip] != '\0' && ip <= len)
    {
        char *pattern = (char*) malloc(50*sizeof(char));
        int j = 0;
        while (message[ip] != ':')
        {
            pattern[j] = message[ip];
            ip++;
            j++;
        }
        printf("pattern:%s\n", pattern);
        int arg = 0;
        ip++;
        while ((message[ip] <= '9') && (message[ip] >= '0') && (message[ip] != '\0') && (ip <= len))
        {
            arg = arg * 10 + message[ip] - '0';
            ip++;
        }
        free(pattern);
        printf("arg = %d\n", arg);
        ip++;
    }
    return 0;
}

