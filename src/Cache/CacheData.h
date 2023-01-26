//
// Created by Olcay Taner YILDIZ on 20.01.2023.
//

#ifndef DATASTRUCTURE_CACHEDATA_H
#define DATASTRUCTURE_CACHEDATA_H

struct cache_data{
    void* data;
    void* key;
};

typedef struct cache_data Cache_data;
typedef Cache_data* Cache_data_ptr;

Cache_data_ptr create_cache_data(void* data, void* key);
void free_cache_data(Cache_data_ptr cache_data, void free_key_method(void *), void free_data_method(void *));

#endif //DATASTRUCTURE_CACHEDATA_H
