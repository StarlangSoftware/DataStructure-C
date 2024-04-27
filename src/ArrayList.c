//
// Created by Olcay Taner YILDIZ on 18.01.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "ArrayList.h"
#include "Memory/Memory.h"

/**
 * Constructor of the array list. Allocates an empty array list. Initial array allocation size is 10 and will be
 * increased later.
 * @return Empty array list.
 */
Array_list_ptr create_array_list() {
    Array_list_ptr array_list = malloc_(sizeof(Array_list), "create_array_list_1");
    array_list->maxSize = 10;
    array_list->array = malloc_(array_list->maxSize * sizeof(void *), "create_array_list_2");
    array_list->size = 0;
    return array_list;
}

/**
 * Constructor of the array list for a given array of strings. Allocates an empty array list and adds strings in the
 * array one by one.
 * @param array Array containing strings to be inserted into the empty array list.
 * @param size Size of the array.
 * @return Allocated and filled array list.
 */
Array_list_ptr create_array_list_of_string(char **array, int size) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < size; i++) {
        array_list_add(result, array[i]);
    }
    return result;
}

/**
 * Constructor of the array list for a given array of integers. Allocates an empty array list and adds integers in the
 * array one by one.
 * @param array Array containing integers to be inserted into the empty array list.
 * @param size Size of the array.
 * @return Allocated and filled array list.
 */
Array_list_ptr create_array_list_of_int(int *array, int size) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < size; i++) {
        array_list_add_int(result, array[i]);
    }
    return result;
}

/**
 * Destructor method for the array list. Deallocates memory allocated for the array list and the contents of the
 * elements if needed.
 * @param array_list Array list
 * @param free_method Destructor method for the contents of the elements of the array
 */
void free_array_list(Array_list_ptr array_list, void free_method(void *)) {
    if (free_method != NULL) {
        for (int i = 0; i < array_list->size; i++) {
            free_method(array_list->array[i]);
        }
    }
    free_(array_list->array);
    free_(array_list);
}

/**
 * Checks if the array list is full or not. If the array list is full, it automatically increases its size by 2 and
 * moves the original elements to newly allocated space.
 * @param array_list Array list
 */
void check_and_increase_size(Array_list_ptr array_list) {
    if (array_list->size == array_list->maxSize) {
        array_list->maxSize *= 2;
        array_list->array = realloc_(array_list->array, array_list->maxSize * sizeof(void *), "check_and_increase_size");
    }
}

/**
 * Adds an element to the array list
 * @param array_list Array list
 * @param item Item to be added.
 */
void array_list_add(Array_list_ptr array_list, void *item) {
    check_and_increase_size(array_list);
    array_list->array[array_list->size] = item;
    array_list->size++;
}

/**
 * Adds a double to the array list. Allocates memory to store the double.
 * @param array_list Array list
 * @param value Number to be added.
 */
void array_list_add_double(Array_list_ptr array_list, double value) {
    double *item = malloc_(sizeof(double), "array_list_add_double");
    *item = value;
    array_list_add(array_list, item);
}

/**
 * Inserts a new element to a given index in the array list. The method shifts all elements after i one right and
 * inserts the new element into the position i.
 * @param array_list Array list
 * @param index Index to insert the new item
 * @param item Item to be inserted.
 */
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

/**
 * Returns the element at the given index.
 * @param array_list Array list
 * @param index Index
 * @return If the index is valid, returns the element at that index. Otherwise, it returns NULL.
 */
void *array_list_get(const Array_list* array_list, int index) {
    if (index < 0 || index >= array_list->size) {
        return NULL;
    }
    return array_list->array[index];
}

/**
 * Returns the double number at the given index.
 * @param array_list Array list
 * @param index Index
 * @return Returns the number at the given index.
 */
double array_list_get_double(const Array_list* array_list, int index) {
    return *((double *) array_list_get(array_list, index));
}

/**
 * Adds all elements in the source array list to the end of the destination array list.
 * @param dst Destination array list
 * @param src Source array list
 */
void array_list_add_all(Array_list_ptr dst, const Array_list* src) {
    if (dst->size + src->size > dst->maxSize) {
        dst->maxSize = (dst->size + src->size) * 2;
        dst->array = realloc_(dst->array, dst->maxSize * sizeof(void *), "array_list_add_all");
    }
    for (int i = 0; i < src->size; i++){
        dst->array[dst->size + i] = src->array[i];
    }
    dst->size += src->size;
}

/**
 * Checks if the aray list contains a specific item. Comparison will be done using the comparator.
 * @param list Array list
 * @param data Item to be searched.
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 * @return True if the array list contains the item, false otherwise.
 */
bool array_list_contains(const Array_list* list, const void *data, int (*comparator)(const void *, const void *)) {
    for (int i = 0; i < list->size; i++) {
        if (comparator(data, list->array[i]) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if the aray list contains a specific item. Comparison will be done using the comparator. The function returns
 * the index of the item if found, -1 otherwise.
 * @param list Array list
 * @param data Item to be searched.
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 * @return The index of the item if found, -1 otherwise.
 */
int array_list_index_of(const Array_list* list, const void *data, int (*comparator)(const void *, const void *)) {
    for (int i = 0; i < list->size; i++) {
        if (comparator(data, list->array[i]) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Checks if the array list is empty or not.
 * @param list Array list
 * @return True if the array list is empty, false otherwise.
 */
bool is_array_list_empty(const Array_list* list) {
    return list->size == 0;
}

/**
 * Sorts the array list using dummy sort algorithm. The dummy sort algorithm checks all possible pairs for displacement
 * and does swap when there is displacement.
 * @param list Array list to sort
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
void array_list_dummy_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    for (int i = 0; i < list->size; i++){
        for (int j = i + 1; j < list->size; j++){
            if (comparator(list->array[i], list->array[j]) > 0){
                array_list_swap(list, i, j);
            }
        }
    }
}

/**
 * Sort the array list using the merge sort algorithm. Wrapper to the merge sort algorithm.
 * @param list Array list to sort
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
void array_list_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    array_list_merge_sort(list, comparator);
}

/**
 * Constructs and returns a sub array list (taking all elements between indexes first_index inclusive and last_index
 * not inclusive) of the original array list.
 * @param list Array list
 * @param first_index Index of the first element in the sublist
 * @param last_index One large than the index of the last element in the sublist
 * @return A sub array list containing all elements between indexes first_index inclusive and last_index not inclusive
 */
Array_list_ptr sub_list(const Array_list* list, int first_index, int last_index) {
    Array_list_ptr result = create_array_list();
    for (int i = first_index; i < last_index; i++) {
        array_list_add(result, list->array[i]);
    }
    return result;
}

/**
 * Shuffles the array list as follows: For every index i starting from 0, generate a random index r between [i, size - 1]
 * and swap elements indexed i and r.
 * @param list Array list to shuffle
 * @param seed Seed to generate random number
 */
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

/**
 * Removes the element to a given index in the array list. The method shifts all elements starting index one left. The
 * method also deallocates memory for the contents of the removed element.
 * @param array_list Array list
 * @param index Index of the item to be removed
 * @param free_method Destructor method for the contents of the elements of the array
 */
void array_list_remove(Array_list_ptr list, int index, void (*free_method)(void *)) {
    if (free_method != NULL) {
        free_method(list->array[index]);
    }
    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
}

/**
 * Replaces the element at a given index with a new element. The method also deallocates memory for the contents of the
 * replaced element.
 * @param list Array list
 * @param index Index of the item to be replaced.
 * @param item Item to be inserted instead of the removed item.
 * @param free_method Destructor method for the contents of the elements of the array
 */
void array_list_replace(Array_list_ptr list, int index, void *item, void (*free_method)(void *)) {
    if (free_method != NULL) {
        free_method(list->array[index]);
    }
    list->array[index] = item;
}

/**
 * Checks if two array are equal or not, both in terms of size and in terms of element equality. Element equality is
 * controlled via the comparator method.
 * @param list1 First array list
 * @param list2 Second array list
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 * @return True if both size and the contents of the array are equal, false otherwise.
 */
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

/**
 * Swaps two elements in the array list given their indexes.
 * @param list Array list
 * @param index1 Index of the first element
 * @param index2 Index of the second element
 */
void array_list_swap(Array_list_ptr list, int index1, int index2) {
    void* tmp = list->array[index1];
    list->array[index1] = list->array[index2];
    list->array[index2] = tmp;
}

/**
 * Sorts the array list using insertion sort.
 * @param list Array list to sort
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
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

/**
 * Sorts the array list using bubble sort.
 * @param list Array list to sort
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
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

/**
 * Sorts the array list using selection sort.
 * @param list Array list to sort
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
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

/**
 * Sorts the array list using quick sort.
 * @param list Array list to sort
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
void array_list_quick_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    array_list_quick_sort_r(list, 0, list->size - 1, comparator);
}

/**
 * Sorts the array list using quick sort. The function also takes an argument which is used in comparator method.
 * @param list Array list to sort
 * @param comparator Comparator function to compare the contents of the elements in the array list. The method utilizes
 * the arg argument to do the comparison.
 * @param arg Argument used in comparison of two elements.
 */
void array_list_quick_sort2(Array_list_ptr list, int (*comparator)(const void *, const void *, const void *), const void* arg) {
    array_list_quick_sort_r2(list, 0, list->size - 1, comparator, arg);
}

/**
 * Recursive quick sort method that sorts all elements between indexes first and last in the array list.
 * @param list Array list to sort
 * @param first First index of the array
 * @param last Last index of the array
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
void array_list_quick_sort_r(Array_list_ptr list, int first, int last, int (*comparator)(const void *, const void *)) {
    if (first < last){
        int pivot = array_list_partition(list, first, last, comparator);
        array_list_quick_sort_r(list, first, pivot - 1, comparator);
        array_list_quick_sort_r(list, pivot + 1, last, comparator);
    }
}

/**
 * Recursive quick sort method that sorts all elements between indexes first and last in the array list. The function
 * also takes an argument which is used in comparator method.
 * @param list Array list to sort
 * @param first First index of the array
 * @param last Last index of the array
 * @param comparator Comparator function to compare the contents of the elements in the array list. The method utilizes
 * the arg argument to do the comparison.
 * @param arg Argument used in comparison of two elements.
 */
void array_list_quick_sort_r2(Array_list_ptr list, int first, int last,
                              int (*comparator)(const void *, const void *, const void *), const void* arg) {

    if (first < last){
        int pivot = array_list_partition2(list, first, last, comparator, arg);
        array_list_quick_sort_r2(list, first, pivot - 1, comparator, arg);
        array_list_quick_sort_r2(list, pivot + 1, last, comparator, arg);
    }
}

/**
 * Partition algorithm that structures the list elements between first and last such that all elements less than pivot
 * are on the left side of  the pivot and all elements larger than pivot are on the right side of the pivot. The method
 * also returns the index of the pivot.
 * @param list Array list
 * @param first First index of the array
 * @param last Last index of the array
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 * @return Index of the pivot
 */
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

/**
 * Partition algorithm that structures the list elements between first and last such that all elements less than pivot
 * are on the left side of  the pivot and all elements larger than pivot are on the right side of the pivot. The method
 * also returns the index of the pivot. The function also takes an argument which is used in comparator method.
 * @param list Array list
 * @param first First index of the array
 * @param last Last index of the array
 * @param comparator Comparator function to compare the contents of the elements in the array list. The method utilizes
 * the arg argument to do the comparison.
 * @param arg Argument used in comparison of two elements.
 * @return Index of the pivot
 */
int array_list_partition2(Array_list_ptr list, int first, int last,
                          int (*comparator)(const void *, const void *, const void *), const void* arg) {
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

/**
 * Sorts the array list using the mergesort algorithm.
 * @param list Array list to be sorted.
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
void array_list_merge_sort(Array_list_ptr list, int (*comparator)(const void *, const void *)) {
    array_list_merge_sort_r(list, 0, list->size - 1, comparator);
}

/**
 * Sorts the array list using the mergesort algorithm. The function also takes an argument which is used in comparator
 * method.
 * @param list Array list to be sorted.
 * @param comparator Comparator function to compare the contents of the elements in the array list. The method utilizes
 * the arg argument to do the comparison.
 * @param arg Argument used in comparison of two elements.
 */
void array_list_merge_sort2(Array_list_ptr list, int (*comparator)(const void *, const void *, const void *),
                            const void *arg) {
    array_list_merge_sort_r2(list, 0, list->size - 1, comparator, arg);
}

/**
 * Recursive merge sort algorithm. Sorts the elements indexed between first and last using merge sort algorithm.
 * @param list Array list to be sorted.
 * @param first First index of the array
 * @param last Last index of the array
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
void array_list_merge_sort_r(Array_list_ptr list, int first, int last, int (*comparator)(const void *, const void *)) {
    if (first < last){
        int pivot = (first + last) / 2;
        array_list_merge_sort_r(list, first, pivot, comparator);
        array_list_merge_sort_r(list, pivot + 1, last, comparator);
        array_list_merge(list, first, pivot, last, comparator);
    }
}

/**
 * Recursive merge sort algorithm. Sorts the elements indexed between first and last using merge sort algorithm. The
 * function also takes an argument which is used in comparator method.
 * @param list Array list to be sorted.
 * @param first First index of the array
 * @param last Last index of the array
 * @param comparator Comparator function to compare the contents of the elements in the array list. The method utilizes
 * the arg argument to do the comparison.
 * @param arg Argument used in comparison of two elements.
 */
void array_list_merge_sort_r2(Array_list_ptr list, int first, int last,
                              int (*comparator)(const void *, const void *, const void *), const void *arg) {
    if (first < last){
        int pivot = (first + last) / 2;
        array_list_merge_sort_r2(list, first, pivot, comparator, arg);
        array_list_merge_sort_r2(list, pivot + 1, last, comparator, arg);
        array_list_merge2(list, first, pivot, last, comparator, arg);
    }
}

/**
 * Merges two sorted subarrays list[start, middle] and list[middle, end] to get sorted array [start, end].
 * @param list Array list
 * @param start Start index of the first subarray.
 * @param middle End index of the first and start index of the second subarray.
 * @param end End index of the second subarray.
 * @param comparator Comparator function to compare the contents of the elements in the array list.
 */
void
array_list_merge(Array_list_ptr list, int start, int middle, int end, int (*comparator)(const void *, const void *)) {
    int leftCount = middle - start + 1;
    int rightCount = end - middle;
    void* leftPart[leftCount];
    void* rightPart[rightCount];
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
}

/**
 * Merges two sorted subarrays list[start, middle] and list[middle, end] to get sorted array [start, end]. The function
 * also takes an argument which is used in comparator method.
 * @param list Array list
 * @param start Start index of the first subarray.
 * @param middle End index of the first and start index of the second subarray.
 * @param end End index of the second subarray.
 * @param comparator Comparator function to compare the contents of the elements in the array list. The method utilizes
 * the arg argument to do the comparison.
 * @param arg Argument used in comparison of two elements.
 */
void array_list_merge2(Array_list_ptr list, int start, int middle, int end,
                       int (*comparator)(const void *, const void *, const void *), const void *arg) {
    int leftCount = middle - start + 1;
    int rightCount = end - middle;
    void* leftPart[leftCount];
    void* rightPart[rightCount];
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
                if (comparator(leftPart[i], rightPart[j], arg) <= 0){
                    list->array[k] = leftPart[i];
                    i++;
                } else {
                    list->array[k] = rightPart[j];
                    j++;
                }
            }
        }
    }
}

/**
 * Removes all elements from the array list and deallocates the contents of all elements in it.
 * @param list Array list to be cleared.
 * @param free_method Destructor method for the contents of the elements of the array
 */
void array_list_clear(Array_list_ptr list, void (*free_method)(void *)) {
    if (free_method != NULL) {
        for (int i = 0; i < list->size; i++) {
            free_method(list->array[i]);
        }
    }
    free_(list->array);
    list->maxSize = 10;
    list->array = malloc_(list->maxSize * sizeof(void *), "array_list_clear");
    list->size = 0;
}

/**
 * Creates an array list of size zeros.
 * @param size Size of the array list.
 * @return Array list.
 */
Array_list_ptr create_array_list_of_double(int size) {
    Array_list_ptr values = create_array_list();
    for (int i = 0; i < size; i++){
        double *value = calloc_(1, sizeof(double), "create_array_list_of_double");
        array_list_add(values, value);
    }
    return values;
}

/**
 * Deallocates the array list, which contains array list as elements. Therefore, the array list is actually an array
 * list of array lists.
 * @param array_list 2d Array list
 * @param free_method Destructor method for the contents of the elements of the array
 */
void free_2d_array_list(Array_list_ptr array_list, void (*free_method)(void *)) {
    for (int i = 0; i < array_list->size; i++){
        Array_list_ptr list = array_list_get(array_list, i);
        free_array_list(list, free_method);
    }
    free_array_list(array_list, NULL);
}

/**
 * Returns the integer at the given index.
 * @param array_list Array list
 * @param index Index
 * @return Returns the integer at the given index.
 */
int array_list_get_int(const Array_list *array_list, int index) {
    return *((int *) array_list_get(array_list, index));
}

/**
 * Enlarges the array list to the given new size.
 * @param array_list Array list to be enlarged.
 * @param new_size New size of the array list.
 */
void array_list_resize(Array_list_ptr array_list, int new_size) {
    if (array_list->size < new_size) {
        array_list->maxSize = new_size;
        array_list->size = new_size;
        array_list->array = realloc_(array_list->array, array_list->maxSize * sizeof(void *), "array_list_resize");
    }
}

/**
 * Adds a integer to the array list. Allocates memory to store the integer.
 * @param array_list Array list
 * @param value Number to be added.
 */
void array_list_add_int(Array_list_ptr array_list, int value) {
    int *item = malloc_(sizeof(int), "array_list_add_int");
    *item = value;
    array_list_add(array_list, item);
}

/**
 * Allocates a 2 dimensional rectangular array.
 * @param size1 Size of the first dimension.
 * @param size2 Size of the second dimension.
 * @return Allocated 2d array.
 */
double **allocate_2d(int size1, int size2) {
    double **result = malloc_(size1 * sizeof(double*), "allocate_2d_1");
    for (int i = 0; i < size1; i++){
        result[i] = calloc_(size2, sizeof(double), "allocate_2d_2");
    }
    return result;
}

/**
 * Deallocates given 2 dimensional array.
 * @param array Array to be dellocated.
 * @param size1 Size of the first dimension.
 */
void free_2d(double** array, int size1) {
    for (int i = 0; i < size1; i++){
        free_(array[i]);
    }
    free_(array);
}

/**
 * Clones an array list. It does not clone the elements inside the array list.
 * @param array_list Array list to be cloned.
 * @return Clone array list.
 */
Array_list_ptr clone_array_list(Array_list_ptr array_list) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < array_list->size; i++){
        array_list_add(result, array_list_get(array_list, i));
    }
    return result;
}

/**
 * Prints the array list to the screen. The method assumes that the elements are strings.
 * @param array_list Array list to be printed.
 */
void print_string_array_list(Array_list_ptr array_list) {
    printf("%s", (char*) array_list_get(array_list, 0));
    for (int i = 1; i < array_list->size; i++){
        printf(" %s", (char*) array_list_get(array_list, i));
    }
    printf("\n");
}
