#include <stdio.h>

#define MDA multidimensional_array
#define COL 3 //quantity of columns

const int multidimensional_array [][COL] = {{1, 2, 3}, {4, 5, 6}};

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
    printf("Задан двумерный массив, состоящий из 2-х строк и 3-х столбцоа.\n"
           "Введите координату X и Y требуемого элемента массива\n");

    int x,y;
    scanf("%d%d", x, y);

}
