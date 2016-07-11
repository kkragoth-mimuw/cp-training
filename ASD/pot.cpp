#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long long V[512][512];
long long D[512][512];
long long VIS[512][512];

priority_queue<pair<long long, pair<int, int> > > Q;

int x, y, h;

int main()
{
    scanf("%d %d %d", &x, &y, &h);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            scanf("%lld", &V[i][j]);
            D[i][j] = 1000000000;
            VIS[i][j] = false;
        }
    }

    Q.push(make_pair(0, make_pair(0,0)));

    long long result = 100000000;

    while (!Q.empty()) {
        int i = (Q.top().second.first);
        int j = (Q.top().second.second);
        int cost = -(Q.top().first);
        Q.pop();

        if (VIS[i][j])
            continue;

        VIS[i][j] = true;


        for (int k = -2; k <= 2; k++) {
            for (int l = -2; l <= 2; l++) {

                if (((i + k) >= 0 ) &&
                    ((i + k) < x) &&
                    ((j + l) >= 0) &&
                    ((j + l) < y)
                )
                {

                    long long new_cost = 100000000;

                    if (abs(V[i+k][j+l] - V[i][j]) < h) {
                        new_cost = 1;
                    } else {
                         new_cost = 1 + (abs(V[i+k][j+l] - V[i][j])) - h;
                    }

                    if (((i+k+1) == x) && ((j+l+1) == y))
                    {
                        result = min(result, cost + new_cost);
                    }

                    Q.push(make_pair(-(cost + new_cost), make_pair((i+k), (j+l))));
                }

            }
        }
    }

    printf("%lld", result);


}
