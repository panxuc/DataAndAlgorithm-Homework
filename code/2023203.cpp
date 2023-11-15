#include <cstdio>

struct Stack
{
    int data[500000][2] = {0};
    int size = 0;
    void push(int x)
    {
        data[size][0] = x;
        if (size == 0 || x != data[size - 1][0])
            data[size][1] = 1;
        else
            data[size][1] = data[size - 1][1] + 1;
        size++;
    }
    void pop()
    {
        size--;
    }
    void popTillNext()
    {
        size -= data[size - 1][1];
    }
    int *top()
    {
        return data[size - 1];
    }
    bool empty()
    {
        return size == 0;
    }
};

int main()
{
    int N = 0;
    long long count = 0;
    scanf("%d", &N);
    Stack s;
    for (int i = 0; i < N; i++)
    {
        int x = 0;
        scanf("%d", &x);
        while (!s.empty() && s.top()[0] < x)
        {
            count += s.top()[1];
            s.popTillNext();
        }
        if (x == s.top()[0])
        {
            count += s.top()[1];
            if (s.top()[1] < s.size)
                count++;
            s.push(x);
        }
        else
        {
            if (!s.empty())
                count++;
            s.push(x);
        }
    }
    printf("%lld", count);
    return 0;
}