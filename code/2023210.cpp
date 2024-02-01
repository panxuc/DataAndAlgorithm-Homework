#include <cstdio>

int n = 0, k = 0;

unsigned int firstK_2D[2001] = {0};
unsigned int last2D[2001] = {0};
unsigned int Dj[32] = {0};
unsigned int temp[2001] = {0};
unsigned int dp[2001][2001] = {0};
unsigned int dpDj[2001] = {0};

void input() {
  scanf("%u%u", &n, &k);
  for (auto i = 1; i <= n; i++) {
    for (auto j = 0; j < k - 2; j++) {
      unsigned int tempDj = 0;
      scanf("%u", &tempDj);
      if (tempDj != 1) {
        firstK_2D[i] += (1u << j);
        Dj[j] = tempDj;
      }
    }
    scanf("%u%u", &last2D[i - 1], &last2D[i]);
  }
}

void calculateDpDj(int i) {
  for (auto j = 1; j <= i; j++) {
    temp[j] |= firstK_2D[i];
    dpDj[j] = 1;
    for (auto l = 0; l < k - 2; l++) {
      if (temp[j] & (1u << l)) {
        dpDj[j] *= Dj[l];
      }
    }
    dpDj[j] *= last2D[j - 1] * last2D[i];
  }
}

void updateDp(int i) {
  for (auto j = i - 1; j >= 1; j--) {
    for (auto l = j; l < i; l++) {
      dp[j][i] = dp[j][i] > dp[j][l] + dp[l + 1][i] + dpDj[j] * last2D[l] ||
                         dp[j][i] == 0
                     ? dp[j][l] + dp[l + 1][i] + dpDj[j] * last2D[l]
                     : dp[j][i];
    }
  }
}

int main() {
  input();
  for (auto i = 1; i <= n; i++) {
    calculateDpDj(i);
    updateDp(i);
  }
  printf("%u\n", dp[1][n]);
  return 0;
}
