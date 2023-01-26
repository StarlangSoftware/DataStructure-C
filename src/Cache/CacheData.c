//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#include <stdlib.h>
#include "CacheData.h"

Cache_data_ptr create_cache_data(void *data, void *key) {
    Cache_data_ptr result = malloc(sizeof(Cache_data));
    result->key = key;
    result->data = data;
    return result;
}

void free_cache_data(Cache_data_ptr cache_data, void (*free_key_method)(void *), void (*free_data_method)(void *)) {
    free_key_method(cache_data->key);
    free_data_method(cache_data->data);
    free(cache_data);
}
