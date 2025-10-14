/**
 * @brief growable list struct for storing vector entries
 * @file entry_vector.h
 * @author Charles Feyen
 * @date 10/14/2025
 * Class: CPE 2600
 * Section: 121
 */

#ifndef ENTRY_VECTOR_H
    #define ENTRY_VECTOR_H
    #define DEFAULT_ENTRY_VECTOR (entry_vector) { entries: NULL, len: 0, cap: 0 }

    #include "vector_entry.h"

    /**
     * @brief A vector (growable list) of `vector_entry`s
     */
    typedef struct entry_vector {
        vector_entry* entries;
        unsigned int len;
        unsigned int cap;
    } entry_vector;
#endif