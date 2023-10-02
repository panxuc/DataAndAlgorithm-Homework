#include <cstdio>

#define MOD 9973

struct Matrix
{
    long long a[2][2];
    Matrix()
    {
        a[0][0] = 0;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = 0;
    }
    Matrix(long long a, long long b, long long c, long long d)
    {
        this->a[0][0] = a;
        this->a[0][1] = b;
        this->a[1][0] = c;
        this->a[1][1] = d;
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ret;
        ret.a[0][0] = (a[0][0] * b.a[0][0] + a[0][1] * b.a[1][0]) % MOD;
        ret.a[0][1] = (a[0][0] * b.a[0][1] + a[0][1] * b.a[1][1]) % MOD;
        ret.a[1][0] = (a[1][0] * b.a[0][0] + a[1][1] * b.a[1][0]) % MOD;
        ret.a[1][1] = (a[1][0] * b.a[0][1] + a[1][1] * b.a[1][1]) % MOD;
        return ret;
    }
};

Matrix pow(Matrix a, long long b)
{
    Matrix ret(1, 0, 0, 1);
    while (b)
    {
        if (b & 1)
            ret = ret * a;
        a = a * a;
        b >>= 1;
    }
    return ret;
}

long long fibo(long long n)
{
    if (n == 0 || n == 1)
    {
        return n;
    }
    else
    {
        Matrix a(1, 1, 1, 0);
        Matrix ret = pow(a, n);
        return ret.a[0][1];
    }
}

int main()
{
    int num = 0;
    scanf("%d", &num);
    long long n[num];
    for (int i = 0; i < num; i++)
    {
        scanf("%lld", &n[i]);
    }
    for (int i = 0; i < num; i++)
    {
        printf("%lld\n", fibo(n[i]));
    }
    return 0;
}