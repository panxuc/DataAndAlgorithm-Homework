#include <cstdio>
#include <vector>

void add(std::vector<int> &v, int x) {
  int l = 0, r = v.size();
  while (l < r) {
    int m = (l + r) / 2;
    if (v[m] < x) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  v.insert(v.begin() + l, x);
}

int find(std::vector<int> &v, int x) {
  int l = 0, r = v.size();
  while (l < r) {
    int m = (l + r) / 2;
    if (v[m] < x) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return l;
}

int findLeq(std::vector<int> &v, long long x) {
  int l = 0, r = v.size();
  while (l < r) {
    int m = (l + r) / 2;
    if (v[m] <= x) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  if (l > 0) {
    --l;
  }
  return l;
}

int findGeq(std::vector<int> &v, long long x) {
  int l = 0, r = v.size();
  while (l < r) {
    int m = (l + r) / 2;
    if (v[m] < x) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return l;
}

int main() {
  int m, k, h;
  scanf("%d%d%d", &m, &k, &h);
  std::vector<int> l;
  std::vector<int> q;
  long long cnt = 0;
  for (int i = 0; i < m; ++i) {
    int x;
    scanf("%d", &x);
    if (l.size() > 0 && !((long long)x + (long long)h < l.front() ||
                          (long long)x - (long long)h > l.back())) {
      cnt += findLeq(l, (long long)x + (long long)h) -
             findGeq(l, (long long)x - (long long)h) + 1;
    }
    q.push_back(x);
    add(l, x);
    if (i >= k) {
      l.erase(l.begin() + find(l, q.front()));
      q.erase(q.begin());
    }
  }
  printf("%lld\n", cnt);
  return 0;
}