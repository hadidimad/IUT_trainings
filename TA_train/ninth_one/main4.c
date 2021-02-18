#include <stdio.h>
#include <string.h>

int getLastNode(char *a, char *b)
{
    int node = -1;

    for (int i = 0; (strlen(a) < strlen(b)) ? a[i] : b[i]; i++)
    {
        if (a[i] == b[i])
        {
            node = i;
        }
        else
        {
            return node;
        }
    }
    return node;
}
int getTime(char *string, int node)
{
    return strlen(string) - node - 1;
}

int main()
{
    int a2b_time, b2a_time, a_length, b_length;
    scanf("%i", &a_length);
    char a[a_length + 1];
    scanf("%s", a);
    scanf("%i", &b_length);
    char b[b_length + 1];
    scanf("%s", b);
    int node = getLastNode(a, b);
    a2b_time = getTime(a, node);
    b2a_time = getTime(b, node);
    printf("%i", a2b_time + b2a_time);
}