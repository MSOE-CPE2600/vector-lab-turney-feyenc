/**
 * @brief `vector_entry` type definition
 * @file vector_entry.h
 * @author Charles Feyen
 * @date 10/1/2025
 * Class: CPE 2600
 * Section: 121
 */

#ifndef VECTOR_ENTRY_H
    #define VECTOR_ENTRY_H
    #define DEFAULT_VECTOR_ENTRY (vector_entry) { name: NULL, v: ZERO_VEC }

    #include "vector.h"

    /**
     * @brief A storage entry for a 3-space vector 
     */
    typedef struct vector_entry {
        char * name;
        vector v;
    } vector_entry;
#endif