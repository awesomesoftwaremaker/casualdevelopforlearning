#include <stdio.h>

#define MDA multidimensional_array
#define COL 3 //quantity of columns

const int multidimensional_array [][COL] = {{54, 32, 77}, {21, 10, 64}};
int x,y;

int indexing ()
{
    return MDA [x][y];
}

int increment ()
{
    return *(*(MDA + x) + y);
}

int pointer ()
{
    int value = (x * COL) + y;
    return *(*MDA + value);
}

int main ()
{
    printf("enter x and y\n");
    scanf("%d%d", x, y);
    printf("%d%d%d", indexing, increment, pointer);
    getchar();

}
