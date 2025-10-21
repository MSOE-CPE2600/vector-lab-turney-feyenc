# Overview

This is a vector math REPL (Read-Execute-Print Loop). It preforms basic aritmetic operations on vectors and can store vectors in variables

# How to Build

Build with 
`gcc -Wall -o vector_calculator main.c repl.c storage.c vector_math.c` or `make`

# How to Run

Run the REPL with `./vector_calculator`

You may pass `-h` as a flag to print the help menu

# Program Commands

## Vector Literals

A vector literal is structured *`i`*,*`j`*,*`k`* or *`i`* *`j`* *`k`*

Examples:
```
> 1 0 0
> 0,1,0
> 1.6, 2.7, 3.1
```

## Commands
- `help` - Prints the help menu
- `list` - Lists all variables and their values
- `clear` - Removes all variables
- `quit` - Ends the REPL
- `load` *`file`* - loads the variables from a CSV table in *`file`* structured *`name`*,*`i`*,*`j`*,*`k`*
- `save` *`file`* - saves all variables to *`file`* as a CSV table structured *`name`*,*`i`*,*`j`*,*`k`*

Examples:
```
> load path/to/file.csv
> list
> quit
```

## Operations
- `+` - Adds two vectors
- `-` - Subtracts one vector from another
- `*` - Multiplies a vector by a scalar literal or finds the dot-product of two vectors
- `x` - Finds the cross-product of two vectors

Note: operations may only be used on variables and scalar literals

Examples:
```
> v + u
> v * 2.2
> i x j
```

## Assignment

Place a variable name followed by ` = ` before an expression that evaluates to a vector to save it under that name (note: there must be whitespace on both sides of the `=`)

Examples:
```
> i = 1 0 0
> j = 0 1 0
> k = i x j
```

# Dynamic Memory Usage

Variables are stored in a dynamically sized array. When the array overflows it is reallocated with double size.

When `clear` is used the array is freed and the array pointer is null. When the next variable is stored the array is allocated with a small default size.