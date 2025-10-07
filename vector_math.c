/**
 * @brief functions for working with the `vector` type
 * @file vector_math.c
 * @author Charles Feyen
 * @date 9/30/2025
 * Class: CPE 2600
 * Section: 121
 */

#include "vector_math.h"
#include "vector.h"
#include <stdio.h>

vector new_vector(const double i, const double j, const double k) {
    return (vector) { i, j, k };
}

void print_vector(const vector *v) {
    if (v == NULL) {
        printf("<invalid vector>");
    } else {
        printf("< %11f, %11f, %11f >", v->i, v->j, v->k);
    }
}

void println_vector(const vector *v) {
    print_vector(v);
    puts("");
}

vector add(const vector u, const vector v) {
    return new_vector(u.i + v.i, u.j + v.j, u.k + v.k);
};

vector sub(const vector u, const vector v) {
    return new_vector(u.i - v.i, u.j - v.j, u.k - v.k);
};

vector mul(const double a, const vector v) {
    return new_vector(a * v.i, a * v.j, a * v.k);
};

double dot_product(const vector u, const vector v) {
    return u.i * v.i + u.j * v.j + u.k * v.k;
}

vector cross_product(const vector u, const  vector v) {
    const double i = u.j * v.k - u.k * v.j;
    const double j = -(u.i * v.k - u.k * v.i);
    const double k = u.i * v.j - u.j * v.i;

    return new_vector(i, j, k);
}