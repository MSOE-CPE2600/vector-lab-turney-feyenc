/**
 * @brief functions for implementing the repl
 * @file repl.h
 * @author Charles Feyen
 * @date 10/6/2025
 * Class: CPE 2600
 * Section: 121
 */

#ifndef REPL_H
    #define REPL_H
    #define GET_NUMBER 80
    #include <stdbool.h>
    #include "vector.h"
    #include "repl_command.h"
    #include "operator.h"

    /**
     * @brief prompts the user for the next line
     * @param buffer the buffer the input is stored in,
     *  should have space for at least `GET_NUMBER` chars
     */
    void prompt(char * buffer);

    /**
     * @brief runs a line of the repl:
     * 
     *  - prompts the user for the next line
     * 
     *  - parses the input
     * 
     *  - executes the command
     * @return returns 0 if the repl should be exited
     */
    int prompt_parse_and_run();

    /**
     * @brief evaluates the given tokens as an expression
     * @param expr_tokens the list of tokens that make up the expression
     *  (does not include an identifier before `=` or an `=`)
     * @param result a pointer where the result is stored if it is a vector
     * @param result_is_vec a pointer that stores if the result was calculated to be a vector
     * @return returns 0 on success, 1 on error
     */
    int evaluate(char **expr_toks, vector *result, bool *result_is_vec);

    /**
     * @brief determines if a string is a number
     * @return the boolean dictating if a string is a number
     */
    bool is_num(const char *s);

    /**
     * @brief converts a string to a `repl_command`
     * @return the corresponding command, defaults to `None`
     */
    repl_command str_to_repl_command(const char *str);

    /**
     * @brief converts a string to an `operator`
     * @return the corresponding command, defaults to `NoSuchOp`
     */
    operator str_to_op(const char *str);

    /**
     * @brief prints the help message
     */
    void print_help();
#endif