
#include <stdio.h>

char arr[18][3] = {
    {'E', '+', ' '}, {'E', '*', ' '},
    {'E', '(', ' '}, {'E', ')', ' '},
    {'E', 'i', ' '}, {'E', '$', ' '},

    {'F', '+', ' '}, {'F', '*', ' '},
    {'F', '(', ' '}, {'F', ')', ' '},
    {'F', 'i', ' '}, {'F', '$', ' '},

    {'T', '+', ' '}, {'T', '*', ' '},
    {'T', '(', ' '}, {'T', ')', ' '},
    {'T', 'i', ' '}, {'T', '$', ' '}
};

void install(char pro, char re)
{
    int i;

    for (i = 0; i < 18; i++)
    {
        if (arr[i][0] == pro && arr[i][1] == re)
        {
            if (arr[i][2] != 'T')
            {
                arr[i][2] = 'T';
            }
            return;
        }
    }
}

int main()
{
    int i, change;

    // Direct FIRSTVT rules
    install('E', '+');
    install('T', '*');
    install('F', '(');
    install('F', 'i');

    // FIRSTVT propagation
    do
    {
        change = 0;

        for (i = 0; i < 18; i++)
        {
            if (arr[i][2] == 'T')
            {
                char pro = arr[i][0];
                char re = arr[i][1];

                if (pro == 'T')
                {
                    int j;
                    for (j = 0; j < 18; j++)
                    {
                        if (arr[j][0] == 'E' &&
                            arr[j][1] == re &&
                            arr[j][2] != 'T')
                        {
                            install('E', re);
                            change = 1;
                        }
                    }
                }

                if (pro == 'F')
                {
                    int j;
                    for (j = 0; j < 18; j++)
                    {
                        if (arr[j][0] == 'T' &&
                            arr[j][1] == re &&
                            arr[j][2] != 'T')
                        {
                            install('T', re);
                            change = 1;
                        }
                    }
                }
            }
        }

    } while (change);

    // Display FIRSTVT table
    printf("\nFIRSTVT TABLE\n");

    for (i = 0; i < 18; i++)
    {
        printf("\n\t%c\t%c\t%c",
               arr[i][0], arr[i][1], arr[i][2]);
    }

    printf("\n\nFIRSTVT SETS\n");

    for (i = 0; i < 18; i++)
    {
        if (i == 0 || arr[i][0] != arr[i - 1][0])
        {
            printf("\n%c -> ", arr[i][0]);
        }

        if (arr[i][2] == 'T')
        {
            printf("%c ", arr[i][1]);
        }
    }

    printf("\n");

    return 0;
}
