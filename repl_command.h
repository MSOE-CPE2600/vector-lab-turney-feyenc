/**
 * @brief enum for interpreting non math repl commands
 * @file repl_command.h
 * @author Charles Feyen
 * @date 10/14/2025
 * Class: CPE 2600
 * Section: 121
 */


#ifndef REPL_COMMAND_H
    #define REPL_COMMAND_H

    /**
     * @brief enum for interpreting non math repl commands
     */
    typedef enum repl_command {
        Quit,
        List,
        Clear,
        Help,
        Load,
        Save,
        None,
    } repl_command;
#endif