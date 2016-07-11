
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int size = 1001;
vector<pair<int, int> > V[size];
int D[size];
pair<int, int> read_pair;
bool przetw[size];


int main()
{
	int n, k, m;
	int r_v0, r_v1, r_v2, r_v3;
	int maximum = 0;
	
	
	scanf("%d%d%d", &n, &k, &m);
	for (int i = 1; i <= size; i++)
	{
		D[i] = 3000001;
		przetw[i] = false;
	}

	for (int i = 1; i <= k; i++)
	{
		scanf("%d", &r_v0);
		D[r_v0] = 0;
	}
	

	
	
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &r_v1, &r_v2, &r_v3);
		read_pair.first = r_v2;
		read_pair.second = r_v3;
		V[r_v1].push_back(read_pair);
		read_pair.first = r_v1;
		V[r_v2].push_back(read_pair);
	}
	
	
	int counter = 1;
	int v;
	while (counter <= size)
	{	
		int minimum = 3000001;
		for (int i = 1; i <= n; i++)
		{
			if (!przetw[i])
			{
				if( minimum > D[i])
				{
					minimum = D[i];
					v = i;
				}
			}		
		}
		for (vector<pair <int, int> >::const_iterator it = V[v].begin(); it !=V[v].end(); ++it)
		{
			if(D[it->first] > D[v] + it->second)
			{
				D[it->first] = D[v] + it->second;
				
			}	
		}
		przetw[v] = true;
		++counter;
		
	}
		
	for (int i = 1; i <= n; i++)
	{
		if (maximum < D[i]) {
			maximum = D[i];
		}
	}
		
	printf("%d\n", maximum);
}