#include <cstdio>
#include <cstdlib>
#include <set>

#define FOR(x, b ,e) for(int x = b; x <= (e); ++x)
using namespace std;
typedef long long ll;

set<ll> S;
ll Players[40004];
int main() {
	ll n, m;
	scanf("%lld %lld", &n, &m);
	
	FOR(i, 1, m) {
		int playerNr, add;
		FOR(j, 1, n) {
			scanf("%d", &playerNr);
			Players[playerNr] = Players[playerNr] << 1;
			if (j > n/2)
				Players[playerNr] += 1;
		}
	}
	FOR(i, 1, n)
		S.insert(Players[i]);

	(S.size() == n) ? printf("TAK") : printf("NIE");
}
