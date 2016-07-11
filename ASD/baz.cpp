#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define FOR(x, b ,e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < n; x++)
void readA(LL *A, int n) {REP(i,n) {scanf("%lld", &A[i]);}}

template <typename T>
void sumSuf(T *A, T *B, int n) {
	if (n > 0) {
		B[n-1] = A[n-1];
		FORD(i, n-2, 0) {
			B[i] = A[i] + B[i+1];
		}
	}
}

const int MAX = 1000002;
LL prices[MAX], sumSfx[MAX], nextEven[MAX], prevEven[MAX], nextUnven[MAX], prevUnven[MAX];

int main()
{
	int n;
	scanf("%d", &n);
	readA(prices, n);
	sumSuf(prices, sumSfx, n);
	
	prevEven[0] = ((prices[0] % 2) == 0) ? prices[0] : (-1);
	prevUnven[0] = (prevEven[0] == (-1)) ? prices[0] : (-1);

	FOR(i, 1, n-1)
	{
		if (prices[i] % 2 == 0) {
			prevEven[i] = prices[i];
			prevUnven[i] = prevUnven[i-1];
		} else {
			prevUnven[i] = prices[i];
			prevEven[i] = prevEven[i-1];
		}
	}

	nextEven[n-1] = ((prices[n-1] % 2) == 0) ? prices[n-1] : (-1);
	nextUnven[n-1] = (nextEven[n-1] == - 1) ? prices[n-1] : (-1);

	FORD(i, n-2, 0)
	{
		if (prices[i] % 2 == 0) {
			nextEven[i] = prices[i];
			nextUnven[i] = nextUnven[i+1];
		} else {
			nextUnven[i] = prices[i];
			nextEven[i] = nextEven[i+1];
		}
	}

	int l;
	scanf("%d", &l);
	REP(i, l)
	{
		int k;
		scanf("%d", &k);
		if (sumSfx[n - k] % 2 == 0) {
			LL score = -1;
			if (n - k - 1 < 0) {
				printf("%lld\n", score);
				continue;
			}
			if ((nextUnven[n - k] != -1) && (prevEven[n - k - 1] != -1)) {
				score = sumSfx[n - k] - nextUnven[n - k] + prevEven[n - k - 1];
			}
			if ((nextEven[n -k] != -1) && (prevUnven[n - k - 1] != -1)) {
				score = max(score, sumSfx[n - k] - nextEven[n - k] + prevUnven[n - k - 1]);
			}
			printf("%lld\n", score);			
		} else {
			printf("%lld\n", sumSfx[n - k]);
		}	
	}
	return 0;
}		
