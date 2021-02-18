#include <stdio.h>

int main()
{
    char temp;
    int right = 0, left = 0, actions = 0;
    while (1)
    {
        // scanf("%c", &temp);
        temp = getchar();

        if (temp == EOF)
        {
            break;
        }
        (temp == '(') ? right++ : left++;
    }
    getchar();

    while (right != left)
    {
        if (right > left)
        {
            right--;
            left++;
            actions++;
        }
        else
        {
            left--;
            right++;
            actions++;
        }
    }
    printf("%i", actions);
}