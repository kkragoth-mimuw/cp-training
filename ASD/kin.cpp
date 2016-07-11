#include <cstdio>
#include <cstdlib>

const long long base = 32768;
const long long size = 2*base + 2;
const long long maxK = 10;
const long long MOD = 1000000000;

long long tree[maxK][size];
long long A[base];
long long n, k, smallBase = 1;

void insertT(long long v, long long val, long long d);
long long queryT(long long v, long long w, long long d);

using namespace std;

int main()
{
	scanf("%lld%lld", &n, &k);
	while (smallBase < n) {
		smallBase *= 2;
	}
	
	for (long long i = 1; i <= n; i++) {
		scanf("%lld", &A[i]);
	}


	for (long long i = 0; i < k; i++) {
		for (long long j = 0; j < size; j++) {
			tree[i][j] = 0;
		}
	}
	
	for (long long i = 1; i <= n; i++)
	{
		insertT(A[i], 1, 0);

		for (long long j = 1; j < k; j++)
		{
			long long sum = queryT(A[i] + 1, smallBase, j - 1);
		      	insertT(A[i], sum, j);
		}
	}

	printf("%lld", (tree[k - 1][1]) % MOD);
}

void insertT(long long v, long long val, long long d)
{
	v += smallBase - 1;
	tree[d][v] += val;

	while (v != 0) {
		v = v / 2;
		tree[d][v] = tree[d][2*v] + tree[d][2*v + 1];

	}
}

long long queryT(long long v, long long w, long long d)
{
	long long va = v + smallBase - 1;
	long long vb = w + smallBase - 1;

	if (va > vb) return 0;

	long long result = tree[d][va];
	if (va != vb) result = (result + tree[d][vb]) % MOD;

	while (va / 2 != vb / 2) {
		if (va % 2 == 0) result = (result + tree[d][va + 1]) % MOD;
		if (vb % 2 == 1) result = (result + tree[d][vb - 1]) % MOD;

		va /= 2;
		vb /= 2;
	}

	return result % MOD;
}
