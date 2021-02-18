#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Extend(char *string, int n)
{
    char ch = '*';
    for (int i = 0; i < n; i++)
    {
        strncat(string, &ch, 1);
    }
}

void Print(char *str)
{
    printf("%s\n", str);
}

void shif_l_once(char *string)
{
    int i;
    char temp = string[0];
    int len = strlen(string);
    for (i = 1; i < len; i++)
    {
        string[i - 1] = string[i];
    }
    string[len - 1] = temp;
}
void shif_r_once(char *string)
{
    int i;
    int len = strlen(string);
    char temp = string[len - 1];
    for (i = len - 2; i >= 0; i--)
    {
        string[i + 1] = string[i];
    }
    string[0] = temp;
}

void Shift_R(char *string, int n)
{
    for (int i = 0; i < n; i++)
    {
        shif_r_once(string);
    }
}

void Shift_L(char *string, int n)
{
    for (int i = 0; i < n; i++)
    {
        shif_l_once(string);
    }
}

void Put(char *string, int place, char value)
{
    string[place - 1] = value;
}
void Reverse(char *string)
{
    char *temp = strdup(string);
    int length = strlen(string);
    int place = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        string[place] = temp[i];
        place++;
    }
    free(temp);
}

void Shrink(char *string, int n)
{
    for (int i = strlen(string) - 1; (i >= 0 && n > 0); i--)
    {
        string[i] = '\0';
        n--;
    }
}

int main()
{

    char value[1000];
    scanf("%s", value);
    while (1)
    {

        char cmd[20];
        scanf("%s", cmd);

        if (!strcmp(cmd, "PRINT"))
        {
            Print(value);
        }
        else if (!strcmp(cmd, "SHIFT-L"))
        {
            int n;
            scanf("%i", &n);
            Shift_L(value, n);
        }
        else if (!strcmp(cmd, "SHIFT-R"))
        {
            int n;
            scanf("%i", &n);
            Shift_R(value, n);
        }
        else if (!strcmp(cmd, "EXTEND"))
        {
            int count;
            scanf("%i", &count);
            Extend(value, count);
        }
        else if (!strcmp(cmd, "SHRINK"))
        {
            int n;
            scanf("%i", &n);
            Shrink(value, n);
        }
        else if (!strcmp(cmd, "REVERSE"))
        {
            Reverse(value);
        }
        else if (!strcmp(cmd, "PUT"))
        {
            int place;
            char character;
            scanf("%i", &place);
            scanf(" %c", &character);
            Put(value, place, character);
        }
        else if (!strcmp(cmd, "EXIT"))
        {
            break;
        }
    }
}