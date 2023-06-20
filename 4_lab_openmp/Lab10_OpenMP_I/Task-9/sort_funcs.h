typedef int intType;

void bubble_sort(intType *list, int N);
void merge_sort(intType *list_to_sort, int N, int start_idx, int n_thr); // 1 mallocs
// void merge_sort(intType *list_to_sort, int N, int n_thr); // 2 mallocs