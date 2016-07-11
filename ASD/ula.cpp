#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

vector<int> V[200007];
vector<int> VT[200007];
vector<int> SSS[200007];
vector<int> SSS_T[200007];
set<int> set_SSS[200007];
bool visited[200007];
int PTS[200007];
int SSS_PTS[200007];
int SSS_NUMBER[200007];
int SSS_ARROW[200007];
stack<int> noArrows;

stack<int> S;

void DFS(int v) {
	visited[v] = true;
	for (auto& w : V[v]) {
		if (!visited[w])
			DFS(w);
	}
	S.push(v);
}	

void DFS_SSS(int v,int sss_number) {
	visited[v] = true;
	SSS_NUMBER[v] = sss_number;
	SSS_PTS[sss_number] += PTS[v];
	SSS[sss_number].push_back(v);
	SSS_T[v].push_back(sss_number);
	for (auto& w : VT[v]) {
		if (!visited[w])
			DFS_SSS(w, sss_number);
	}
}

int main() {
	int n, m;
	int maximum = 0;

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &PTS[i]);	
		visited[i] = false;
		SSS_PTS[i - 1] = SSS_ARROW[i - 1] =0;
	}

	for (int i = 1; i <= m; i++) {
		int inp1, inp2;
		scanf("%d %d", &inp1, &inp2);
		V[inp1].push_back(inp2);
		VT[inp2].push_back(inp1);
	}

	for (int v = 1; v <= n; v++) {
		if (!visited[v])
			DFS(v);
	}

	for (int i = 0; i <= n; i++)
		visited[i] = false;

	int sss_count = 0;
	while (!S.empty()) {
		int v = S.top();
		S.pop();
		if (!visited[v]) {
			DFS_SSS(v, sss_count);
			sss_count++;
		}
	}

	for (int skladowa = 0; skladowa < sss_count; skladowa++) {
		for (auto& v : SSS[skladowa]) {
			for (auto& w : V[v]) {
				if (SSS_NUMBER[w] != skladowa) {
					set_SSS[skladowa].insert(SSS_NUMBER[w]);
					SSS_ARROW[skladowa]++;
				}
			}
		}
	}

	for (int skladowa = 0; skladowa < sss_count; skladowa++) {
		if (SSS_ARROW[skladowa] == 0)
			noArrows.push(skladowa);
	}


	for (int skladowa = 0; skladowa < sss_count; skladowa++) {
		maximum = max(maximum, SSS_PTS[skladowa]);
	}

	int max_sss;
	while (!noArrows.empty()) {
		int v = noArrows.top();
		noArrows.pop();

		for (auto& x : SSS_T[v]) {
			SSS_ARROW[x]--;
			if (SSS_ARROW[x] == 0) {
				noArrows.push(x);
				max_sss = 0;
				for (auto& y : set_SSS[x]) {
					max_sss = max(max_sss, SSS_PTS[y]);
				}
				SSS_PTS[x] += max_sss;
				maximum = max(maximum, SSS_PTS[x]);
			}
		}
	}
	printf("%d", maximum);
}
