
#ifndef __INFIX_H__
#define __INFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "stack.h"
#include "postfix.h"

double evaluate_infix_expression(char ** expr, int nterms);
char ** infixToPostfix(char ** infix, int length);
bool is_operand(char * valueBeingChecked);
bool is_left_bracket(char * valueBeingChecked);
bool is_operator(char * valueBeingChecked);
bool operator_of_ge_precedence(struct double_stack* input, char * valueBeingChecked, char ** infix);
bool is_right_bracket(char * valueBeingChecked);
bool left_bracket_on_stack(struct double_stack * input, char ** infix);
#endif
