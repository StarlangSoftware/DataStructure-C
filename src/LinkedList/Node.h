//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#ifndef DATASTRUCTURE_NODE_H
#define DATASTRUCTURE_NODE_H

struct node {
    void *data;
    struct node *previous;
    struct node *next;
};

typedef struct node Node;
typedef Node *Node_ptr;

Node_ptr create_node(void *data);

void free_node(Node_ptr node, void free_method(void *data));

#endif //DATASTRUCTURE_NODE_H
