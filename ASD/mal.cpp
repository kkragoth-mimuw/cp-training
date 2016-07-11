#include <cstdio>

using namespace std;

typedef long long ll;

const ll MAX = 6000005;
const int mixed = 2;

ll sum[MAX];
int state[MAX];

void updateSum(ll i, ll nl, ll nr)
{
    switch(state[i]) {
        case 0: sum[i] = 0; break;
        case 1: sum[i] = nr - nl + 1; break;
        default: sum[i] = sum[2*i] + sum[2*i + 1];
    }
}

void update(ll l, ll r, int v, ll i, ll nl, ll nr)
{
    if ((r < nl) || (nr < l))
    {
        return; // brak czesci wspolnej
    }
    else if ((l <= nl) && (nr <= r)) // pokrywaja sie zupelnie
    {
        state[i] = v;
        updateSum(i, nl, nr);
    }
    else // maja czesc wspolna ale tez roznice
    {
        ll nm = (nl + nr) / 2;
        if (state[i] != mixed)
        {
            state[2*i] = state[i]; updateSum(2*i, nl, nm);
            state[2*i + 1] = state[i]; updateSum(2*i + 1, nm + 1, nr);
            state[i] = mixed;
        }
        update(l, r, v, 2*i, nl, nm);
        update(l, r, v, 2*i + 1, nm + 1, nr);
        updateSum(i, nl, nr);
    }
}

int main()
{
    ll n, days, l, r;
    scanf("%lld", &n);
    scanf("%lld", &days);

    char c; int v;
    for (int i = 0; i < days; i++)
    {
        scanf("%lld %lld %c", &l, &r, &c);
        if (c == 'B')
            v = 1;
        else
            v = 0;
        update(l, r, v, 1, 1, n);
        printf("%lld\n", sum[1]);
    }
}
