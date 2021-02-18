#include <stdio.h>
#include <stdlib.h>
typedef struct _stack
{
    int *items;
    int length;
} Stack;

Stack init()
{
    Stack s;
    s.items = (int *)malloc(0);
    s.length = 0;
    return s;
}

void append(Stack *s, int item)
{
    s->items = realloc(s->items, ((s->length) + 1) * sizeof(int));
    (s->items[s->length]) = item;
    s->length++;
}
void pop(Stack *s)
{
    free(&(s->items[s->length]));
    s->length--;
}

int main()
{
    int tests;
    scanf("%i", &tests);
    for (int i = 0; i < tests; i++)
    {
        int n;
        scanf("%i", &n);
        Stack *map;
        map = malloc(sizeof(Stack) * n);
        for (int j = 0; j < n; j++)
        {
            map[j] = init();
            for (int k = 0; k < n; k++)
            {
                int temp;
                scanf("%i", &temp);
                append(&map[j], temp);
            }
        }
        
    }
}