//
// Created by Olcay Taner YILDIZ on 23.09.2023.
//

#include <stdio.h>
#include "../src/HashMap/HashMap.h"

int main(){
    char* words1[] = {"ali", "ayşe", "çift", "çöğüş"};
    char* words2[] = {"öç", "şişe", "Ali", "Çift",
                     "Çöğüş", "Şişe", "Öç", "ayşe", "çift"};
    Hash_map_ptr map1 = create_string_hash_map();
    for (int i = 0; i < 4; i++){
        hash_map_insert(map1,words1[i], words1[i]);
    }
    Hash_map_ptr map2 = create_string_hash_map();
    for (int i = 0; i < 9; i++){
        hash_map_insert(map2,words2[i], words2[i]);
    }
    hash_map_merge(map1, map2);
    Array_list_ptr list = key_list(map1);
    for (int i = 0; i < list->size; i++){
        printf("%s\n", (char*)array_list_get(list, i));
    }
}