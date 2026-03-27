// calc_mac.c - A simple arithmetic calculator
// Standalone version that runs on macOS
// Supports: +, -, *, / between two integer operands
// Usage: ./calc_mac <num1> <operator> <num2>
// Example: ./calc_mac 10 + 5   => Result: 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parse a signed integer from a string
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
    return 0;
  }

  for(; s[i] != '\0'; i++){
    if(s[i] < '0' || s[i] > '9'){
      return 0;
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

  if(argc != 4){
    printf("Usage: calc_mac <num1> <operator> <num2>\n");
    printf("Operators: +  -  *  /\n");
    printf("Example:   calc_mac 10 + 5\n");
    exit(1);
  }

  a = parse_int(argv[1], &valid_a);
  if(!valid_a){
    printf("calc_mac: invalid number '%s'\n", argv[1]);
    exit(1);
  }

  if(argv[2][0] == '\0' || argv[2][1] != '\0'){
    printf("calc_mac: invalid operator '%s'\n", argv[2]);
    printf("Supported operators: +  -  *  /\n");
    exit(1);
  }
  op = argv[2][0];

  b = parse_int(argv[3], &valid_b);
  if(!valid_b){
    printf("calc_mac: invalid number '%s'\n", argv[3]);
    exit(1);
  }

  switch(op){
    case '+':
      result = a + b;
      printf("%d + %d = %d\n", a, b, result);
      break;

    case '-':
      result = a - b;
      printf("%d - %d = %d\n", a, b, result);
      break;

    case '*':
      result = a * b;
      printf("%d * %d = %d\n", a, b, result);
      break;

    case '/':
      if(b == 0){
        printf("calc_mac: error: division by zero\n");
        exit(1);
      }
      result = a / b;
      printf("%d / %d = %d\n", a, b, result);
      break;

    default:
      printf("calc_mac: unknown operator '%c'\n", op);
      printf("Supported operators: +  -  *  /\n");
      exit(1);
  }

  exit(0);
}
