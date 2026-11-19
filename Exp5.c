#include <stdio.h>
int main()
{
    char str[1000];
    int words = 0, newline = 0, characters = 0;
    int inWord = 0;
    int i;

    printf("Enter text (press ~ to finish):\n");

    scanf("%999[^~]", str);

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            newline++;
        }

        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
        {
            characters++;

            if (inWord == 0)
            {
                words++;
                inWord = 1;
            }
        }
        else
        {
            inWord = 0;
        }
    }

    if (i > 0 && str[i - 1] != '\n')
    {
        newline++;
    }

    printf("\nTotal number of words: %d\n", words);
    printf("Total number of lines: %d\n", newline);
    printf("Total number of characters: %d\n", characters);

    return 0;
}