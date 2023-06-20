#include <stdlib.h>
#include <omp.h>
#include "sort_funcs.h"

void bubble_sort(intType *list, int N)
{
    int i, j;
    for (i = 0; i < N - 1; i++)
        for (j = 1 + i; j < N; j++)
        {
            if (list[i] > list[j])
            {
                // Swap
                intType tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
}

void merge_sort(intType *list_to_sort, int N, int n_thr)
{
    if (N == 1)
    {
        // Only one element, no sorting needed. Just return directly in this case.
        return;
    }

    omp_set_nested(1);
    int n1_thr, n2_thr;
    if (n_thr == 1)
    {
        // omp_set_nested(0);
        n1_thr = 1;
        n2_thr = 1;
    }
    else
    {
        n1_thr = n_thr / 2;
        n2_thr = n_thr - n1_thr;
    }

    int n1 = N / 2;
    int n2 = N - n1;
    // Allocate new lists
    intType *list1 = (intType *)malloc(n1 * sizeof(intType));
    intType *list2 = (intType *)malloc(n2 * sizeof(intType));
    
    int i;
    for (i = 0; i < n1; i++)
        list1[i] = list_to_sort[i];
    for (i = 0; i < n2; i++)
        list2[i] = list_to_sort[n1 + i];
    
    // Sort list1 and list2
#pragma omp parallel num_threads((n_thr > 1) ? 2 : 1)
#pragma omp sections
    {
#pragma omp section
        {
            merge_sort(list1, n1, n1_thr);
        }
#pragma omp section
        {
            merge_sort(list2, n2, n2_thr);
        }
    }
    // Merge!
    int i1 = 0;
    int i2 = 0;
    i = 0;
    while (i1 < n1 && i2 < n2)
    {
        if (list1[i1] < list2[i2])
        {
            list_to_sort[i] = list1[i1];
            i1++;
        }
        else
        {
            list_to_sort[i] = list2[i2];
            i2++;
        }
        i++;
    }
    while (i1 < n1)
        list_to_sort[i++] = list1[i1++];
    while (i2 < n2)
        list_to_sort[i++] = list2[i2++];
    free(list1);
    free(list2);
}
