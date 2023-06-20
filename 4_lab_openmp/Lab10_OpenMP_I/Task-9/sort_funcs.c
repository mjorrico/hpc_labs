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

void merge_sort(intType *list_to_sort, int N, int start_idx, int n_thr)
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
        omp_set_nested(0);
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
    // Sort list1 and list2
#pragma omp parallel num_threads(n_thr)
#pragma omp sections
    {
#pragma omp section
        {
            merge_sort(list_to_sort, n1, start_idx, n1_thr);
        }
#pragma omp section
        {
            merge_sort(list_to_sort, n2, start_idx + n1, n2_thr);
        }
    }
    // Merge!
    int i1 = 0, i2 = 0, i = 0;
    intType *temp_array = malloc(N * sizeof(intType));
    while (i1 < n1 && i2 < n2)
    {
        if (list_to_sort[i1 + start_idx] < list_to_sort[i2 + start_idx + n1])
        {
            temp_array[i] = list_to_sort[i1 + start_idx];
            i1++;
        }
        else
        {
            temp_array[i] = list_to_sort[i2 + start_idx + n1];
            i2++;
        }
        i++;
    }
    while (i1 < n1)
        temp_array[i++] = list_to_sort[start_idx + i1++];
    while (i2 < n2)
        temp_array[i++] = list_to_sort[start_idx + n1 + i2++];

    for (i = 0; i < N; i++)
    {
        list_to_sort[i + start_idx] = temp_array[i];
    }

    free(temp_array);
}
