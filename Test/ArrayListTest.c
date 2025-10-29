//
// Created by Olcay Taner YILDIZ on 18.02.2023.
//

#include "../src/ArrayList.h"
#include "../src/Memory/Memory.h"

int main() {
    start_memory_check();
    Array_list_ptr a = create_array_list();
    array_list_insert(a, 0, "ali");
    array_list_insert(a, 0, "topu");
    array_list_insert(a, 0, "at");
    free_array_list(a, NULL);
    end_memory_check();
}
