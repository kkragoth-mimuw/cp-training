#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<long long> V;
int main()
{
    int n;
    long long r;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &r);
        V.push_back(r);
    }

    sort(V.begin(), V.end());


    long long max_length = 1;
    long long cur_length = 1;

    for (int i = 1; i < n; i++) {

        if ((V[i] - V[i-1]) <= 1) {
             cur_length++;
             max_length = max(max_length, cur_length);
        }
        else {
            cur_length = 1;
        }

    }

    printf("%lld", max_length);
    return 0;
}
