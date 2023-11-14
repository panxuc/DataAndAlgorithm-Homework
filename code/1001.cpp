#include <cstdio>
#include <cstring>

void reverse(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main()
{
    char a[200];
    char b[200];
    char ret[200];
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(ret, 0, sizeof(ret));
    scanf("%s%s", a, b);
    reverse(a);
    reverse(b);
    for (int i = 0; a[i] + b[i] > 0; i++)
    {
        if (a[i] == 0)
            a[i] = '0';
        if (b[i] == 0)
            b[i] = '0';
        ret[i] += a[i] + b[i] - '0';
        if (ret[i] > '9')
        {
            ret[i] -= 10;
            ret[i + 1] += 1;
        }
    }
    if (ret[strlen(ret) - 1] > 0 && ret[strlen(ret) - 1] < '0')
    {
        ret[strlen(ret) - 1] += '0';
    }
    reverse(ret);
    printf("%s\n", ret);
    return 0;
}