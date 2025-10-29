//
// Created by Olcay Taner YILDIZ on 26.11.2023.
//

#ifndef DATASTRUCTURE_MEMORY_H
#define DATASTRUCTURE_MEMORY_H

#include <stddef.h>
#include "../HashMap/HashMap.h"

static Hash_map_ptr memory_map = NULL;

void start_memory_check();

void start_large_memory_check();

void start_medium_memory_check();

void start_x_large_memory_check();

void end_memory_check();

void* malloc_(size_t size);

void* realloc_(void *ptr, size_t size);

void* calloc_(size_t count, size_t size);

char* back_trace_info();

void free_(void* allocated);

#endif //DATASTRUCTURE_MEMORY_H
