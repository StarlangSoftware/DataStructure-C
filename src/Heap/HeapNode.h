//
// Created by Olcay Taner YILDIZ on 18.01.2023.
//

#ifndef DATASTRUCTURE_HEAPNODE_H
#define DATASTRUCTURE_HEAPNODE_H

struct heap_node{
    void* data;
};

typedef struct heap_node Heap_node;
typedef Heap_node* Heap_node_ptr;

Heap_node_ptr create_heap_node(void* data);
void free_heap_node(Heap_node_ptr node, void free_method(void* data));

#endif //DATASTRUCTURE_HEAPNODE_H
