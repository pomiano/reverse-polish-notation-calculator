
# ONP Calculator (A&DS)

## Project Description

This project implements a calculator using Reverse Polish Notation (RPN) that handles various arithmetic operations and functions. The calculator converts infix expressions to postfix notation and evaluates them, printing the stack state before each operation.

## Operations Supported:

- **Arithmetic operations**: `+`, `-`, `*`, `/` (on integers, with division results rounded down)
- **Conditional function**: `IF(a, b, c)` – returns b if a > 0, otherwise c
- **Unary function**: `N a` – negation
- **Multi-argument functions**: `MIN(a1, a2, ..., an)`, `MAX(a1, a2, ..., an)`
- **Parentheses**: `(...)`

## Requirements:

- The calculator must be implemented using a stack.
- The stack cannot be implemented using standard libraries for data storage.
- The program should not store expressions in infix notation but should process tokens during conversion.
- Error handling for issues like division by zero, with the message `ERROR`.

## Example Usage

### Input:

```
4
MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) .
2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .
N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .
IF ( ( 6 + 8 ) , ( 4 / 2 ) , MIN ( 8 , 2 , 1 , 0 , 3 ) ) * 2 * 6 / N ( 3 ) .
```

### Output:

```
100  1  34  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6
MAX3 2 34 1 100
MIN4 77 35 36 66 80 34 100
MIN6 60 50 35 80 34 100
34

2  100  1  6  5  *  2  +  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6  3  *  +
* 5 6 1 100 2
+ 2 30 1 100 2
MAX3 2 32 1 100 2
MIN4 77 35 36 66 80 32 100 2
MIN6 60 50 35 80 32 100 2
* 3 32 2
+ 96 2
98

400  N  11  3  2  *  -  2  /  +  200  N  N  +
N 400
* 2 3 11 -400
- 6 11 -400
/ 2 5 -400
+ 2 -400
N 200 -398
N -200 -398
+ 200 -398
-198

6  8  +  4  2  /  8  2  1  0  3  MIN5  IF  2  *  6  *  3  N  /  
+ 8 6
/ 2 4 14
MIN5 3 0 1 2 8 2 14
IF 0 2 14
* 2 2
* 6 4
N 3 24
/ -3 24
```

## How to Run

To run the project, compile the C++ files and execute the binary. Input expressions in the format described above and observe the results.
