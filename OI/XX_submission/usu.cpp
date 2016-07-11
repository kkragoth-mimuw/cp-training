/*****************************************/
/*                                       */
/*   Olimpiada Informatyczna XX          */
/*   Etap: I                             */
/*   Zadanie: Usuwanka (USU)             */
/*   Autor: Piotr "renostr15h" Szulc     */
/*                                       */
/*****************************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
const int MAXN = 1000000;
using namespace std;
int n, k;
int it = 0;
int number = 0;
int c[MAXN];
vector<int> V[MAXN];
char word;

void group(int iloscc, int iloscb, int id) {
    id = number;
    number++;
    while (iloscc < 1 || iloscb < k) {
        if(iloscc < 1 && c[it] == 1){
            iloscc++;
            V[id].push_back(it);
            it++;
        }
        else if(iloscc == 1 && c[it]==1){
            group(0, 0, 0);
        }
        else if(iloscb < k && c[it]==0){
            iloscb++;
            V[id].push_back(it);
            it++;
        }
        else if(iloscb < k && c[it] ==0){
            group(0, 0, 0);
        }
    }
}
int main()  {
    scanf("%d %d\n", &n, &k);
    for (int i =0; i < n; i++) {
        scanf("%c", &word);
        if (word =='c') {
            c[i] = 1;
        }
        else {
            c[i] = 0;
        }
    }
    while (it < n){
        group(0,0,0);
    }

    for(int i = 0; i < n/(k+1); i++ )
    {
        for (int j = 0; j < V[i].size(); j++)
        {
            printf("%d ", V[i][j]+1);
        }
        printf("\n");
    }
        return 0;
}
