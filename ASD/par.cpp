#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

const bool debug = true;

using namespace std;

const int S = 500005;
int n, k;

int Left[S];
int Right[S];
int Parent[S];
int Depth[S];

int V[S];
int Links[20][S];

pair<int, int> Fardown[S];
pair<int, int> Farup[S];
pair<int, int> Far[S];

void setHeight(int i, int height)
{
    if (i != 0) {
        Depth[i] = height;
        setHeight(Left[i], height + 1);
        setHeight(Right[i], height + 1);
    }
}

void setLinks()
{
    for (int i = 0; i <= log2(n); i++) {
        for (int j = 0; j < S; j++) {
            Links[i][j] = -1;
        }
    }

    for (int i = 0; i <= log2(n); i++) {
        for (int v = 1; v <= n; v++)
            if (i == 0)
                Links[i][v] = Parent[v];
            else if (Links[i - 1][v] != -1)
                Links[i][v] = Links[i - 1][Links[i - 1][v]];
            else
                Links[i][v] = -1;
    }
}

int ancestor(int v, int h)
{
    int result = v;
    int i = log2(h);
    while (h > 0) {
        if (pow(2, i) > h)
            i = i - 1;
        else {
            result = Links[i][result];
            h = h - pow(2, i);
        }
    }
    return result;
}

int lca(int u, int v)
{
    int du = Depth[u];
    int dv = Depth[v];

    if (du < dv) {
        v = ancestor(v, dv - du);
        dv = Depth[v];
    } else if (du > dv) {
        u = ancestor(u, du- dv);
        du = Depth[u];
    }

    if (u == v)
        return u;

    int i = log2(n);

    while (i >= 0) {
        if (Links[i][u] != Links[i][v]) {
            u = Links[i][u];
            v = Links[i][u];
        }
        i--;
    }

    return Parent[u];
}

void PostOrder(int v) {
    pair<int, int> wynik = make_pair(0, v);
    if (Left[v] > 0) {
        PostOrder(Left[v]);
        wynik = make_pair(Fardown[Left[v]].first + 1, Fardown[Left[v]].second);
    }
    if (Right[v] > 0) {
        PostOrder(Right[v]);
        wynik = max(wynik,
                    make_pair(Fardown[Right[v]].first + 1, Fardown[Right[v]].second));
    }

    Fardown[v] = wynik;
}

void PreOrder(int v) {
    pair<int, int> wynik = make_pair(0, v);

    if (Parent[v] > 0) {
        wynik = max(wynik,
                    make_pair(Farup[Parent[v]].first + 1, Farup[Parent[v]].second));

        if ((Left[Parent[v]] == v) && (Right[Parent[v]] > 0))
            wynik = max(wynik,
                    make_pair(Fardown[Right[Parent[v]]].first + 2, Fardown[Right[Parent[v]]].second));

        if ((Right[Parent[v]] == v) && (Left[Parent[v]] > 0))
            wynik = max(wynik,
                    make_pair(Fardown[Left[Parent[v]]].first + 2, Fardown[Left[Parent[v]]].second));
    }

    Farup[v] = wynik;

    if (Left[v] > 0)
        PreOrder(Left[v]);

    if (Right[v] > 0)
        PreOrder(Right[v]);
}

void setFar()
{
    PostOrder(1);
    PreOrder(1);

    for (int i = 1; i <= n; i++)
        Far[i] = max(Fardown[i], Farup[i]);
}

int main()
{
    int input;
    scanf("%d", &n);

    for (int i = 0; i <= n; i++) {
        Left[i] = Right[i] = Parent[i] = Depth[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 2; j++) {
            scanf("%d", &input);

            if (input != -1) {
                Parent[input] = i;
                ((j == 1) ? Left[i] : Right[i]) = input;
            }
        }
    }

    setHeight(1, 0);
    setLinks();
    setFar();
    /*
    if (debug) {
        printf("***\n");
        for (int i = 1; i <= n; i++) {
            printf("i: %d %d %d", &i )
        }

    } */

    scanf("%d", &k);

    for (int i = 1; i <= k; i++) {
        int u, d;
        scanf("%d %d", &u, &d);

        int d_max = Far[u].first;
        int v = Far[u].second;

        if (d > d_max) {
            printf("-1\n");
            continue;
        }

        int l = lca(u, v);
        int d1 = Depth[u] - Depth[l];
        int d2 = Depth[v] - Depth[l];

        if (d <= d1)
            printf("%d\n", ancestor(u, d));
        else
            printf("%d\n", ancestor(v, d_max - d));

    }

    return 0;
}
