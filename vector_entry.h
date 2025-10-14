/**
 * @brief `vector_entry` type definition
 * @file vector_entry.h
 * @author Charles Feyen
 * @date 10/14/2025
 * Class: CPE 2600
 * Section: 121
 */

#ifndef VECTOR_ENTRY_H
    #define VECTOR_ENTRY_H

    #include "vector.h"

    /**
     * @brief A storage entry for a 3-space vector 
     */
    typedef struct vector_entry {
        char * name;
        vector v;
    } vector_entry;
#endif