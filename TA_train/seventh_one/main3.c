#include <stdio.h>

int stringLength(char *a)
{
    int i = 0;
    while (a[i])
    {
        i++;
    }
    return i;
}

int str_to_num(char a)
{
    if (a >= '0' && a <= '9')
        return (int)a - '0';
    else
        return (int)a - 'A' + 10;
}
char num_to_str(char num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'A');
}

char *sum(int a[], int b[], int *out, int length_a)
{

    for (int i = length_a - 1; i >= 0; i--)
    {
        out[i] = a[i] + b[i];
    }

    for (int i = 0; i < length_a; i++)
    {
        if (out[i] > 9)
        {
            out[i] -= 10;
            out[i + 1] += 1;
        }
    }
}

void ShowArray(int a[])
{
    for (int i = 0; i < 10; i++)
    {
        printf("%i , ", a[i]);
    }
    printf("\n");
}
int main()
{

    int n;
    char a[1000];

    int out[1001] = {0};
    int temp[1001] = {0};
    scanf("%i", &n);
    for (int i = 0; i < n; i++)
    {
        int b[1000];
        scanf("%s", a);
        int a_length = stringLength(a);
        for (int i = a_length - 1; i >= 0; i--)
        {
            b[a_length - i - 1] = str_to_num(a[i]);
        }
        for (int i = 0; i <= 1000; i++)
        {
            temp[i] = out[i];
        }

        sum(b, temp, out, stringLength(a));

        // printf("%s",out);
    }

    int first_digit = 0;
    for (int i = 999; i >= 0; i--)
    {
        if (out[i] != 0)
        {
            first_digit = 1;
        }
        if (first_digit)
        {
            printf("%i", out[i]);
        }
    }
    if (!first_digit)
    {
        printf("0");
    }
}