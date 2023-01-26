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

void free_array_list(Array_list_ptr array_list, void free_method(void*)) {
    for (int i = 0; i < array_list->size; i++){
        free_method(array_list->array[i]);
    }
    free(array_list->array);
    free(array_list);
}

void check_and_increase_size(Array_list_ptr array_list) {
    if (array_list->size == array_list->maxSize){
        array_list->maxSize *= 2;
        array_list->array = realloc(array_list->array, array_list->maxSize * sizeof(void *));
    }
}

void array_list_add(Array_list_ptr array_list, void *item) {
    check_and_increase_size(array_list);
    array_list->array[array_list->size] = item;
    array_list->size++;
}

void array_list_insert(Array_list_ptr array_list, int index, void *item) {
    if (index < 0 || index > array_list->size){
        return;
    }
    if (index == array_list->size){
        array_list_add(array_list, item);
    } else {
        check_and_increase_size(array_list);
        memmove(array_list + ((index + 1) * sizeof(void *)), array_list + (index * sizeof(void *)), (array_list->size - index) * sizeof(void *));
        array_list->array[index] = item;
        array_list->size++;
    }
}

void *array_list_get(Array_list_ptr array_list, int index) {
    if (index < 0 || index >= array_list->size){
        return NULL;
    }
    return array_list->array[index];
}

void array_list_add_all(Array_list_ptr dst, Array_list_ptr src) {
    if (dst->size + src->size > dst->maxSize){
        dst->maxSize = (dst->size + src->size) * 2;
        dst->array = realloc(dst->array, dst->maxSize * sizeof(void *));
    }
    memcpy(dst->array + dst->size * (sizeof(void *)), src->array, src->size * (sizeof(void *)));
    dst->size += src->size;
}

int array_list_contains(Array_list_ptr list, void *data, int (*comparator)(void *, void *)) {
    for (int i = 0; i < list->size; i++){
        if (comparator(data, list->array[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int array_list_index_of(Array_list_ptr list, void *data, int (*comparator)(void *, void *)) {
    for (int i = 0; i < list->size; i++){
        if (comparator(data, list->array[i]) == 0){
            return i;
        }
    }
    return -1;
}

int is_array_list_empty(Array_list_ptr list) {
    return list->size == 0;
}

void array_list_sort(Array_list_ptr list, int (*comparator)(void *, void *)) {
    qsort(list->array, list->size, sizeof(void *), (int (*)(const void *, const void *)) comparator);
}

Array_list_ptr sub_list(Array_list_ptr list, int first_index, int last_index) {
    Array_list_ptr result = create_array_list();
    for (int i = first_index; i < last_index; i++){
        array_list_add(result, list->array[i]);
    }
    return result;
}
