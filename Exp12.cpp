
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i, l;

// Function declarations
int E();
int T();
int F();
int EP();
int TP();

// E -> TE'
int E()
{
    if (T())
    {
        if (EP())
            return 1;
    }
    return 0;
}

// E' -> +TE' | epsilon
int EP()
{
    if (input[i] == '+')
    {
        i++;

        if (T())
        {
            if (EP())
                return 1;
        }
        return 0;
    }

    return 1;
}

// T -> FT'
int T()
{
    if (F())
    {
        if (TP())
            return 1;
    }
    return 0;
}

// T' -> *FT' | epsilon
int TP()
{
    if (input[i] == '*')
    {
        i++;

        if (F())
        {
            if (TP())
                return 1;
        }
        return 0;
    }

    return 1;
}

// F -> (E) | ID
int F()
{
    if (input[i] == '(')
    {
        i++;

        if (E())
        {
            if (input[i] == ')')
            {
                i++;
                return 1;
            }
        }
        return 0;
    }

    // ID
    if (isalpha((unsigned char)input[i]) ||
        isdigit((unsigned char)input[i]))
    {
        i++;
        return 1;
    }

    return 0;
}

// Main function
int main()
{
    printf("\nRecursive Descent Parsing\n");

    printf("\nGrammar:");
    printf("\nE  -> TE'");
    printf("\nE' -> +TE' / epsilon");
    printf("\nT  -> FT'");
    printf("\nT' -> *FT' / epsilon");
    printf("\nF  -> (E) / ID");

    printf("\n\nEnter the input string: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;

    // Remove newline and spaces
    int j = 0;
    for (int k = 0; input[k] != '\0'; k++)
    {
        if (!isspace((unsigned char)input[k]))
            input[j++] = input[k];
    }
    input[j] = '\0';

    l = strlen(input);
    i = 0;

    if (E() && i == l)
    {
        printf("\n\nString is ACCEPTED.");
    }
    else
    {
        printf("\n\nString is NOT ACCEPTED.");
    }

    return 0;
}
