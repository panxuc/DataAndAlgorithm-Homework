#include <cstdio>

int main() {
  int p = 0, n = 0, m = 0;
  scanf("%d", &p);
  scanf("%d%d", &n, &m);
  if (p == 3) {
    double a[n] = {0}, b[n] = {0}, c[n] = {0};
    for (int i = 0; i < n - 1; i++) {
      scanf("%lf", &c[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%lf", &b[i]);
    }
    for (int i = 1; i < n; i++) {
      scanf("%lf", &a[i]);
    }
    // LU分解
    for (int i = 1; i < n; i++) {
      a[i] = a[i] / b[i - 1];
      b[i] = b[i] - a[i] * c[i - 1];
    }
    double z[n] = {0};
    for (int i = 0; i < m; i++) {
      // 输入
      for (int j = 0; j < n; j++) {
        scanf("%lf", &z[j]);
      }
      // 前代
      for (int j = 1; j < n; j++) {
        z[j] = z[j] - a[j] * z[j - 1];
      }
      // 后代
      z[n - 1] = z[n - 1] / b[n - 1];
      for (int j = n - 2; j >= 0; j--) {
        z[j] = (z[j] - c[j] * z[j + 1]) / b[j];
      }
      // 输出
      for (int j = 0; j < n - 1; j++) {
        printf("%.4lf ", z[j]);
      }
      printf("%.4lf\n", z[n - 1]);
    }
  }
  if (p == 5) {
    double a[n] = {0}, b[n] = {0}, c[n] = {0}, d[n] = {0}, e[n] = {0};
    for (int i = 0; i < n - 2; i++) {
      scanf("%lf", &e[i]);
    }
    for (int i = 0; i < n - 1; i++) {
      scanf("%lf", &d[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%lf", &c[i]);
    }
    for (int i = 1; i < n; i++) {
      scanf("%lf", &b[i]);
    }
    for (int i = 2; i < n; i++) {
      scanf("%lf", &a[i]);
    }
    // LU分解
    d[0] = d[0] / c[0];
    e[0] = e[0] / c[0];
    c[1] = c[1] - b[1] * d[0];
    d[1] = (d[1] - b[1] * e[0]) / c[1];
    e[1] = e[1] / c[1];
    for (int i = 2; i < n; i++) {
      b[i] = b[i] - a[i] * d[i - 2];
      c[i] = c[i] - a[i] * e[i - 2] - b[i] * d[i - 1];
      d[i] = (d[i] - b[i] * e[i - 1]) / c[i];
      e[i] = e[i] / c[i];
    }
    double z[n] = {0};
    for (int i = 0; i < m; i++) {
      // 输入
      for (int j = 0; j < n; j++) {
        scanf("%lf", &z[j]);
      }
      // 前代
      z[0] = z[0] / c[0];
      z[1] = (z[1] - b[1] * z[0]) / c[1];
      for (int j = 2; j < n; j++) {
        z[j] = (z[j] - a[j] * z[j - 2] - b[j] * z[j - 1]) / c[j];
      }
      // 后代
      z[n - 2] = z[n - 2] - d[n - 2] * z[n - 1];
      for (int j = n - 3; j >= 0; j--) {
        z[j] = z[j] - d[j] * z[j + 1] - e[j] * z[j + 2];
      }
      // 输出
      for (int j = 0; j < n - 1; j++) {
        printf("%.4lf ", z[j]);
      }
      printf("%.4lf\n", z[n - 1]);
    }
  }
}