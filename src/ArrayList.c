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

void *array_list_get(Array_list_ptr array_list, int index) {
    if (index < 0 || index >= array_list->size) {
        return NULL;
    }
    return array_list->array[index];
}

double array_list_get_double(Array_list_ptr array_list, int index) {
    return *((double *) array_list_get(array_list, index));
}

void array_list_add_all(Array_list_ptr dst, Array_list_ptr src) {
    if (dst->size + src->size > dst->maxSize) {
        dst->maxSize = (dst->size + src->size) * 2;
        dst->array = realloc(dst->array, dst->maxSize * sizeof(void *));
    }
    memcpy(dst->array + dst->size * (sizeof(void *)), src->array, src->size * (sizeof(void *)));
    dst->size += src->size;
}

int array_list_contains(Array_list_ptr list, void *data, int (*comparator)(void *, void *)) {
    for (int i = 0; i < list->size; i++) {
        if (comparator(data, list->array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int array_list_index_of(Array_list_ptr list, void *data, int (*comparator)(void *, void *)) {
    for (int i = 0; i < list->size; i++) {
        if (comparator(data, list->array[i]) == 0) {
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
    for (int i = first_index; i < last_index; i++) {
        array_list_add(result, list->array[i]);
    }
    return result;
}

void array_list_shuffle(Array_list_ptr list) {
    void *tmp;
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

int array_list_equals(Array_list_ptr list1, Array_list_ptr list2, int (*comparator)(void *, void *)) {
    if (list1->size != list2->size) {
        return 0;
    }
    for (int i = 0; i < list1->size; i++) {
        if (comparator(list1->array[i], list2->array[i]) != 0) {
            return 0;
        }
    }
    return 1;
}
