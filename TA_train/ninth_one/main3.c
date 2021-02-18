#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    int n;
    int caps = 0;
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        char word[5];
        scanf("%s", word);

        if (!strcmp(word, "CAPS"))
        {
            caps = !caps;
        }
        else
        {
            printf("%c", (caps) ? toupper(word[0]) : tolower(word[0]));
        }
    }
}