#include <stdio.h>
#include <stdlib.h>

int stringLength(char *a)
{
    int i = 0;
    while (a[i] != '\n')
    {
        i++;
    }
    return i;
}
void getLine(char *input)
{
    int i = 0;
    input[i] = getchar();

    while (1)
    {
        if (input[i] == '\n')
        {
            break;
        }
        i++;
        input[i] = getchar();
    }
}

int main()
{
    int n;
    char a[10];
    fgets(a, 10, stdin);
    n = atoi(a);
    // scanf("%i\n", &n);

    for (int i = 0; i < n; i++)
    {
        char name[1000] = {0};

        fgets(name, 1000, stdin);

        int shouldChange = 0;
        for (int j = 0; j < stringLength(name); j++)
        {
            if (shouldChange || j == 0)
            {
                shouldChange = 0;
                if (name[j] >= 'a' && name[j] <= 'z')
                {
                    name[j] -= ('a' - 'A');
                }
            }
            else
            {
                if (name[j] != ' ')
                {
                    if (name[j] <= 'Z' && name[j] >= 'A')
                    {
                        name[j] += ('a' - 'A');
                    }
                }
            }

            if (name[j] == ' ')
            {
                shouldChange = 1;
            }
        }
        printf("%s", name);
    }
    return 0;
}
