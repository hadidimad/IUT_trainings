#include <stdio.h>

char convertionTable[8][4] = {
    {"000"},
    {"001"},
    {"010"},
    {"011"},
    {"100"},
    {"101"},
    {"110"},
    {"111"},
};
int convertionResult[8] = {0, 1, 2, 3, 4, 5, 6, 7};

//here three digit binary code goes
int convertDigit(char a[])
{
    int equal = 1;
    for (int i = 0; i < 8; i++)
    {
        equal = 1;
        for (int j = 0; j < 3; j++)
        {
            if (convertionTable[i][j] != a[j])
            {
                equal = 0;
            }
        }
        if (equal)
        {
            return convertionResult[i];
        }
    }
}
int stringLength(char *a)
{
    int i = 0;
    while (a[i])
    {
        i++;
    }
    return i;
}

void shiftStirngRight(char a[], int length, int count)
{
    // printf("shiftin a in %d \n", count);

    for (int i = length; i >= 0; i--)
    {

        a[i + count] = a[i];
        // printf("%c %c \n", a[i + count], a[i]);
    }
    // printf("a is %s in length of %i\n", a, length);

    for (int i = 0; i < count; i++)
    {

        a[i] = '0';
    }
}

int convertTo8base(char a[], int length)
{
    int output = 0;
    // printf("a is %s in length of %i\n", a, length);

    if (length % 3 != 0)
    {
        shiftStirngRight(a, length, (length % 3) + 1);
        length += (length % 3) + 1;
    }
    // printf("a is %s in length of %i\n", a, length);

    for (int i = 0; i < length; i += 3)
    {
        output *= 10;
        char slice[4] = {a[i], a[i + 1], a[i + 2], '\0'};
        // printf("sliceis %s \n", slice);
        output += convertDigit(slice);
    }
    return output;
}

int main()
{
    int output;
    char input[18];

    scanf("%s", input);
    printf("%i", convertTo8base(input, stringLength(input)));
}