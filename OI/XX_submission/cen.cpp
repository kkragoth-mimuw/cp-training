/*****************************************/
/*                                       */
/*   Olimpiada Informatyczna XX          */
/*   Etap: I                             */
/*   Zadanie: Cennik (Cen)               */
/*   Autor: Piotr "renostr15h" Szulc     */
/*                                       */
/*****************************************/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
const int MAXN = 100000;
const int TMAXN = 200000;
const int INF = 100000001;
int n, m, k, a, b;
vector<int> V[MAXN+1];
vector<int> A;
vector<int> B;
int Queue[TMAXN];
int Head = 0;
int Tail = 0;
bool toskip = false;
int dis_parz[MAXN+1];
int dis_nieparz[MAXN+1];
int ojc_parz[MAXN+1];
int ojc_nieparz[MAXN+1];
int main() {
    scanf("%d%d%d%d%d", &n, &m, &k, &a, &b);
    while(m--) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        V[v1].push_back(v2);
        V[v2].push_back(v1);
    }
    for(int i = 1; i<=n; i++){
        dis_parz[i] = INF;
        dis_nieparz[i] = INF;
        ojc_parz[i] = (-1) *i;
        ojc_nieparz[i] = (-1) *i;
    }
    dis_nieparz[k] = 0;
    dis_parz[k] = 0;
    ojc_nieparz[k] = 1;
    ojc_parz[k] = 1;
    int v = k;
    for(unsigned int i = 0; i < V[v].size();i++) {
                 dis_nieparz[V[v][i]] = dis_parz[v] + 1;
                 ojc_nieparz[V[v][i]] = v;
                 Queue[Tail] = V[v][i];
                 Tail++;
    }
    dis_nieparz[v] = INF;
    dis_parz[v] = INF;

    while (Head != Tail) {
        int v = Queue[Head];
        for(unsigned int i = 0; i < V[v].size();i++) {
         toskip = false;
         if (ojc_nieparz[V[v][i]] != ojc_nieparz[v] && ojc_nieparz[v] != V[v][i]) {
            if ( (dis_nieparz[v] != INF)&& (dis_nieparz[v] +1 < dis_parz[V[v][i]]) ) {
                dis_parz[V[v][i]] = dis_nieparz[v] + 1;
                ojc_parz[V[v][i]] = v;
/*
                printf("Jestem w %d od w %d, disparz ustalam na %d, ojca parz na %d \n",
                       V[v][i], v, dis_parz[V[v][i]], ojc_parz[V[v][i]]);
*/
                Queue[Tail] = V[v][i];
                Tail++;
                if (Tail == TMAXN-1) { Tail = 0; }
            }
         }
         if ((ojc_parz[V[v][i]] != ojc_parz[v]) || ((ojc_parz[V[v][i]] == ojc_parz[v])
                && (V[v].size() != 2) || (V[V[v][i]].size() != 2))) {


            if (V[v].size() == V[V[v][i]].size()) {
                B.push_back(V[v][i]);
                A.push_back(v);

                for (unsigned int j = 0; j < V[v].size(); j++)
                {
                    A.push_back(V[v][j]);
                    B.push_back(V[V[v][i]][j]);
                }
                sort(A.begin(), A.end());
                sort(B.begin(), B.end());
                toskip = true;
                for (unsigned int j = 0; j < A.size(); j++)
                {
                    if (A[j] != B[j]) {
                    toskip = false;
                    A.clear();
                    B.clear();
                    break;
                    }
                }
                A.clear();
                B.clear();
            }




            if ( (dis_parz[v] != INF) && (dis_parz[v] +1 < dis_nieparz[V[v][i]]) && (!toskip) ) {
                dis_nieparz[V[v][i]] = dis_parz[v] + 1;
                ojc_nieparz[V[v][i]] = v;
/*
                printf("Jestem w %d od w %d, disnieparz ustalam na %d, ojcanieparz na %d \n",
                       V[v][i], v, dis_nieparz[V[v][i]], ojc_nieparz[V[v][i]]);
*/
                Queue[Tail] = V[v][i];
                Tail++;
                if (Tail == TMAXN-1) { Tail = 0; }
            }
         }
        }
        Head++;
        if (Head == TMAXN - 1) { Head = 0; }
    }
/*
    for(int i = 1; i <=n; i++)
    {
        cout <<dis_parz[i] <<" "<< dis_nieparz[i] <<endl;
    }
*/
    if (2*a > b) {
        for (int i = 1; i <= n; i++) {
            if (k == i) {printf("0\n"); continue;}
            printf("%d\n", min((dis_parz[i]/2) * b, (dis_nieparz[i]/2)* b + a));
        }
    }
    else {
        for (int i = 1; i<=n; i++) {
            if (k == i) {printf("0\n"); continue;}
            printf("%d\n", min(dis_parz[i] *a , dis_nieparz[i]* a));
        }
    }
    return 0;
}

