#include <cstdio>
#include <cstdlib>

using namespace std;

typedef long long ll;

ll A[1001];
ll C[1001][1001][2];

ll mod = 1000000000;

ll f(int l, int r, int k)
{
	// printf("f %d %d %d\n", l, r, k);
	if (l == r)
	{
		return 1;
	}	
	else
	{
		ll result = 0;

		if (k  == 0)
		{
			if (A[l] < A[l+1])
			{
				if (C[l+1][r][0] == -1)
					C[l+1][r][0] = f(l+1,r,0);

				result += C[l+1][r][0];
			}

			if (A[l] < A[r])
			{
				if (C[l+1][r][1] == -1)
					C[l+1][r][1] = f(l+1,r,1);

				result = (result + C[l+1][r][1]) % mod;
			}
		}

		else if (k == 1)
		{
			if (A[l] < A[r])
			{
				if (C[l][r-1][0] == -1)
					C[l][r-1][0] = f(l, r-1, 0);
				
				result += C[l][r-1][0];
					
			}
			
			if (A[r-1] < A[r])
			{
				if (C[l][r-1][1] == -1)
					C[l][r-1][1] = f(l, r-1, 1);

				result = (result + C[l][r-1][1]) % mod;
			}
		}

		if (r - l == 1)
			return (result / 2) % mod;
		else
			return result % mod;
	}
}

int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &A[i]);
	}

	for (int x = 0; x <= 1000; x++)
	{
		for (int y = 0; y <= 1000; y++)
		{
			for (int z = 0; z <= 1; z++)
			{
				C[x][y][z] = -1;
			}
		}
	}

	if (n == 1)
		printf("1");
	//else if (n == 2)
	//	printf("%lld", ((f(1, n, 1) + f(1, n, 0)) /2) % mod);
	else
		printf("%lld", (f(1, n, 1) + f(1, n, 0)) % mod);
}
