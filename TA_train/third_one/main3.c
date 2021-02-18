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

int val(char c)
{
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else
        return (int)c - 'A' + 10;
}

int toDeci(char *str, int base)
{
    int len = stringLength(str);
    int power = 1;
    int num = 0;
    int i;

    for (i = len - 1; i >= 0; i--)
    {
        
        num += val(str[i]) * power;
        power = power * base;
    }

    return num;
}

char reVal(int num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'A');
}


int main()
{
    int inBase, outBase;
    char N[15];
    scanf("%s", N);
    scanf("%i %i", &inBase, &outBase);
    int isEqual = 1;
    int decimal = toDeci(N, inBase);
    int index = 0;
    while (decimal > 0)
    {
        N[index++] = reVal(decimal % outBase);
        decimal /= outBase;
    }
    N[index] = '\0';
    int length = stringLength(N);
    for (int i = 0; i < length; i++)
    {
        if (N[i] != N[length - i - 1])
        {
            isEqual = 0;
        }
    }
    printf((isEqual) ? "YES" : "NO");
    return 0;
}