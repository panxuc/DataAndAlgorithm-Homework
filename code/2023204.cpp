#include <cstdio>

int main() {
  int N = 0, M = 0;
  scanf("%d%d", &N, &M);
  unsigned int colo[N] = {0};
  unsigned int dest[M] = {0};
  for (int i = 0; i < N; i++) {
    scanf("%d", &colo[i]);
  }
  for (int i = 0; i < M; i++) {
    scanf("%d", &dest[i]);
  }
  unsigned int path[200] = {0};
  for (int i = 0; i < M; i++) {
    if (dest[i] == 1) {
      printf("1\n");
    } else {
      path[0] = dest[i];
      bool noPath = false;
      unsigned int temp = 0;
      int lastJ = 0;
      for (int j = 1; j < 132; j++) {
        temp = path[j - 1] / 2;
        for (int k = 0; k < N; k++) {
          if (colo[k] <= temp) {
            temp++;
          } else {
            break;
          }
          if (temp >= path[j - 1]) {
            break;
          }
        }
        if (temp >= path[j - 1]) {
          noPath = true;
          break;
        } else {
          path[j] = temp;
          if (temp == 1) {
            lastJ = j;
            break;
          }
        }
      }
      if (noPath) {
        printf("0\n");
      } else {
        for (int j = lastJ; j >= 0; j--) {
          printf(j == 0 ? "%u\n" : "%u ", path[j]);
        }
      }
    }
  }
  return 0;
}