void tribonacci(int n)
{
    // initialize array (int* seq) to 1, using malloc/calloc
    int *seq = (int *)malloc(sizeof(int));

    for (int i = 0; i <= n; i++)
    {
        tribonacciHelper(i, seq);
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", *(seq + j));
        }
        int newSize = i + 1;
        seq = realloc(seq, newSize * sizeof(int));
        printf("\n");
    }
    free(seq);
}

// n=amount of numbers in the series to compute, seq=array to store series
void tribonacciHelper(int n, int *seq)
{
    if (n < 1)
        seq[0] = 0;
    else if (n < 2)
    {
        seq[0] = 0;
        seq[1] = 1;
    }
    else if (n < 3)
    {
        seq[0] = 0;
        seq[1] = 1;
        seq[2] = 1;
    }
    else
    {
        seq[0] = 0;
        seq[1] = 1;
        seq[2] = 1;
        int i;
        for (i = 3; i <= n; i++)
            seq[i] = seq[i - 3] + seq[i - 2] + seq[i - 1];
    }
}