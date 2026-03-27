// calc.c - A simple arithmetic calculator for Xv6
// Supports: +, -, *, / between two integer operands
// Usage: calc <num1> <operator> <num2>
// Example: calc 10 + 5   => Result: 15
//          calc 20 / 4   => Result: 5

#include "types.h"
#include "stat.h"
#include "user.h"

// Parse a signed integer from a string.
// Handles optional leading '-' sign.
int
parse_int(char *s, int *valid)
{
  int result = 0;
  int sign = 1;
  int i = 0;

  *valid = 0;

  if(s[0] == '-'){
    sign = -1;
    i = 1;
  }

  if(s[i] == '\0'){
    return 0; // empty or just '-'
  }

  for(; s[i] != '\0'; i++){
    if(s[i] < '0' || s[i] > '9'){
      return 0; // non-digit character encountered
    }
    result = result * 10 + (s[i] - '0');
  }

  *valid = 1;
  return sign * result;
}

int
main(int argc, char *argv[])
{
  int a, b, result, valid_a, valid_b;
  char op;

  // Validate argument count
  if(argc != 4){
    printf(1, "Usage: calc <num1> <operator> <num2>\n");
    printf(1, "Operators: +  -  *  /\n");
    printf(1, "Example:   calc 10 + 5\n");
    exit();
  }

  // Parse first operand
  a = parse_int(argv[1], &valid_a);
  if(!valid_a){
    printf(1, "calc: invalid number '%s'\n", argv[1]);
    exit();
  }

  // Parse operator (must be exactly one character)
  if(argv[2][0] == '\0' || argv[2][1] != '\0'){
    printf(1, "calc: invalid operator '%s'\n", argv[2]);
    printf(1, "Supported operators: +  -  *  /\n");
    exit();
  }
  op = argv[2][0];

  // Parse second operand
  b = parse_int(argv[3], &valid_b);
  if(!valid_b){
    printf(1, "calc: invalid number '%s'\n", argv[3]);
    exit();
  }

  // Perform the requested operation
  switch(op){
    case '+':
      result = a + b;
      printf(1, "%d + %d = %d\n", a, b, result);
      break;

    case '-':
      result = a - b;
      printf(1, "%d - %d = %d\n", a, b, result);
      break;

    case '*':
      result = a * b;
      printf(1, "%d * %d = %d\n", a, b, result);
      break;

    case '/':
      if(b == 0){
        printf(1, "calc: error: division by zero\n");
        exit();
      }
      result = a / b;
      printf(1, "%d / %d = %d\n", a, b, result);
      break;

    default:
      printf(1, "calc: unknown operator '%c'\n", op);
      printf(1, "Supported operators: +  -  *  /\n");
      exit();
  }

  exit();
}