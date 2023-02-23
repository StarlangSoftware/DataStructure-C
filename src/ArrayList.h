//
// Created by Olcay Taner YILDIZ on 18.01.2023.
//

#ifndef DATASTRUCTURE_ARRAYLIST_H
#define DATASTRUCTURE_ARRAYLIST_H

struct array_list {
    void **array;
    int maxSize;
    int size;
};

typedef struct array_list Array_list;
typedef Array_list *Array_list_ptr;

Array_list_ptr create_array_list();

Array_list_ptr create_array_list_of_string(char *array[], int size);

Array_list_ptr create_array_list_of_int(int array[], int size);

void free_array_list(Array_list_ptr array_list, void free_method(void *data));

void check_and_increase_size(Array_list_ptr array_list);

void array_list_add(Array_list_ptr array_list, void *item);

void array_list_add_double(Array_list_ptr array_list, double value);

void array_list_insert(Array_list_ptr array_list, int index, void *item);

void *array_list_get(Array_list_ptr array_list, int index);

double array_list_get_double(Array_list_ptr array_list, int index);

void array_list_add_all(Array_list_ptr dst, Array_list_ptr src);

int array_list_contains(Array_list_ptr list, void *data, int comparator(void *item1, void *item2));

int array_list_equals(Array_list_ptr list1, Array_list_ptr list2, int comparator(void *item1, void *item2));

int array_list_index_of(Array_list_ptr list, void *data, int comparator(void *item1, void *item2));

void array_list_sort(Array_list_ptr list, int comparator(void *item1, void *item2));

int is_array_list_empty(Array_list_ptr list);

Array_list_ptr sub_list(Array_list_ptr list, int first_index, int last_index);

void array_list_shuffle(Array_list_ptr list);

void array_list_remove(Array_list_ptr list, int index, void free_method(void *data));

void array_list_replace(Array_list_ptr list, int index, void *item, void free_method(void *data));


#endif //DATASTRUCTURE_ARRAYLIST_H
