// Author: Aakarsh MJ
// About:  Converts infix to Postfix
// Date:   23 January 2023
// All rights reserved to Aakarsh MJ



#include <stdio.h>
#include <string.h>

void infixtopostfix(char *string, int len);
int precedence(char );
char stack[10];
int top=-1;

int main( int argc, char *argv)
{
    char string[10];
    printf("Enter the infix expression:");
    scanf("%s", string);
    int len = strlen(string);

// Calling conversion function
    printf("Postfix expression: ");
    infixtopostfix( string, len );
    return 0 ;
}

void infixtopostfix( char *string, int len)
{
    int iterator = 0;
    char operand;
    while( iterator < len){
        operand = *(string+iterator);
        if ( (int)operand >= 48 && (int)operand <= 57){
            printf("%c",string[iterator]);
        } else{
            if( top < 0){
                stack[++top] = operand;
            }
            else{
                if (precedence(operand)== 4){
                    stack[++top] = operand;
                    iterator++;
                    do{
                        if( string[iterator] >= 48 && string[iterator] <= 57 ){
                            printf("%c", string[iterator]) ;
                        } else {
                            stack[++top] = string[iterator] ; 
                        }
                    }while( string[++iterator] != ')');

                    while( stack[top] != '('){
                        printf("%c", stack[--top]) ;
                    } 
                // To remove '(' from the stack
                    top--;
                } 
                
                // when incoming operator has lower precedence than that in stakc
                else if ( precedence(operand) < precedence((stack[top]))){
                    while(precedence(operand) < precedence((stack[top])) && top != -1){
                        printf("%c", stack[top--]);
                    }
                    stack[++top] = operand;
                }

                // when incoming operator has higher precedence than that in stakc
                else if ( precedence(operand) > precedence((stack[top]))){
                    stack[++top] = operand;
                }
                

                // when incoming operator has same precedence than that in stakc
                else {
                    printf("%c", stack[top--]);
                    stack[++top] = operand;
                }
            }

        }
        iterator++;
    }
    // print the remaining stack
    while( top != -1 ){
        printf("%c", stack[top--]);
    }
}


int precedence( char test )
{
    switch ((int)test){
        case '(':
        case ')':   return 4;
                    break;
        case '^':   return 3;
                    break;
        case '*':   
        case '/':   return 2;
                    break;
        case '-':
        case '+':   return 1;
                    break;

        default:    fprintf(stderr, "Unsupported operator encountered: '%c'\n", (int)test);
                    fprintf(stderr, "Use supported operators: '(', ')', '^', '*', '/', '-', '+' \n");
    }
    return (-1);
}