#include <cstdio>

using namespace std;

const int N = 1000001;
bool winning[N];
bool sold[N];

int last[N];

int n, m, b, a;
int maxWinning;

long long result[N];
int nResult;

int main()
{
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b);
        winning[b] = true;
        maxWinning = b;
    }
    long long clients = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        if (last[a] == 0) {
            last[a] = a; // ostatnia wielokrotnoœæ liczby zu¿yta
        }
        int dailyclients = 0;
        while (last[a] <= maxWinning && dailyclients < a)
        {
            if (!sold[last[a]]) {
                sold[last[a]] = true;
                ++dailyclients;
                if (winning[last[a]]) {
                    result[++nResult] = clients + dailyclients;
                }
            }
            last[a] += a;
        }

        clients += a;
    }
    printf("%d\n", nResult);
    for (int i = 1; i <= nResult; i++)
    {
        printf ("%lld\n", result[i]);
    }

}
