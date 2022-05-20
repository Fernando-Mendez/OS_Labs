#include "ex1.h"

void update(int *a, int *b){
    int tmpInt = *a,
        tmpInt2 = *b;
    (*a) = (*a) - (*b);

    if (abs(*a) % 2 == 0)
    {
        (*b) = (tmpInt2) * (tmpInt);
    }
    else
    {
        (*b) = abs((tmpInt2)) - abs((tmpInt));
    }
}