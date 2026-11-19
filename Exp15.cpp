
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[100];
char stack[100];
char lasthandle[10];

int i = 0;
int top = 0;
int l;

// Handles used for reduction
char handles[][5] = {
    "(E)",
    "E+E",
    "E-E",
    "E*E",
    "E/E",
    "E^E",
    "i"
};

// Operator precedence table
// Order: +  -  *  /  ^  i  (  )  $

char prec[9][9] = {
    {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'},
    {'<', '<', '<', '<', '<', '<', '<', '=', 'e'},
    {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'},
    {'<', '<', '<', '<', '<', '<', '<', 'e', '>'}
};

// Find index of terminal
int getindex(char c)
{
    switch (c)
    {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '^': return 4;
        case 'i': return 5;
        case '(': return 6;
        case ')': return 7;
        case '$': return 8;
        default:  return -1;
    }
}

// Find topmost terminal in stack
int topterminal()
{
    int j;

    for (j = top; j >= 0; j--)
    {
        if (getindex(stack[j]) != -1)
            return j;
    }

    return -1;
}

// Shift operation
int shift()
{
    if (i >= l || top >= 98)
        return 0;

    stack[++top] = input[i++];
    stack[top + 1] = '\0';

    return 1;
}

// Reduction operation
int reduce()
{
    int h, len;

    for (h = 0; h < 7; h++)
    {
        len = strlen(handles[h]);

        if (top + 1 >= len)
        {
            if (strncmp(stack + top - len + 1,
                        handles[h], len) == 0)
            {
                top = top - len + 1;
                stack[top] = 'E';

                strcpy(lasthandle, handles[h]);
                stack[top + 1] = '\0';

                return 1;
            }
        }
    }

    return 0;
}

// Display stack
void dispstack()
{
    int j;

    for (j = 0; j <= top; j++)
        printf("%c", stack[j]);
}

// Display remaining input
void dispinput()
{
    int j;

    for (j = i; j < l; j++)
        printf("%c", input[j]);
}

// Main function
int main()
{
    int t;
    int relation;
    int accepted = 0;

    printf("\nOPERATOR PRECEDENCE PARSING\n");

    printf("\nGrammar:");
    printf("\nE -> E+E");
    printf("\nE -> E-E");
    printf("\nE -> E*E");
    printf("\nE -> E/E");
    printf("\nE -> E^E");
    printf("\nE -> (E)");
    printf("\nE -> i");

    printf("\n\nEnter the input string: ");

    if (scanf("%99s", input) != 1)
        return 1;

    // Validate input symbols
    for (t = 0; input[t] != '\0'; t++)
    {
        if (getindex(input[t]) == -1 ||
            input[t] == '$')
        {
            printf("\nInvalid input symbol!");
            return 0;
        }
    }

    // Add end marker
    strcat(input, "$");
    l = strlen(input);

    // Initialize stack
    strcpy(stack, "$");
    top = 0;
    i = 0;

    printf("\n\nSTACK\tINPUT\t\tACTION\n");

    while (1)
    {
        // Check acceptance
        if (strcmp(stack, "$E") == 0 &&
            input[i] == '$')
        {
            accepted = 1;
            break;
        }

        t = topterminal();

        if (t == -1 || getindex(input[i]) == -1)
            break;

        relation = prec[getindex(stack[t])]
                       [getindex(input[i])];

        if (relation == '<' || relation == '=')
        {
            if (!shift())
                break;

            dispstack();
            printf("\t");
            dispinput();
            printf("\tShift\n");
        }
        else if (relation == '>')
        {
            if (reduce())
            {
                dispstack();
                printf("\t");
                dispinput();
                printf("\tReduced: E -> %s\n", lasthandle);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    if (accepted)
        printf("\nString is ACCEPTED.\n");
    else
        printf("\nString is NOT ACCEPTED.\n");

    return 0;
}
