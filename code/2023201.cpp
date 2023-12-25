#include <cstdio>

int ternaryPlus(int a, int b) {
  if (a + b < 3) {
    return a + b;
  } else {
    return a + b - 3;
  }
}

int main() {
  int num = 0;
  int temp = 0;
  int ret[32] = {0};
  int ans = 0;
  scanf("%d", &num);
  for (int i = 0; i < 3 * num - 1; i++) {
    scanf("%d", &temp);
    for (int j = 0; j < 32; j++) {
      ret[j] = ternaryPlus(ret[j], temp & 1);
      temp >>= 1;
      if (temp == 0) {
        break;
      }
    }
  }
  for (int i = 0; i < 32; i++) {
    if (ret[i]) {
      ans += 1 << i;
    }
  }
  printf("%d", ans);
  return 0;
}