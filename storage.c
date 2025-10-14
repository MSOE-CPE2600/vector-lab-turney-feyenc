/**
 * @brief functions for vector storage
 * @file storage.c
 * @author Charles Feyen
 * @date 10/14/2025
 * Class: CPE 2600
 * Section: 121
 */

#include "vector.h"
#include "vector_math.h"
#include "vector_entry.h"
#include "entry_vector.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

// The buffer that stores the vectors
entry_vector vector_storage = DEFAULT_ENTRY_VECTOR;

int store(const char * name, const vector v) {
    // overwrites a vector of the same name
    for (int i = 0; i < vector_storage.len; i++) {
        const vector_entry entry = vector_storage.entries[i];

        if (entry.name == NULL || !strcmp(name, entry.name)) {
            store_to(name, v, i);
            return 0;
        }
    }

    // grows the vector if more space is needed
    if (vector_storage.len == vector_storage.cap) {
        unsigned int new_cap;

        // sets the new capacity
        if (vector_storage.cap == 0) {
            new_cap = DEFAULT_STORAGE_CAPACITY;
        } else {
            new_cap = vector_storage.cap * 2;
        }

        // reallocates memory
        // note: if entries is null this will simply allocate memory
        vector_entry *new_ptr = realloc(vector_storage.entries, new_cap * sizeof(vector_entry));

        // handles errors
        if (new_ptr == NULL) {
            printf("<Out of memory>\n");
            return 1;
        }

        // assigns pointer and capacity to storage vector
        vector_storage.entries = new_ptr;
        vector_storage.cap = new_cap;
    }

    // adds the vector to the end of the storage
    store_to(name, v, vector_storage.len);
    vector_storage.len++;

    return 0;
}

vector *get(const char * name) {
    if (name == NULL) {
        return NULL;
    }

    for (int i = 0; i < vector_storage.len; i++) {
        const vector_entry entry = vector_storage.entries[i];

        if (entry.name != NULL && !strcmp(name, entry.name)) {
            return &vector_storage.entries[i].v;
        }
    }

    printf("<no such vector '%s'>\n", name);
    return NULL;
}

void clear() {
    // frees the entry names
    for (int i = 0; i < vector_storage.len; i++) {
        if (vector_storage.entries[i].name != NULL) {
            free(vector_storage.entries[i].name);
        }
    }

    // frees the allocated memory
    free(vector_storage.entries);

    // resets the storage vector to default
    vector_storage = DEFAULT_ENTRY_VECTOR;
}

void list() {
    if (vector_storage.len == 0) {
        puts("<storage empty>");
    }

    for (int i = 0; i < vector_storage.len; i++) {
        vector_entry entry = vector_storage.entries[i];

        if (entry.name != NULL) {
            printf("%7s: ", entry.name);
            print_vector(&entry.v);
            puts("");
        } else {
            printf("<vector %d unused>\n", i);
        }
    }
}

void store_to(const char *name, const vector v, const unsigned int index) {
    char *name_ptr = malloc(strlen(name) + 1);
    strcpy(name_ptr, name);
    name_ptr[strlen(name)] = '\0';
    vector_storage.entries[index] = (vector_entry) { name: name_ptr, v };
}

void save(FILE *csv) {
    for (int i = 0; i < vector_storage.len; i++) {
        vector_entry entry = vector_storage.entries[i];

        if (entry.name != NULL) {
             fprintf(csv, "%s,%lf,%lf,%lf\n", entry.name, entry.v.i, entry.v.j, entry.v.k);
        } else {
            fprintf(csv, "\n");
        }
    }

    puts("saved all vectors");
}