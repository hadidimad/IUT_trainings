#include <stdio.h>
int ways[3] = {1, 2, 5};
int ways_counter = 0;
void go_go_go(int reamin_steps)
{
    if (reamin_steps == 0)
    {
        ways_counter++;
        return;
    }
    for (int i = 0; i < 3; i++)
    {

        if (reamin_steps >= ways[i])
        {
            go_go_go(reamin_steps - ways[i]);
        }
    }
}

int main()
{
    int n;
    scanf("%i", &n);

    go_go_go(n);
    printf("%i", ways_counter);
}