#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;


vector<int> V[100001];
vector<int> VR[100001];
int DEG[100001];

long long COST[100001];
priority_queue<pair<int, long long> > Q;
int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 1; i <= n; i++)
        scanf("%lld", &COST[i]);

    int r1, r2;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &r1, &r2);
        V[r1].push_back(r2);
        VR[r2].push_back(r1);
    }

    for(int i = 1; i <= n; i++) {
        DEG[i] = V[i].size();

        if (DEG[i] == 0) {
            Q.push(make_pair(-COST[i], i));

        }
    }

    int c = 0;
    long long result = 0;

    while (!Q.empty() && (c <k)) {
        c++;
        int u = (Q.top().second);
        long long pu = -(Q.top().first);

        Q.pop();
        result = max(result, COST[u]);

        for (vector<int>::iterator it = VR[u].begin(); it != VR[u].end(); it++) {
            if (--DEG[*it] == 0) {
                Q.push(make_pair(-(COST[*it]), *it));
            }
        }
    }

    printf("%lld", result);

    return 0;
}
