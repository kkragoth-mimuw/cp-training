/*****************************************/
/*                                       */
/*   Olimpiada Informatyczna XX          */
/*   Etap: I                             */
/*   Zadanie: Taksówki (TAK)             */
/*   Autor: Piotr "renostr15h" Szulc     */
/*                                       */
/*****************************************/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
const int MAXN = 500000;
long long int m ,d ,distancefromBaseToEnd, rv;
long long A[MAXN];
int left, right, middle, n;
int numberoftaxi = 0;
int last_used = -1;
void read() {
    scanf ("%lld %lld %d", & m, &d, &n);
    for (int i=0; i<n; i++){
        scanf("%lld", &rv);
        A[i] = (-1) * rv;
    }
    std::sort (A, A+n);
    for (int i=0; i<n; i++){
        A[i] *= (-1);
    }
    distancefromBaseToEnd = m - d;
}
void bin_search() {
    left = 0;
    right = n-1;
    while (left < right){
        middle = (left+right)/2;
        if (A[middle] == distancefromBaseToEnd) {break;}
        else if (A[middle]> distancefromBaseToEnd) {left = middle+1;}
        else {right = middle-1;}
    }
    if(A[middle]+1>= distancefromBaseToEnd) middle++;
    if(A[middle] < distancefromBaseToEnd) middle--;
    last_used = middle;
}
int sum() {
    for (int i=0; i<last_used && d>0 && A[i] > d; i++) {
        numberoftaxi++;
        d-=(A[i] - d);
    }
    if (d>0)
    for (int i = last_used+1; d>0 && i<n && A[i] >d; i++) {
        numberoftaxi++;
        d-=(A[i] - d);
    }
    if(d*(-1) >= distancefromBaseToEnd) {
        return numberoftaxi;
    }
    else if(A[last_used] >= (2* d + distancefromBaseToEnd)){
        ++numberoftaxi;
        return numberoftaxi;
    }
    else return 0;
}
int main()
{
    read();
    if ((A[0] <distancefromBaseToEnd) || A[0] <d){
        printf("0");
        return 0;
    }
    bin_search();
    printf("%d", sum());
    return 0;
}
