#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>

int n, m;
int src, dest, limit;
int tTime = 0, tCost = 0, mCost = 0x3f3f3f3f;

struct Path {
  int dest;
  int time;
  int cost;
};

struct Node {
  std::vector<Path> path;
};

void dfs(std::vector<Node> &graph, std::vector<int> &time,
         std::vector<int> &cost, std::vector<bool> &visited, int s) {
  if (s == dest) {
    if (tCost < mCost) {
      mCost = tCost;
    }
    return;
  }
  for (int i = 0; i < graph[s].path.size(); i++) {
    int to = graph[s].path[i].dest, t = graph[s].path[i].time,
        c = graph[s].path[i].cost;
    if (tTime + t > limit) {
      continue;
    }
    if (tTime + t >= time[to] && tCost + c >= cost[to]) {
      continue;
    } else if (tTime + t >= time[to]) {
      time[to] = tTime + t;
    } else {
      time[to] = tTime + t;
      cost[to] = tCost + c;
    }
    if (visited[to]) {
      continue;
    }
    tTime += t;
    tCost += c;
    visited[to] = true;
    dfs(graph, time, cost, visited, to);
    tTime -= t;
    tCost -= c;
    visited[to] = false;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  std::vector<Node> graph(n);
  for (int i = 0; i < m; i++) {
    int from, to, t, c;
    scanf("%d%d%d%d", &from, &to, &t, &c);
    graph[from].path.push_back({to, t, c});
  }
  scanf("%d%d%d", &src, &dest, &limit);
  std::vector<int> time(n, 0x3f3f3f3f);
  std::vector<int> cost(n, 0x3f3f3f3f);
  std::vector<bool> visited(n, false);
  visited[src] = true;
  dfs(graph, time, cost, visited, src);
  printf("%d\n", mCost == 0x3f3f3f3f ? -1 : mCost);
  return 0;
}
