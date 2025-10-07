/**
 * @brief functions for working with the `vector` type
 * @file vector_math.h
 * @author Charles Feyen
 * @date 9/30/2025
 * Class: CPE 2600
 * Section: 121
 */

#ifndef VECTOR_MATH_H
    #define VECTOR_MATH_H

    #include "vector.h"

    /**
     * @brief creates a new vector
     * @param i the i component of the new vector
     * @param j the j component of the new vector
     * @param k the k component of the new vector
     * @return the new vector
     */
    vector new_vector(const double i, const double j, const double k);

    /**
     * @brief prints a vector without a newline
     * @param v the vector to print
     */
    void print_vector(const vector *v);

    /**
     * @brief prints a vector with a newline
     * @param v the vector to print
     */
    void println_vector(const vector *v);

    /**
     * @brief adds two vectors
     * @param u the first vector
     * @param v the second vector
     * @return the result of adding the vectors
     */
    vector add(const vector u, const vector v);

    /**
     * @brief subtracts one vector from another
     * @param u the first vector
     * @param v the second vector
     * @return the result of subtracting `v` from `u`
     */
    vector sub(const vector u, const vector v);

    /**
     * @brief finds the scalar prodocut of number and a vector
     * @param a the number
     * @param v the vector
     * @return the scalar product of `a` and `v`
     */
    vector mul(const double a, const vector v);

    /**
     * @brief finds the dot prodocut of two vectors
     * @param u the first vector
     * @param v the second vector
     * @return the dot product of `u` and `v`
     */
    double dot_product(const vector u, const vector v);

    /**
     * @brief finds the coss prodocut of two vectors
     * @param u the first vector
     * @param v the second vector
     * @return the cross product of `u` and `v`
     */
    vector cross_product(const vector u, const vector v);
#endif