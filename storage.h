/**
 * @brief function headers for vector storage
 * @file storage.h
 * @author Charles Feyen
 * @date 10/14/2025
 * Class: CPE 2600
 * Section: 121
 */

#ifndef STORAGE_H
    #include "vector_entry.h"
    #include <stdio.h>

    #define STORAGE_H
    #define DEFAULT_STORAGE_CAPACITY 4

    /**
     * @brief stores a pointer under the given name
     * @param name the name to store the vector under
     * @param v the vector
     * @return `0` on success, `1` if there is not enough space left to store the vector
     */
    int store(const char * name, const vector v);

    /**
     * @brief gets a pointer to a vector by the name it is stored under
     * @param name the name of the vector to get
     * @return a pointer to the vector, `NULL` if the name doesn't exist
     */
    vector *get(const char * name);

    /**
     * @brief clears the storage and resets the allocated memory
     */
    void clear();

    /**
     * @brief prints each vector
     */
    void list();

    /**
     * @brief saves all stored vectors to a csv file
     * @param csv the file (must be opened in write mode)
     */
    void save(FILE *csv);
#endif