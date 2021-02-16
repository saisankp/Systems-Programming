#include "postfix.h"
#include <stdio.h>
#include <math.h>

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  // Write your code here
  struct double_stack *stack = double_stack_new(nargs); // make a new stack using the stack.c file we made last week!
  for(int i = 0; i < nargs; i++) {
       if( ((args[i][0] >= '0' && args[i][0] <= '9' ) || (args[i][1] >= '0' && args[i][1] <= '9')) ) { //if it is a number
	  double operand =  atof(args[i]);
	  printf("operand: %f", operand);
	  double_stack_push(stack, operand);
       }
       else if(strlen(args[i]) == 1) { //is 1 because it will be [+][\0]
	switch(args[i][0]) {
	double op2, op1, result;
	case '+':
	 op2 = double_stack_pop(stack);
	 op1 = double_stack_pop(stack);
	 result = op1 + op2;
	 double_stack_push(stack, result);
	 break ;

	case '-':
	 op2 = double_stack_pop(stack);
	 op1 = double_stack_pop(stack);
	 result = op1 - op2;
	 double_stack_push(stack, result);
	 break ;

	case 'X':
	 op2 = double_stack_pop(stack);
	 op1 = double_stack_pop(stack);
	 result = op1 * op2;
	 double_stack_push(stack, result);
	 break;

	case '/':
	op2 = double_stack_pop(stack);
	op1 = double_stack_pop(stack);
	result = op1/op2;
	double_stack_push(stack, result);
	break;

	case '^':
	op2 = double_stack_pop(stack);
	op1 = double_stack_pop(stack);
	result = pow(op1, op2);
	double_stack_push(stack, result);
	break;

	default :
	break;
	}
      }
  }
  double answer = double_stack_pop(stack);
  return answer;
}
