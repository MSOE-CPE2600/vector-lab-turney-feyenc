/**
 * @brief functions for implementing the repl
 * @file repl.c
 * @author Charles Feyen
 * @date 10/14/2025
 * Class: CPE 2600
 * Section: 121
 */

#include <stdio.h>
#include "repl.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector_math.h"
#include "storage.h"
#include "repl_command.h"
#include "operator.h"

void prompt(char *buffer) {
    printf("vecmath> ");
    fgets(buffer, GET_NUMBER, stdin);
}

int prompt_parse_and_run() {
    // gets input
    char input[GET_NUMBER + 1];
    prompt(input);
    int len = strlen(input);

    // skips empty lines
    if (len <= 1) {
        return 1;
    }

    // parses and stores five tokens
    char *toks[5] = {
        strtok(input, TOK_SEP),
        strtok(NULL, TOK_SEP),
        strtok(NULL, TOK_SEP),
        strtok(NULL, TOK_SEP),
        strtok(NULL, TOK_SEP),
    };

    // logs an error if there are extra tokens
    if (strtok(NULL, TOK_SEP) != NULL) {
        puts("<invalid expression: extra tokens>");
        return 1;
    }
    
    // if the line is only spaces
    if (toks[0] == NULL || !strcmp(toks[0], "")) {
        return 1;
    }

    // parses and handles any initial command
    switch (str_to_repl_command(toks[0])) {
    case Quit:
        return 0;
    case Clear:
        clear();
        puts("<storage cleared>");
        return 1;
    case List:
        list();
        return 1;
    case Help:
        print_help();
        return 1;
    case Load:
        if (toks[1] == NULL) {
            puts("<no file provided>");
            return 1;
        }

        FILE *rcsv = fopen(toks[1], "r");

        if (rcsv == NULL) {
            printf("<No file: %s>\n", toks[1]);
            return 1;
        }

        load(rcsv);

        fclose(rcsv);

        return 1;
    case Save:
        if (toks[1] == NULL) {
            puts("<no file provided>");
            return 1;
        }

        FILE *wcsv = fopen(toks[1], "w");

        if (wcsv == NULL) {
            printf("<No file: %s>\n", toks[1]);
            return 1;
        }

        save(wcsv);

        fclose(wcsv);

        return 1;
    default:
        break;
    }

    char *assign = NULL;
    int expr_offset = 0;

    // determines if an expression will be assigned to a variable
    if (toks[1] != NULL && !strcmp(toks[1], "=")) {
        if (is_num(toks[0])) {
            printf("<Cannot assign to '%s'>\n", toks[0]);
            return 1;
        }

        assign = toks[0];
        expr_offset = 2;
    } else if (toks[4] != NULL || toks[3] != NULL) {
        // logs an error if there are extra tokens
        puts("<invalid expression: extra tokens>");
        return 1;
    }

    // calculates the result of the expression
    vector result;
    bool result_is_vec = false;
    if (evaluate(toks + expr_offset, &result, &result_is_vec)) {
        return 1;
    }

    // prints the result
    if (result_is_vec) {
        if (assign != NULL) {
            printf("%s = ", assign);
        }

        println_vector(&result);
    }

    // stores the result if applicable
    if (assign != NULL) {
        if (result_is_vec) {
            store(assign, result);
        } else {
            printf("<Non-vector value cannot be assigned to '%s'>\n", assign);
        }
    }

    return 1;
}

int evaluate(char **expr_toks, vector *result, bool *result_is_vec) {
    // determines which tokens are numbers and parses the potential operator
    const bool first_is_num = is_num(expr_toks[0]);
    const bool second_is_num = is_num(expr_toks[1]);
    const bool third_is_num = is_num(expr_toks[2]);
    const operator op = str_to_op(expr_toks[1]);

    if (expr_toks[1] == NULL && expr_toks[2] == NULL) {
        // gets a variable value
        vector *vec = get(expr_toks[0]);
        if (vec != NULL) {
            *result = *vec;
            *result_is_vec = true;
        }
    } else if (first_is_num && second_is_num && (third_is_num || expr_toks[2] == NULL)) {
        // creates a vector from scalar components
        const double i = atof(expr_toks[0]);
        const double j = atof(expr_toks[1]);
        double k = 0.0;
        
        if (expr_toks[2] != NULL) {
            k = atof(expr_toks[2]);
        }

        *result = new_vector(i, j, k);
        *result_is_vec = true;
    } else if (op != NoSuchOp && !first_is_num && !third_is_num) {
        // preforms an operation on two vector variables

        // gets the first vector
        vector *u = get(expr_toks[0]);
        if (u == NULL) {
            return 1;
        }

        // gets the second vector
        vector *v = get(expr_toks[2]);
        if (v == NULL) {
            return 1;
        }

        // applies the operation
        switch (op) {
        case Add:
            *result = add(*u, *v);
            *result_is_vec = true;
            break;
        case Sub:
            *result = sub(*u, *v);
            *result_is_vec = true;
            break;
        case Cross:
            *result = cross_product(*u, *v);
            *result_is_vec = true;
            break;
        case DotOrMul:
            double prod = dot_product(*u, *v);
            printf("%f\n", prod);
            break;
        default:
            break;
        }
    } else if (
        op == DotOrMul
        && expr_toks[0] != NULL
        && expr_toks[2] != NULL
        && (first_is_num ^ third_is_num)
    ) {
        // does a scalar multiplication
        double a;
        vector *v;

        // gets a and v
        if (first_is_num) {
            a = atof(expr_toks[0]);
            if ((v = get(expr_toks[2])) == NULL) {
                return 1;
            }
        } else {
            a = atof(expr_toks[2]);
            if ((v = get(expr_toks[0])) == NULL) {
                return 1;
            }
        }
        
        // calculates the result
        *result = mul(a, *v);
        *result_is_vec = true;
    } else {
        // logs an error
        puts("<invalid expression>");
        return 1;
    }

    return 0;
}

bool is_num(const char *s) {
    if (s == NULL) {
        return false;
    }

    int len = strlen(s);
    int dot = 0;

    for (int i = 0; i < len; i++) {
        if (i == 0 && s[0] == '-') {
            continue;
        }

        int is_digit = s[i] >= '0' && s[i] <= '9';

        if (!is_digit) {
            if (s[i] == '.' && dot == 0) {
                dot++;
            } else {
                return false;
            }
        }
    }
    
    return len > 0;
}

repl_command str_to_repl_command(const char *str) {
    if (!strcmp(str, "quit")) {
        return Quit;
    }

    if (!strcmp(str, "list")) {
        return List;
    }

    if (!strcmp(str, "clear")) {
        return Clear;
    }

    if (!strcmp(str, "help")) {
        return Help;
    }

    if (!strcmp(str, "load")) {
        return Load;
    }

    if (!strcmp(str, "save")) {
        return Save;
    }

    return None;
}

operator str_to_op(const char *str) {
    if (str == NULL) {
        return NoSuchOp;
    }

    if (!strcmp(str, "+")) {
        return Add;
    }

    if (!strcmp(str, "-")) {
        return Sub;
    }

    if (!strcmp(str, "*")) {
        return DotOrMul;
    }

    if (!strcmp(str, "x")) {
        return Cross;
    }

    return NoSuchOp;
}

void print_help() {
    puts("^");
    puts("| help: prints this help info");
    puts("| quit: exits the program");
    puts("| list: lists stored variables");
    puts("| clear: clears stored variables");
    puts("| load file: (where file is a csv file) loads vectors from file into storage");
    puts("| save file: (where file is a csv file) saves vectors from storage to file");
    puts("|");
    puts("| i j (where i and j are scalars) defines a vector");
    puts("| i j k (where i, j, and k are scalars) defines a vector");
    puts("|");
    puts("| u + v (where u and v are vectors) adds two vectors");
    puts("| u - v (where u and v are vectors) subtracts two vectors");
    puts("| u * v (where u and v are vectors) finds the dot-product of two vectors");
    puts("| u x v (where u and v are vectors) finds the cross-product of two vectors");
    puts("| a * v (where a is scalar and v is a vector) finds the scalar multiplication of a and v");
    puts("| v * a (where a is scalar and v is a vector) finds the scalar multiplication of a and v");
    puts("|");
    puts("| left = right (where left is an identifier and right is a vector expression)");
    puts("|   can be used to assign the vector on the right to the variable left");
    puts("|");
    puts("| ? (where ? is an identifier) accesses the values assigned to ?");
    puts("v");
}

int load(FILE * csv) {
    char buffer[GET_NUMBER + 1];
    int n = 0;

    while (!feof(csv)) {
        // gets the line
        fgets(buffer, GET_NUMBER, csv);

        // prevents issues with file final newlines
        size_t len = strlen(buffer);
        buffer[len - 1] = ' ';

        // gets the tokens
        char *toks[4] = {
            strtok(buffer, TOK_SEP),
            strtok(NULL, TOK_SEP),
            strtok(NULL, TOK_SEP),
            strtok(NULL, TOK_SEP),
        };

        // skip the line if it is only spaces
        if (toks[0] == NULL || !strcmp(toks[0], "")) {
            continue;
        }

        // handles extra numbers
        if (strtok(NULL, TOK_SEP) != NULL) {
            puts("<file error: invalid vector: extra numbers>");
            return 1;
        }

        // handles invalid numbers
        if (!is_num(toks[1]) || !is_num(toks[2]) || !is_num(toks[3])) {
            puts("<file error: invalid vector: invalid numbers>");
            return 1;
        }

        // creates the vector
        const vector v = new_vector(atof(toks[1]), atof(toks[2]), atof(toks[3]));

        // stores the vector, handles errors
        if (store(toks[0], v)) {
            return 1;
        }

        // logs the vectors being stored
        printf("%s = ", toks[0]);
        println_vector(&v);

        n++;
    }

    // prints how many vectors were loaded
    printf("<loaded %d vectors>\n", n);

    return 0;
}