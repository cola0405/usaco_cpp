#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int M = 4e5 + 10;
// 存储从每个城镇出发的边指向的城镇
vector<int> edges[N];
// 存储指向每个城镇的边的起始城镇
vector<int> incomingEdges[N];
// 存储每条边的标签
vector<int> edgeLabels[N];

// 存储从每个城镇出发的最长行程的深度
int depth[N];
// 存储每个城镇的出度
int outDegree[N];
// 存储每个城镇的最优后继城镇
int nextTown[N];
// 存储每个城镇的最优后继边的标签
int bestEdgeLabel[N];
// 存储每个城镇的排名
int rankTown[N];
// 存储从每个城镇出发的最长行程的路径标签总和
ll labelSum[N];
// 用于排序的辅助数组
int townIds[N];

int main() {
    int n, m;
    // 读取城镇数量和道路数量
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, l;
        // 读取每条道路的起始城镇、终点城镇和标签
        scanf("%d%d%d", &u, &v, &l);
        edges[u].push_back(v);
        edgeLabels[u].push_back(l);
        incomingEdges[v].push_back(u);
        outDegree[u]++;
    }

    vector<int> currentLengthTowns;
    vector<int> nextLengthTowns;
    // 初始化出度为 0 的城镇
    for (int i = 1; i <= n; i++) {
        if (!outDegree[i]) {
            depth[i] = 1;
            currentLengthTowns.push_back(i);
            labelSum[i] = 0;
        }
    }

    int currentLength = 1;
    while (!currentLengthTowns.empty()) {
        // 增加当前行程长度
        ++currentLength;
        // 处理当前长度的城镇
        for (int v : currentLengthTowns) {
            for (int u : incomingEdges[v]) {
                if (--outDegree[u] == 0) {
                    nextLengthTowns.push_back(u);
                    depth[u] = currentLength;
                    bestEdgeLabel[u] = 1e9 + 7;
                }
            }
        }
        // 为每个城镇选择最优后继城镇
        for (int u : nextLengthTowns) {
            for (int i = 0; i < edges[u].size(); i++) {
                int v = edges[u][i];
                int l = edgeLabels[u][i];
                if (depth[v] == currentLength - 1) {
                    if (l < bestEdgeLabel[u]) {
                        bestEdgeLabel[u] = l;
                        nextTown[u] = v;
                        labelSum[u] = labelSum[v] + l;
                    } else if (l == bestEdgeLabel[u] && rankTown[v] < rankTown[nextTown[u]]) {
                        nextTown[u] = v;
                        labelSum[u] = labelSum[v] + l;
                    }
                }
            }
        }
        // 对下一个长度的城镇进行排序并排名
        int cnt = 0;
        for (int u : nextLengthTowns) {
            townIds[++cnt] = u;
        }
        sort(townIds + 1, townIds + cnt + 1, [&](const int& a, const int& b) {
            if (bestEdgeLabel[a] != bestEdgeLabel[b])
                return bestEdgeLabel[a] < bestEdgeLabel[b];
            return rankTown[nextTown[a]] < rankTown[nextTown[b]];
        });
        for (int i = 1; i <= cnt; i++) {
            rankTown[townIds[i]] = i;
        }
        // 更新当前长度的城镇列表
        swap(currentLengthTowns, nextLengthTowns);
        nextLengthTowns.clear();
    }
    // 输出结果
    for (int i = 1; i <= n; i++) {
        printf("%d %lld\n", depth[i] - 1, labelSum[i]);
    }
    return 0;
}    