#include <cstdio>
#include <algorithm>

int DP[200][200];
int T[200];

int recursive(int a, int b) {
    if (a == b) return 1;
    if (a > b) return 0;
    if (DP[a][b] == 0) {
        int best_reuse = 99999;
        for (int i = a + 1; i <= b; i++) {
            if (T[a] == T[i]) {
                best_reuse = std::min(best_reuse, recursive(a+1, i-1) + recursive(i, b));
            }
        }
        DP[a][b] = std::min(recursive(a+1, b) + 1, best_reuse);
    }
    return DP[a][b];
}

int main() {
    int t, n, k;
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 200; j++) {
                DP[i][j] = 0;
            }
        }
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++) {
            scanf("%d", &T[i]);
            DP[i][i] = 1;
        }
        printf("%d\n", recursive(0, n-1));
    }
}
