#include <stdio.h>

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

typedef struct _team
{
    int id;
    int win;
    int lose;
    int draw;
    int money;
    char *name;

    Stack players;
} Team;

typedef struct _player
{
    int id;
    char *name;
    int price;
    int speed;
    int finishing;
    int defence;
} Player;

typedef struct _field
{
    Stack teams;
    Stack players;
} Field;

Field init_field()
{
    Field f;
    f.teams = init();
    f.players = init();
    return f;
}

int main()
{
}