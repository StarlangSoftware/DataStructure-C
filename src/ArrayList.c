//
// Created by Olcay Taner YILDIZ on 18.01.2023.
//

#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

Array_list_ptr create_array_list() {
    Array_list_ptr array_list = malloc(sizeof(Array_list));
    array_list->maxSize = 10;
    array_list->array = malloc(array_list->maxSize * sizeof(void *));
    array_list->size = 0;
    return array_list;
}

Array_list_ptr create_array_list_of_string(char **array, int size) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < size; i++) {
        array_list_add(result, array[i]);
    }
    return result;
}

Array_list_ptr create_array_list_of_int(int *array, int size) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < size; i++) {
        array_list_add(result, &(array[i]));
    }
    return result;
}

void free_array_list(Array_list_ptr array_list, void free_method(void *)) {
    if (free_method != NULL) {
        for (int i = 0; i < array_list->size; i++) {
            free_method(array_list->array[i]);
        }
    }
    free(array_list->array);
    free(array_list);
}

void check_and_increase_size(Array_list_ptr array_list) {
    if (array_list->size == array_list->maxSize) {
        array_list->maxSize *= 2;
        array_list->array = realloc(array_list->array, array_list->maxSize * sizeof(void *));
    }
}

void array_list_add(Array_list_ptr array_list, void *item) {
    check_and_increase_size(array_list);
    array_list->array[array_list->size] = item;
    array_list->size++;
}

void array_list_add_double(Array_list_ptr array_list, double value) {
    double *item = malloc(sizeof(double));
    *item = value;
    array_list_add(array_list, item);
}

void array_list_insert(Array_list_ptr array_list, int index, void *item) {
    if (index < 0 || index > array_list->size) {
        return;
    }
    if (index == array_list->size) {
        array_list_add(array_list, item);
    } else {
        check_and_increase_size(array_list);
        for (int i = array_list->size; i > index; i--) {
            array_list->array[i] = array_list->array[i - 1];
        }
        array_list->array[index] = item;
        array_list->size++;
    }
}

void *array_list_get(const Array_list* array_list, int index) {
    if (index < 0 || index >= array_list->size) {
        return NULL;
    }
    return array_list->array[index];
}

double array_list_get_double(const Array_list* array_list, int index) {
    return *((double *) array_list_get(array_list, index));
}

void array_list_add_all(Array_list_ptr dst, const Array_list* src) {
    if (dst->size + src->size > dst->maxSize) {
        dst->maxSize = (dst->size + src->size) * 2;
        dst->array = realloc(dst->array, dst->maxSize * sizeof(void *));
    }
    for (int i = 0; i < src->size; i++){
        dst->array[dst->size + i] = src->array[i];
    }
    dst->size += src->size;
}

bool array_list_contains(const Array_list* list, const void *data, int (*comparator)(const void *, const void *)) {
    for (int i = 0; i < list->size; i++) {
        if (comparator(data, list->array[i]) == 0) {
            return true;
        }
    }
    return false;
}

int array_list_index_of(const Array_list* list, const void *data, int (*comparator)(const void *, const void *)) {
    for (int i = 0; i < list->size; i++) {
        if (comparator(data, list->array[i]) == 0) {
            return i;
        }
    }
    return -1;
}

bool is_array_list_empty(const Array_list* list) {
    return list->size == 0;
}

void array_list_dummy_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    for (int i = 0; i < list->size; i++){
        for (int j = i + 1; j < list->size; j++){
            if (comparator(list->array[i], list->array[j]) > 0){
                array_list_swap(list, i, j);
            }
        }
    }
}

void array_list_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    array_list_merge_sort(list, comparator);
}

Array_list_ptr sub_list(const Array_list* list, int first_index, int last_index) {
    Array_list_ptr result = create_array_list();
    for (int i = first_index; i < last_index; i++) {
        array_list_add(result, list->array[i]);
    }
    return result;
}

void array_list_shuffle(Array_list_ptr list, int seed) {
    void *tmp;
    srandom(seed);
    for (int i = 0; i < list->size; i++) {
        int index = random() % (list->size - i);
        tmp = list->array[i];
        list->array[i] = list->array[i + index];
        list->array[i + index] = tmp;
    }
}

void array_list_remove(Array_list_ptr list, int index, void (*free_method)(void *)) {
    if (free_method != NULL) {
        free_method(list->array[index]);
    }
    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
}

void array_list_replace(Array_list_ptr list, int index, void *item, void (*free_method)(void *)) {
    if (free_method != NULL) {
        free_method(list->array[index]);
    }
    list->array[index] = item;
}

bool array_list_equals(const Array_list* list1, const Array_list* list2, int (*comparator)(const void *, const void *)) {
    if (list1->size != list2->size) {
        return false;
    }
    for (int i = 0; i < list1->size; i++) {
        if (comparator(list1->array[i], list2->array[i]) != 0) {
            return false;
        }
    }
    return true;
}

void array_list_swap(Array_list_ptr list, int index1, int index2) {
    void* tmp = list->array[index1];
    list->array[index1] = list->array[index2];
    list->array[index2] = tmp;
}

void array_list_insertion_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    for (int j = 1; j < list->size; j++){
        void* t = list->array[j];
        int i = j - 1;
        while (i >= 0 && comparator(list->array[i], t) > 0){
            list->array[i + 1] = list->array[i];
            i--;
        }
        list->array[i + 1] = t;
    }
}

void array_list_bubble_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    bool exchanged = true;
    while (exchanged){
        exchanged = false;
        for (int i = 0; i < list->size - 1; i++){
            if (comparator(list->array[i], list->array[i + 1]) > 0){
                exchanged = true;
                array_list_swap(list, i, i + 1);
            }
        }
    }
}

void array_list_selection_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    for (int i = 0; i < list->size - 1; i++){
        void* min = list->array[i];
        int pos = i;
        for (int j = i + 1; j < list->size; j++){
            if (comparator(list->array[j], min) < 0){
                min = list->array[j];
                pos = j;
            }
        }
        if (pos != i){
            list->array[pos] = list->array[i];
            list->array[i] = min;
        }
    }
}

void array_list_quick_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    array_list_quick_sort_r(list, 0, list->size - 1, comparator);
}

void array_list_quick_sort2(Array_list_ptr list, int (*comparator)(const void *, const void *, const void *), void* arg) {
    array_list_quick_sort_r2(list, 0, list->size - 1, comparator, arg);
}

void array_list_quick_sort_r(Array_list_ptr list, int first, int last, int (*comparator)(const void *, const void *)) {
    if (first < last){
        int pivot = array_list_partition(list, first, last, comparator);
        array_list_quick_sort_r(list, first, pivot - 1, comparator);
        array_list_quick_sort_r(list, pivot + 1, last, comparator);
    }
}

void array_list_quick_sort_r2(Array_list_ptr list, int first, int last,
                              int (*comparator)(const void *, const void *, const void *), void* arg) {

    if (first < last){
        int pivot = array_list_partition2(list, first, last, comparator, arg);
        array_list_quick_sort_r2(list, first, pivot - 1, comparator, arg);
        array_list_quick_sort_r2(list, pivot + 1, last, comparator, arg);
    }
}

int array_list_partition(Array_list_ptr list, int first, int last, int (*comparator)(const void *, const void *)) {
    void* x = list->array[last];
    int i = first - 1;
    for (int j = first; j < last; j++){
        if (comparator(list->array[j], x) <= 0){
            i++;
            array_list_swap(list, i, j);
        }
    }
    array_list_swap(list, i + 1, last);
    return i + 1;
}

int array_list_partition2(Array_list_ptr list, int first, int last,
                          int (*comparator)(const void *, const void *, const void *), void* arg) {
    void* x = list->array[last];
    int i = first - 1;
    for (int j = first; j < last; j++){
        if (comparator(list->array[j], x, arg) <= 0){
            i++;
            array_list_swap(list, i, j);
        }
    }
    array_list_swap(list, i + 1, last);
    return i + 1;
}

void array_list_merge_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    array_list_merge_sort_r(list, 0, list->size - 1, comparator);
}

void array_list_merge_sort_r(Array_list_ptr list, int first, int last, int (*comparator)(const void *, const void *)) {
    if (first < last){
        int pivot = (first + last) / 2;
        array_list_merge_sort_r(list, first, pivot, comparator);
        array_list_merge_sort_r(list, pivot + 1, last, comparator);
        array_list_merge(list, first, pivot, last, comparator);
    }
}

void
array_list_merge(Array_list_ptr list, int start, int middle, int end, int (*comparator)(const void *, const void *)) {
    int leftCount = middle - start + 1;
    int rightCount = end - middle;
    void** leftPart = malloc(leftCount * sizeof(void*));
    void** rightPart = malloc(rightCount * sizeof(void*));
    for (int i = 0; i < leftCount; i++){
        leftPart[i] = list->array[start + i];
    }
    for (int i = 0; i < rightCount; i++){
        rightPart[i] = list->array[middle + i + 1];
    }
    int i = 0, j = 0;
    for (int k = start; k <= end; k++){
        if (j == rightCount){
            list->array[k] = leftPart[i];
            i++;
        } else {
            if (i == leftCount){
                list->array[k] = rightPart[j];
                j++;
            } else {
                if (comparator(leftPart[i], rightPart[j]) <= 0){
                    list->array[k] = leftPart[i];
                    i++;
                } else {
                    list->array[k] = rightPart[j];
                    j++;
                }
            }
        }
    }
    free(leftPart);
    free(rightPart);
}

void array_list_clear(Array_list_ptr list, void (*free_method)(void *)) {
    if (free_method != NULL) {
        for (int i = 0; i < list->size; i++) {
            free_method(list->array[i]);
        }
    }
    free(list->array);
    list->maxSize = 10;
    list->array = malloc(list->maxSize * sizeof(void *));
    list->size = 0;
}

Array_list_ptr create_array_list_of_double(int size) {
    Array_list_ptr values = create_array_list();
    for (int i = 0; i < size; i++){
        double *value = calloc(1, sizeof(double));
        array_list_add(values, value);
    }
    return values;
}
