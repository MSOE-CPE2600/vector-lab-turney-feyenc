/**
 * @brief runs a vector math repl
 * @file main.c
 * @author Charles Feyen
 * @date 10/7/2025
 * Class: CPE 2600
 * Section: 121
 * 
 * Compile with: gcc -Wall -o vector_calculator main.c repl.c storage.c vector_math.c
 */

#include "repl.h"
#include "storage.h"
#include <string.h>

/**
 * @brief runs the repl
 * @param argc the number of cli arguments
 * @param argv the cli arguments
 * @return returns 0 on success
 */
int main(int argc, char *argv[]) {
    // prints the help info if -h is passed
    if (argc >= 2 && !strcmp("-h", argv[1])) {
        print_help();
    }

    // runs the repl
    while (prompt_parse_and_run()) {}

    // clears storage
    clear();

    return 0;
}