/**
 * @brief functions for vector storage
 * @file storage.c
 * @author Charles Feyen
 * @date 9/30/2025
 * Class: CPE 2600
 * Section: 121
 */

#include "vector.h"
#include "vector_math.h"
#include "vector_entry.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

// The buffer that stores the vectors
vector_entry vector_storage[STORAGE_CAPACITY] = {
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
    DEFAULT_VECTOR_ENTRY,
};

int store(const char * name, const vector v) {
    for (int i = 0; i < STORAGE_CAPACITY; i++) {
        const vector_entry entry = vector_storage[i];

        if (entry.name == NULL || !strcmp(name, entry.name)) {
            char *name_ptr = malloc(strlen(name) + 1);
            strcpy(name_ptr, name);
            name_ptr[strlen(name)] = '\0';
            vector_storage[i] = (vector_entry) { name: name_ptr, v };
            return 0;
        }
    }

    printf("No available space to store '%s'\n", name);
    return 1;
}

vector *get(const char * name) {
    if (name == NULL) {
        return NULL;
    }

    for (int i = 0; i < STORAGE_CAPACITY; i++) {
        const vector_entry entry = vector_storage[i];

        if (entry.name != NULL && !strcmp(name, entry.name)) {
            return &vector_storage[i].v;
        }
    }

    printf("<no such vector '%s'>\n", name);
    return NULL;
}

void clear() {
    for (int i = 0; i < STORAGE_CAPACITY; i++) {
        if (vector_storage[i].name != NULL) {
            free(vector_storage[i].name);
        }
        vector_storage[i] = DEFAULT_VECTOR_ENTRY;
    }
}

void list() {
    for (int i = 0; i < STORAGE_CAPACITY; i++) {
        vector_entry entry = vector_storage[i];

        if (entry.name != NULL) {
            printf("%7s: ", entry.name);
            print_vector(&entry.v);
            puts("");
        } else {
            printf("<vector %d unused>\n", i);
        }
    }
}