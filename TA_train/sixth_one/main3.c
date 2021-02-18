#include <stdio.h>

void get_distance(int n)
{
    int cursor_head = 0;
    int counter = 0;
    int x = 0, y = 0;
    int moving_length = 0;
    while (counter < n - 1)
    {
        if ((counter % 2) == 0)
        {
            moving_length++;
        }
        switch (cursor_head)
        {
        case 0:
            x += moving_length;
            break;
        case 1:
            y += moving_length;
            break;
        case 2:
            x -= moving_length;
            break;
        case 3:
            y -= moving_length;
            break;
        }
        cursor_head++;
        cursor_head = (cursor_head > 3) ? 0 : cursor_head;
        counter++;
    }
    printf("%i %i", x, y);
}

int main()
{
    int n = 0;
    scanf("%i", &n);
    get_distance(n);
}