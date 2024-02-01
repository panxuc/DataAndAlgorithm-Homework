#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

#define THRESHOLD_NEWTON 1e-4
#define THRESHOLD_CHEBYSHEV 1e-10
#define THRESHOLD_N 20

#define CHEBYSHEV_SCALE 1.0

int n, m;
int fit;
double max = -1e10, min = 1e10;
double x[101] = {0}, y[101] = {0}, nt[101][101] = {0};
double cb[101][101] = {0}, s1[101][101] = {0}, s2[101] = {0};
double t1[101][101] = {0}, t2[101] = {0}, t3[101] = {0};

void inputXY() {
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &x[i], &y[i]);
  }
}

void newtonNT() {
  nt[0][0] = y[0];
  for (int i = 1; i < n; i++) {
    nt[i][0] = y[i];
    for (int j = 1; j <= i; j++) {
      nt[i][j] = (nt[i][j - 1] - nt[i - 1][j - 1]) / (x[i] - x[i - j]);
    }
  }
}

int newtonFit() {
  for (int i = n - 1; i >= 0; i--) {
    if (nt[i][i] > THRESHOLD_NEWTON || nt[i][i] < -THRESHOLD_NEWTON) {
      return i;
    }
  }
  return -1;
}

double newtonCalc(double t) {
  double w = 1;
  double z = nt[0][0];
  for (int j = 1; j < n; j++) {
    w *= (t - x[j - 1]);
    if (nt[j][j] > THRESHOLD_NEWTON || nt[j][j] < -THRESHOLD_NEWTON) {
      z += nt[j][j] * w;
    }
  }
  return z;
}

void chebyshevCB(double x, double *cb) {
  cb[0] = 1;
  cb[1] = x;
  for (int i = 2; i < n; i++) {
    cb[i] = 2 * x * cb[i - 1] - cb[i - 2];
  }
}

void chebyshevScale() {
  for (int i = 0; i < n; i++) {
    if (x[i] < min) {
      min = x[i];
    }
    if (x[i] > max) {
      max = x[i];
    }
  }
  if (min == max) {
    min = min - 1;
    max = max + 1;
  }
  for (int i = 0; i < n; i++) {
    x[i] = (2 * x[i] * CHEBYSHEV_SCALE - max - min) / (max - min);
    chebyshevCB(x[i], cb[i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      s2[i] += y[j] * cb[j][i];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        s1[i][j] += cb[k][i] * cb[k][j];
      }
    }
  }
}

bool testFit() {
  memcpy(t1, s1, sizeof(s1));
  memcpy(t2, s2, sizeof(s2));
  for (int i = 0; i <= fit; i++) {
    int s = i;
    for (int j = i + 1; j <= fit; j++) {
      if (std::abs(t1[j][i]) > std::abs(t1[s][i])) {
        s = j;
      }
    }
    if (s != i) {
      for (int j = i; j <= fit; j++) {
        std::swap(t1[s][j], t1[i][j]);
      }
      std::swap(t2[s], t2[i]);
    }
    for (int j = i + 1; j <= fit; j++) {
      double ratio = t1[j][i] / t1[i][i];
      for (int k = i; k <= fit; k++) {
        t1[j][k] -= ratio * t1[i][k];
      }
      t2[j] -= ratio * t2[i];
    }
  }
  for (int i = fit; i >= 0; i--) {
    t2[i] /= t1[i][i];
    for (int j = i - 1; j >= 0; j--) {
      t2[j] -= t2[i] * t1[j][i];
    }
  }
  for (int i = 0; i < n; i++) {
    double yy = 0;
    for (int j = 0; j <= fit; j++) {
      yy += t2[j] * cb[i][j];
    }
    if (std::abs(yy - y[i]) >= THRESHOLD_CHEBYSHEV) {
      return false;
    }
  }
  return true;
}

void chebyshevFit() {
  for (fit = 0; fit < n; fit++) {
    if (testFit()) {
      return;
    }
  }
}

double chebyshevCalc(double t) {
  memset(t3, 0, sizeof(t3));
  t3[0] = 1;
  t3[1] = t;
  double ret = 0;
  for (int i = 2; i <= fit; i++) {
    t3[i] = 2 * t * t3[i - 1] - t3[i - 2];
  }
  for (int i = 0; i <= fit; i++) {
    ret += t3[i] * t2[i];
  }
  return ret;
}

int main() {
  scanf("%d%d", &n, &m);
  if (n <= THRESHOLD_N) {
    inputXY();
    newtonNT();
    fit = newtonFit();
    printf("%d\n", fit);
    for (int i = 0; i < m; i++) {
      double t;
      scanf("%lf", &t);
      printf("%lf\n", newtonCalc(t));
    }
  } else {
    inputXY();
    chebyshevScale();
    chebyshevFit();
    printf("%d\n", fit);
    for (int i = 0; i < m; i++) {
      double t;
      scanf("%lf", &t);
      t = (2 * t * CHEBYSHEV_SCALE - max - min) / (max - min);
      printf("%lf\n", chebyshevCalc(t));
    }
  }
  return 0;
}
