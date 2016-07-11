#include <cstdio>
#include <cstdlib>
using namespace std;
const int size = 131072;
struct direction {
    int x;
    int y;
    char c;

    direction() : x(0), y(0), c('N')
    {}
};

struct wskazowka {
    int k;
    char c;
    int d;
    int pos;
};

wskazowka wsk[size];
int intervalTree[2 * size];
int find_place(int k)
{
    int pos = 1;
    int range = size;
    while (range > 1)
    {
        if (k <= (range / 2) - intervalTree[2*pos])
            pos *= 2;
        else {
            k -= (range / 2) - intervalTree[2*pos];
            pos = 2 * pos + 1;
        }
        range = range / 2;
    }

    int index = pos - size + 1;
    intervalTree[pos] = 1;

    while (pos > 1)
    {
         pos /= 2;
         intervalTree[pos]++;
    }

    //printf("%d\n", index);
    return index;
}

direction Tree[2 * size];
void addDirections(direction &result, direction left, direction right)
{
  char direct = right.c;

  switch (left.c)
  {
     case 'N':
         //printf("tak \n");
         result.x = left.x + right.x;
         result.y = left.y + right.y;
         result.c = right.c;

         break;
     case 'W':
         result.x = left.x - right.y;
         result.y = left.y + right.x;


         if (direct == 'N') {
             result.c = 'W';
         } else if (direct == 'E') {
              result.c = 'N';
         } else if (direct == 'S') {
             result.c = 'E';
         } else if (direct == 'W') {
             result.c = 'S';
         }
         break;
     case 'E':
         result.x = left.x + right.y;
         result.y = left.y - right.x;

         if (direct == 'N')
             result.c = 'E';
         if (direct == 'E')
             result.c = 'S';
         if (direct == 'W')
             result.c = 'N';
         if (direct == 'S')
             result.c = 'W';
         break;
     case 'S':
         result.x = left.x - right.x;
         result.y = left.y - right.y;

         if (direct == 'N')
             result.c = 'S';
         if (direct == 'S')
             result.c = 'N';
         if (direct == 'E')
             result.c = 'W';
         if (direct == 'W')
             result.c = 'E';
         break;
  }
}

void printf_direction(direction d)
{
  printf("kierunek: %d %d %c\n", d.x, d.y, d.c);
}

void update(int pos, char instruction_direction, int d)
{
    direction  result;


    pos += size - 1;
    direction dir;

    switch (instruction_direction)
    {
        case 'L': dir.x = -d; dir.c = 'W'; break;
        case 'U': dir.y = -d; dir.c = 'S'; break;
        case 'R': dir.x = d; dir.c ='E'; break;
    }

    //printf("Nowy wezel: %d %d %c\n", dir.x, dir.y, dir.c);
    Tree[pos] = dir;

    //printf("UWAGA\n");
    //printf_direction(result);
    addDirections(result, Tree[pos], result);
    //printf_direction(result);

    while (pos > 1) {
        if (pos % 2) {
          //printf("dodaje\n");
          //printf_direction(Tree[pos - 1]);
          //printf_direction(result);
          addDirections(result, Tree[pos - 1], result);
        }
        pos /= 2;
        addDirections(Tree[pos], Tree[2*pos], Tree[2*pos + 1]);

    }

    printf("%d %d\n", result.x, result.y);

}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d %c %d", &wsk[i].k, &wsk[i].c, &wsk[i].d);
    }

    for (int i = 0; i < size; i++)
    {
         intervalTree[i] = 0;
    }



    for (int i = n - 1; i >= 0; i--)
    {
        wsk[i].pos = find_place(wsk[i].k);
    }
    /*
    for (int i = 0; i < n; i++)
    {
         printf("%d: %d %c %d\n", i, ordered_wsk[i].k, ordered_wsk[i].c, ordered_wsk[i].d);
    }
    */

    for (int i = 0; i < n; i++)
    {
        update(wsk[i].pos, wsk[i].c, wsk[i].d);
    }
/*
    for (int i = 0; i < 2*n; i++)
    {
         printf("%d: %d %d\n", i, Tree[i].x, Tree[i].y);
    }
  */
}
