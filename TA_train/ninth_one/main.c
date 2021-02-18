#include <stdio.h>
#include <string.h>
#include <ctype.h>

void lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

int main()
{
    char key[100];
    scanf("%s", key);
    lowercase(key);
    int n, chosenWords = 0;
    scanf("%i", &n);
    for (int i = 0; i < n; i++)
    {
        char word[10000];
        scanf("%s", word);
        lowercase(word);

        if (strstr(word, key))
        {
            chosenWords++;
        }
    }
    printf("%i", chosenWords);
}