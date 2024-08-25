#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "assert.h"

char *read_file(char *path)
{
    static char content[1024 * 1024];
    content[0] = 0;
    FILE *f = fopen(path, "r");

    if (f == NULL)
    {
        return NULL;
    }

    unsigned int pos = 0;
    char c;
    while ((c = fgetc(f)) != EOF)
    {
        content[pos] = c;
        pos++;
    }
    content[pos] = 0;
    fclose(f);
    return content;
}

char interpret(char *source)
{
    unsigned char memory[30000];
    memset(memory, 0, sizeof(memory));
    char *fptr = source;
    unsigned char *mptr = memory;
    char c;
    unsigned int repeat_times = 0;
    unsigned int memory_pointer = 0;
    unsigned int memory_used = 1;
    while ((c = (*fptr)))
    {
        if (c == '>')
        {
            mptr++;
            memory_pointer++;
            if (memory_pointer == memory_used)
            {
                memory_used++;
            }
        }
        else if (c == '<')
        {
            mptr--;
            memory_pointer--;
        }
        else if (c == '+')
        {
            if ((*mptr) < 255)
                (*mptr)++;
        }
        else if (c == '-')
        {
            if ((*mptr) > 0)
                (*mptr)--;
        }
        else if (c == ',')
        {
            c = fgetc(stdin);
            *mptr = c;
        }
        else if (c == '.')
        {
            if(isalpha(*mptr) || isspace(*mptr)  || ispunct(*mptr) || isdigit(*mptr)){
                putc(*mptr, stdout); 
            }else{
                printf("%d",*mptr);
            }
            fflush(stdout);
        }
        else if (c == '[')
        {
            if (!*mptr)
            {
                (*fptr)++;
                unsigned int indent = 1;
                while (indent != 0)
                {
                    c = *fptr;
                    if (c == '[')
                    {
                        indent++;
                    }
                    else if (c == ']')
                    {
                        indent--;
                    }
                    (fptr++);
                }
            }
        }
        else if (c == ']')
        {

            if ((*mptr))
            {
                (fptr)--;
                unsigned int indent = 1;
                while (indent != 0)
                {
                    c = *fptr;
                    if (c == '[')
                    {
                        indent--;
                    }
                    else if (c == ']')
                    {
                        indent++;
                    }
                    fptr--;
                }
            }
        }
        else if (*fptr == '!')
        {
            for (unsigned int i = 0; i < memory_used + 1; i++)
            {
                if (isalnum(memory[i]))
                {
                    printf("[%c]", memory[i]);
                }
                else
                {
                    printf("[%d]", memory[i]);
                }
            }
            printf("\n");
        }
        else if (isdigit(*fptr))
        {
            char *repeat_fptr = fptr - 2;
            char digitss[10];
            unsigned int dcount = 0;
            while (isdigit(*fptr))
            {
                digitss[dcount] = *fptr;
                fptr++;
                dcount++;
            }
            digitss[dcount] = 0;
            unsigned int digits = atoi(digitss);
            if (!repeat_times)
            {
                repeat_times = digits;
            }
            repeat_times--;
            if (repeat_times)
            {
                fptr = repeat_fptr;
            }
            else
            {
                fptr--;
            }
        }
        fptr++;
    }
    return *mptr;
}

void tests(){
    // Numbers (Custom implementation)
    assert(interpret("+5[->+5<]>") == 25);
    assert(interpret("+10[->+5<]>") == 50);
    // Loop rules
    assert(interpret("+++++[->+++++<]>") == 25);
    // Recursion
    assert(interpret("+2[[[-]]]+5") == 5);
    // Addition
    assert(interpret("+2+4") == 6);
    // Substraction
    assert(interpret("+5--") == 3);
    // Big numbers
    assert(interpret("+65+--") == '@');
}

int main(int argc, char *argv[])
{
    tests();
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    char *file_name = argv[1];
    char *source = read_file(file_name);
    if (source == NULL)
    {
        printf("File \"%s\" does not exist.\n", file_name);
        return 1;
    }
    char r = interpret(source);
    printf("\nResult: %d\n", r);
    return 0;
}
