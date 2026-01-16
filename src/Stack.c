//
// Created by Olcay Taner YILDIZ on 16.01.2023.
//

#include "Stack.h"
#include "Memory/Memory.h"

/**
 * Constructor for a stack. Allocates an empty stack.
 * @return Empty stack.
 */
Stack_ptr create_stack() {
    Stack_ptr result = malloc_(sizeof(Stack));
    result->list = create_linked_list(NULL);
    return result;
}

/**
 * Destructor method for the stack. Deallocates memory allocated for the stack and the contents of the
 * elements if needed.
 * @param stack Stack
 * @param free_method Destructor method for the contents of the elements of the stack
 */
void free_stack(Stack_ptr stack, void free_method(void *)) {
    free_linked_list(stack->list, free_method);
    free_(stack);
}

/**
 * Adds an element to stack.
 * @param stack Stack
 * @param item Item to be added.
 */
void push(Stack_ptr stack, void *item) {
    add_last(stack->list, create_node(item));
}

/**
 * Removes an element from the stack.
 * @param stack Stack
 * @return Item removed.
 */
void *pop(Stack_ptr stack) {
    return remove_last(stack->list);
}

/**
 * Checks if the stack is empty or not.
 * @param stack Stack
 * @return Returns true if the stack is empty, false otherwise.
 */
bool is_stack_empty(const Stack* stack) {
    return is_linked_list_empty(stack->list);
}

/**
 * Returns the topmost element of the stack.
 * @param stack Stack
 * @return Topmost element of the stack.
 */
void *peek(Stack_ptr stack) {
    if (is_linked_list_empty(stack->list)) {
        return NULL;
    }
    return stack->list->tail->data;
}
