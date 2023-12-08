#include <cstdio>
#include <vector>

typedef struct Node
{
    std::vector<unsigned short> next;
};

int main()
{
    int N = 0, M = 0;
    scanf("%d%d", &N, &M);
    std::vector<Node> node(N);
    std::vector<unsigned short> fromNum(N, 0);
    unsigned short nextNum = 0;
    unsigned short nextIndex = 0;
    for (int i = 0; i < N; i++)
    {
        scanf("%hu", &nextNum);
        for (int j = 0; j < nextNum; j++)
        {
            scanf("%hu", &nextIndex);
            node[i].next.push_back(nextIndex);
        }
    }
    std::vector<unsigned short> queue;
    std::vector<bool> visited(N, false);
    queue.push_back(0);
    visited[0] = true;
    for (int i = 0; i < queue.size(); i++)
    {
        unsigned short index = queue[i];
        for (int j = 0; j < node[index].next.size(); j++)
        {
            unsigned short next = node[index].next[j];
            fromNum[next]++;
            if (!visited[next])
            {
                queue.push_back(next);
                visited[next] = true;
            }
        }
    }
    bool flag = queue.size() == N;
    // queue.clear();
    // visited.assign(N, false);
    if (flag)
    {
        printf("1\n");
        for (int i = 0; i < M; i++)
        {
            unsigned short from = 0, to = 0;
            scanf("%hu%hu", &from, &to);
            if (to == 0)
            {
                printf("1\n");
            }
            else
            {
                if (fromNum[to] == 1)
                {
                    bool PathExists = false;
                    for (int j = 0; j < node[from].next.size(); j++)
                    {
                        if (node[from].next[j] == to)
                        {
                            PathExists = true;
                            printf("0\n");
                            break;
                        }
                    }
                    if (!PathExists)
                    {
                        printf("1\n");
                    }
                }
                else
                {
                    std::vector<unsigned short> queue;
                    std::vector<bool> visited(N, false);
                    queue.push_back(0);
                    visited[0] = true;
                    bool flag = false;
                    for (int j = 0; j < queue.size(); j++)
                    {
                        unsigned short index = queue[j];
                        for (int k = 0; k < node[index].next.size(); k++)
                        {
                            unsigned short next = node[index].next[k];
                            if (!visited[next] && !(index == from && next == to))
                            {
                                queue.push_back(next);
                                visited[next] = true;
                                if (next == to)
                                {
                                    flag = true;
                                    break;
                                }
                            }
                        }
                        if (flag)
                        {
                            break;
                        }
                    }
                    printf("%d\n", flag ? 1 : 0);
                    // queue.clear();
                    // visited.assign(N, false);
                }
            }
        }
    }
    else
    {
        printf("0\n");
        for (int i = 0; i < M; i++)
        {
            printf("0\n");
        }
    }
}