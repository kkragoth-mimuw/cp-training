#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
 
int n;
vector<pair<int, int> > G[1007];
pair<int, int> E[1007];
 
 
/// Procedura dfs
//@param a Wierzchołek z którego zaczynamy
//@param p Poprzednik wierzchołka
//
//Procedura zwraca, do ilu wierzchołków da się dojść z a (łącznie z nim) drogą inną niż przez wierzchołek p
int dfs(int a, int p){
        int ret = 1;
        for(int i = 0; i < G[a].size(); i++){
                int b = G[a][i].first;
                if (b!=p) ret += dfs(b, a);
        }
        return ret;
}
 
int obc(int a, int b){
        int x = dfs(a, b);
        return x * (n-x);
}
 
int main(){
        scanf("%d", &n);
        for(int i = 0; i < n-1; i++){
                int a, b;
                scanf("%d %d", &a, &b);
                a--;
                b--;
                G[a].push_back(make_pair(b, i));
                G[b].push_back(make_pair(a, i));
                E[i] = make_pair(a, b);
        }
 
        int mxo = 0; //maksymalne znalezione obciążenie               
        for(int i = 0; i < n-1; i++){
                mxo = max(mxo, obc(E[i].first, E[i].second));
        }
 
        printf("%d", mxo);
}
 