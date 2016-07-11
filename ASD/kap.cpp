#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool vis[200001];
pair<int, int> C[200001];
vector<int> V[200001];
int D[200001];

priority_queue<pair<int, int> > Q;
priority_queue<pair<pair<int,int>, int> > X;
priority_queue<pair<pair<int,int>, int> > Y;

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        C[i] = make_pair(x, y);

        X.push(make_pair(make_pair(x, y), i));
        Y.push(make_pair(make_pair(y, x), i));

        D[i] = 1000000000;
    }

    while (!X.empty())
    {
        pair<pair<int, int>, int> prevX = X.top();
        X.pop();

        pair<pair<int, int>, int> prevY = Y.top();
        Y.pop();

        if (!X.empty())
        {
            V[prevX.second].push_back(X.top().second);
            V[X.top().second].push_back(prevX.second);

            V[prevY.second].push_back(Y.top().second);
            V[Y.top().second].push_back(prevY.second);
        }

    }

    Q.push(make_pair(0, 1));

    while (!Q.empty())
    {
        int result = -Q.top().first;
        int v = Q.top().second;
        Q.pop();

        if (vis[v])
            continue;

        vis[v] = true;

        for (auto it = V[v].begin(); it != V[v].end(); it++)
        {
            int cost = result + min(abs(C[v].first - C[*it].first), abs(C[v].second - C[*it].second));
            if (cost < D[*it])
            {
                D[*it] = cost;
                Q.push(make_pair(-cost, *it));
            }
        }
    }

    printf("%d", D[n]);


}