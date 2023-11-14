#include <cstdio>

int queue[100000][2] = {0};

void insert(int id, int pos)
{
    queue[id][0] = pos;
    queue[id][1] = queue[pos][1];
    queue[pos][1] = id;
    if (queue[id][1] != 0)
    {
        queue[queue[id][1]][0] = id;
    }
}

void report(int id)
{
    printf("%d\n", queue[id][1]);
}

void remove(int id)
{
    queue[queue[id][0]][1] = queue[id][1];
    if (queue[id][1] != 0)
    {
        queue[queue[id][1]][0] = queue[id][0];
    }
}

void display()
{
    int i = queue[0][1];
    while (i != 0)
    {
        printf("%d\n", i);
        i = queue[i][1];
    }
}

int main()
{
    int N = 0, command = 0;
    insert(1, 0);
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &command);
        if (command == 1)
        {
            int id = 0, pos = 0;
            scanf("%d%d", &pos, &id);
            insert(id, pos);
        }
        else if (command == 2)
        {
            int id = 0;
            scanf("%d", &id);
            report(id);
        }
        else if (command == 3)
        {
            int id = 0;
            scanf("%d", &id);
            remove(id);
        }
    }
    display();
    return 0;
}