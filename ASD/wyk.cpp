#include <cstdio>
#include <algorithm>

const int M = 5007;

using namespace std;

int N, K;
int max1 = -1;
int max2 = -1;
int index1, index2;
int maximum = 0;

int T[M][3];
int DP[2][3][M];


void select_free_indexes(int ind)
{
	if (ind == 0) {
		index1 = 1;
		index2 = 2;
	}
	else if (ind == 1) {
		index1 = 0;
		index2 = 2;
	} else {
		index1 = 0;
		index2 = 1;
	}
}

int main()
{
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &T[i][j]);
		}
	}

	for (int start = 0; start < 3; start++) {
		for (int i = 0; i < 3; i++) {
			for(int k = 0; k <= K; k++) {
				DP[0][i][k] = 0; 
			}
		}
		
		select_free_indexes(start);
		DP[0][start][1] = max(T[0][index1], T[0][index2]);
		DP[0][start][2] = T[0][index1] + T[0][index2];

		if (start == 1) {
			DP[0][0][1] = T[0][2];
			DP[0][2][1] = T[0][0];
		} else
			DP[0][1][1] = (start == 0) ? T[0][2] : T[0][0]; 

		int i;
		for (i = 1; i < N; i++) {
			for (int k = 0; k <= K; k++) {

					/*

					DP[i % 2][j][k] = max ({

						
						DP[(i - 1) % 2][j][k],
						((k >= 1) ? (DP[(i - 1) % 2][j][k-1] + max(T[i][index1], T[i][index2])) : 0),
						((k >= 2) ? (DP[(i - 1) % 2][j][k-2] + T[i][index1] + T[i][index2]) : 0),

						
						((j + 1 < 3) ? DP[(i - 1) % 2][j+1][k] : 0),
						(((j == 1) && (k >= 1) ) ? DP[(i - 1) % 2][j+1][k-1] + T[i][0] : 0),
						(((j == 0) && (k >= 1) ) ? DP[(i - 1) % 2][j+1][k-1] + T[i][2] : 0),

						
						((j == 0) ? DP[(i - 1) % 2][j+2][k] : 0),

						
						((j - 1 >= 0) ? DP[(i - 1) % 2][j-1][k] : 0),
						(((j == 2) && (k >= 1)) ? DP[(i - 1) % 2][j-1][k-1] + T[i][0] : 0),
						(((j == 1) && (k >= 1)) ? DP[(i - 1) % 2][j-1][k-1] + T[i][2] : 0),
						
						((j == 2) ? DP[(i - 1) % 2][j-2][k] : 0)
					});

					*/

					DP[i % 2][0][k] = max({

						DP[(i - 1) % 2][0][k],
						((k >= 1) ? (DP[(i - 1) % 2][0][k-1] + max(T[i][1], T[i][2])) : 0),
						((k >= 2) ? (DP[(i - 1) % 2][0][k-2] + T[i][1] + T[i][2]) : 0),

						DP[(i - 1) % 2][1][k],
						((k >= 1) ? (DP[(i - 1) % 2][1][k-1] + T[i][2]) : 0),

						DP[(i - 1) % 2][2][k]

					});

					DP[i % 2][1][k] = max ({
						DP[(i - 1) % 2][1][k],
						((k >= 1) ? (DP[(i - 1) % 2][1][k-1] + max(T[i][0], T[i][2])) : 0),
						((k >= 2) ? (DP[(i - 1) % 2][1][k-2] + T[i][0] + T[i][2]) : 0),

						DP[(i - 1) % 2][0][k],
						((k >= 1) ? (DP[(i - 1) % 2][0][k-1] + T[i][2]) : 0),

						DP[(i - 1) % 2][2][k],
						((k >= 1) ? (DP[(i - 1) % 2][2][k-1] + T[i][0]) : 0),
					});

					DP[i % 2][2][k] = max({

						DP[(i - 1) % 2][2][k],
						((k >= 1) ? (DP[(i - 1) % 2][2][k-1] + max(T[i][0], T[i][1])) : 0),
						((k >= 2) ? (DP[(i - 1) % 2][2][k-2] + T[i][0] + T[i][1]) : 0),

						DP[(i - 1) % 2][1][k],
						((k >= 1) ? (DP[(i - 1) % 2][1][k-1] + T[i][0]) : 0),

						DP[(i - 1) % 2][0][k]

					});

			}
		}

		if (N == 1 && K > 2)
			K = 2;

		maximum = max((DP[(i + 1) % 2][start][K]), maximum);

	}

	printf("%d", maximum);
}
