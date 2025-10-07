/**
 * @brief `vector` type definition
 * @file vector.h
 * @author Charles Feyen
 * @date 9/30/2025
 * Class: CPE 2600
 * Section: 121
 */

#ifndef VECTOR_H
    #define VECTOR_H
    #define ZERO_VEC (vector) { i: 0.0, j: 0.0, k: 0.0 }

    /**
     * @brief A 3-space vector 
     */
    typedef struct vector {
        double i;
        double j;
        double k;
    } vector;
#endif