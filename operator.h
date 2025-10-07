/**
 * @brief enum that represents an operation
 * @file operator.h
 * @author Charles Feyen
 * @date 10/1/2025
 * Class: CPE 2600
 * Section: 121
 */


#ifndef OPERATOR_H
    #define OPERATOR_H

    /**
     * @brief enum for interpreting non math repl commands
     */
    typedef enum operator {
        Add,
        Sub,
        DotOrMul,
        Cross,
        NoSuchOp,
    } operator;
#endif