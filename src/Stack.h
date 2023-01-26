//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

#include "LinkedList/LinkedList.h"

struct stack{
    Linked_list_ptr list;
};

typedef struct stack Stack;
typedef Stack* Stack_ptr;

Stack_ptr create_stack();
void free_stack(Stack_ptr stack, void free_method(void *));
void push(Stack_ptr stack, void* item);
void* pop(Stack_ptr stack);
int is_stack_empty(Stack_ptr stack);

#endif //DATASTRUCTURE_STACK_H
