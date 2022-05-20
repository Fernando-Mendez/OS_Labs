#include "ex4.h"

int main(void)
{

    int nlines; /*number of input lines read */

    char *word;
    char **word_list;

    scanf("%d\n", &nlines);
    // TODO: INIT word AND word_list

    char cmd[100];
    word_list = (char **)malloc(nlines * sizeof(char *));

    // READ WORDS AND POINT EACH ELEMENT OF WORD_LIST TO A WORD
    for (int i = 0; i < nlines; i++)
    {
        fgets(cmd, 100, stdin);
        word = (char *)malloc(strlen(cmd) - 1 * sizeof(char));
        word = strcpy(word, cmd);
        word_list[i] = word;
    }

    qsort_((void **)word_list, 0, nlines - 1, (int (*)(void *, void *))(strcmp));

    // PRINT SORTED ELEMENTS:
    for (int i = 0; i < nlines; i++)
    {
        printf("%s", word_list[i]);
    }
}

void qsort_(void **v, int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);

    qsort_(v, left, last - 1, comp);
    qsort_(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}