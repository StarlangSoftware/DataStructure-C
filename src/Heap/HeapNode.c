//
// Created by Olcay Taner YILDIZ on 18.01.2023.
//

#include <stdlib.h>
#include "HeapNode.h"

Heap_node_ptr create_heap_node(void* data){
    Heap_node_ptr result = malloc(sizeof(Heap_node));
    result->data = data;
    return result;
}

void free_heap_node(Heap_node_ptr node, void free_method(void* data)) {
    free_method(node->data);
    free(node);
}
