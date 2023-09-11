//
// Created by Olcay Taner YILDIZ on 11.09.2023.
//

#include <stdio.h>
#include "../src/HashMap/HashSet.h"

int main(){
    char* words[] = {"ali", "ayşe", "çift", "çöğüş", "öç", "şişe", "Ali", "Çift",
                      "Çöğüş", "Şişe", "Öç"};
    Hash_set_ptr set = create_hash_set_of_string(words, 11);
    for (int i = 0; i < 6; i++){
        if (!hash_set_contains(set, words[i])){
            printf("Error in word %s\n", words[i]);
        }
    }
    free_hash_set(set, NULL);
}