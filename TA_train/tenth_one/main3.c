#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    int count = 0, c = 0, i = 0, j = 0, k, l, size = 0;
    char p[50][100], cmp[100];
    while (1)
    {
        scanf("%s", cmp);
        if (!strcmp(cmp, "0"))
        {
            break;
        }
        strcpy(p[size], cmp);
        size++;
    }
    size--;
    for (i = 0; i < size; i++) //loop for sorting
    {
        for (j = i + 1; j <= size; j++)
        {

            char a = (p[i][0] >= 'A' && p[i][0] <= 'Z') ? (p[i][0] + ('a' - 'A')) : p[i][0];
            char b = (p[j][0] >= 'A' && p[j][0] <= 'Z') ? (p[j][0] + ('a' - 'A')) : p[j][0];

            if (a == b)
            {
                if (p[i][0] < p[j][0])
                {
                    strcpy(cmp, p[i]);
                    strcpy(p[i], p[j]);
                    strcpy(p[j], cmp);
                }
                else
                {
                    char aa = (p[i][1] >= 'A' && p[i][1] <= 'Z') ? (p[i][1] + ('a' - 'A')) : p[i][1];
                    char bb = (p[j][1] >= 'A' && p[j][1] <= 'Z') ? (p[j][1] + ('a' - 'A')) : p[j][1];
                    if (aa == bb)
                    {
                        // if (p[i][0] > p[j][0])
                        // {
                        //     strcpy(cmp, p[i]);
                        //     strcpy(p[i], p[j]);
                        //     strcpy(p[j], cmp);
                        // }
                    }
                    else if (aa > bb)
                    {
                        strcpy(cmp, p[i]);
                        strcpy(p[i], p[j]);
                        strcpy(p[j], cmp);
                    }
                }
            }
            else if (a > b)
            {
                strcpy(cmp, p[i]);
                strcpy(p[i], p[j]);
                strcpy(p[j], cmp);
            }
        }
    }
    printf("After sorting string is \n");
    for (i = 0; i <= size; i++)
    {
        printf("%s ", p[i]);
    }
}