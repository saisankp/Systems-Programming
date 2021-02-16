
#include "infix.h"

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {

    //Step 1: convert from Infix to postfix!
    char** postfix = malloc(sizeof(char*) * nargs); //allocate some memory for the postfix version the input.
    postfix = infixToPostfix(args, nargs); //convert the given infix to postfix using our method infixToPostfix.

    //Step 2: calculate the nterms for postfix!
    //The nterms for evaluate_postfix_expression will be less than evaluate_infix_expression, because we won't include the brackets.
    //Hence, we remove the brackets from the number of terms before calling evaluate_postfix_expression.
    int numberOfBrackets = 0;
    for (int i = 0; i < nargs; i ++) {
        if(is_left_bracket(args[i]) || is_right_bracket(args[i])) {
            numberOfBrackets++;
        }
    }

    //Step 3: calculate the postfix expression with the new value of nargs (i.e. nargs - numberOfBrackets).
    double answer = evaluate_postfix_expression(postfix, (nargs-numberOfBrackets));
    return answer;
}

//Note: All new methods below have been adequately added to the header file infix.h.

//this method converts infix into postfix!
char ** infixToPostfix(char ** infix, int length) {
    char ** postfix = malloc(sizeof(char *) * length);
    int postfix_length = 0;
    struct double_stack* stack = double_stack_new(length);

    for (int i = 0; i < length; i ++) {  //loop through all elements in infix and do different things based on what it is!
        if(is_operand(infix[i])) {
            //Just add to the output! (postfix).
            postfix[postfix_length] = infix[i];
            postfix_length++;
        }
        else if (is_left_bracket(infix[i])) {
            //Just push the index of the bracket onto the stack!
            double_stack_push(stack, i);
        }

        else if (is_operator(infix[i])) {
            //if there is an operator of greater than or equal precedence on the stack, keep popping operators off the stack onto the output (postfix)/
            //if not / once finished, push the index of the operator onto the stack!
            while(operator_of_ge_precedence(stack, infix[i], infix)) {
                int op = double_stack_pop(stack);
                postfix[postfix_length] = infix[op];
                postfix_length++;
            }
            double_stack_push(stack, i);
        }

        else if (is_right_bracket(infix[i])) {
            //The right bracket algorithm is tricky, but boiled down we do two things.
            // 1. while the top of the stack doesn't have a left bracket, pop them off and put them to the output (postfix).
            // 2. then pop off the remaining left bracket that should remain!
            int op;
            while(left_bracket_on_stack(stack, infix) == false) {
                op = double_stack_pop(stack);
                postfix[postfix_length] = infix[op];
                postfix_length++;
            }
            //pop the left bracket.
             op = double_stack_pop(stack);
        }
        else {
            //We should never reach this else statement!
        }
    }
    //after the for-loop iterating through our inputs, we may have some operators left on the stack.
    //to deal with this, we need to make sure that all operators are popped off the stack at the end, onto the output (postfix).
    int top = stack->items[stack->top-1]; //get the element on the top of the stack.
    int op2; //let's put any remaining operators into op2 one at a time after we pop them so they can go to the output(postfix).
    while(is_operator(infix[top])) {
        top = stack->items[stack->top-1]; //get the element on the top of the stack.
        op2 = double_stack_pop(stack);
        postfix[postfix_length] = infix[op2];
        postfix_length++;
    }
    //at this point, we can be confident that the stack doesn't have any operators remaining, and we are done converting from infix to postfix!
    return postfix;
}

//this method checks if a pointer to a char is an operand!
bool is_operand(char * valueBeingChecked) {
    bool isOperand = false;
    if((valueBeingChecked[0] >= '0' && valueBeingChecked[0] <= '9')) {
        isOperand = true;
    }
    return isOperand;
}

//this method checks if a pointer to a char is a left bracket!
bool is_left_bracket(char * valueBeingChecked) {
    bool isLeftBracket = false;
    if(valueBeingChecked[0] == '(') {
        isLeftBracket = true;
    }
    return isLeftBracket;
}

//this method checks if a pointer to a char is an operator!
bool is_operator(char * valueBeingChecked) {
    bool isOperator = false;
    if(valueBeingChecked[0] == '+' || valueBeingChecked[0] == '-' || valueBeingChecked[0] == '/' || valueBeingChecked[0] == 'X' || valueBeingChecked[0] == '^') { // Operators
        isOperator = true;
    }
    return isOperator;
}

//this method checks if there is an operator of greater than or equal precedence on the stack!
bool operator_of_ge_precedence (struct double_stack* input, char * valueBeingChecked, char ** infix) {
    bool operator_of_ge_precedence = false;
    int precedenceOfTop = 0;
    int precedenceOfValueBeingChecked = 0;

//get precedence of value at the top of the stack
    int top = input->items[input->top-1];
    if(is_left_bracket(infix[top])) {       //make sure that if a left bracket is at the top of the stack, just ignore it and return false.
        return false;
    }
    switch (infix[top][0]) {
        case 'X':
            precedenceOfTop = 2;
            break;

        case '-':
            precedenceOfTop = 1;
            break;

        case '+':
            precedenceOfTop = 1;
            break;

        case '^':
            precedenceOfTop = 3;
            break;

        case '/':
            precedenceOfTop = 2;
            break;

        default:
            break;
    }
    //get precedence of value being compared
    switch(valueBeingChecked[0]) {
        case 'X':
            precedenceOfValueBeingChecked = 2;
            break;

        case '-':
            precedenceOfValueBeingChecked = 1;
            break;

        case '+':
            precedenceOfValueBeingChecked = 1;
            break;

        case '^':
            precedenceOfValueBeingChecked = 3;
            break;

        case '/':
            precedenceOfValueBeingChecked = 2;
            break;

        default:
            break;
    }

    if(precedenceOfTop >= precedenceOfValueBeingChecked) {
        operator_of_ge_precedence = true;
    }

    return operator_of_ge_precedence;
}

//this method checks if a pointer to a char is a right bracket!
bool is_right_bracket(char * valueBeingChecked) {
    bool isRightBracket = false;
    if(valueBeingChecked[0] == ')') {
        isRightBracket = true;
    }

    return isRightBracket;
}

//this method checks if there is a left bracket on the top of the stack.
bool left_bracket_on_stack(struct double_stack * input, char ** infix) {
    bool leftBracketOnStack = false;
    //get value at top of stack
    int top = input->items[input->top-1];
    if( infix[top][0] == '(' )  {
        leftBracketOnStack = true;
    }

    return leftBracketOnStack;
}

