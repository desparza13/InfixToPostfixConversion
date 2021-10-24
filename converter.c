/*
Omar Chavira Román
Daniela Esparza Espinosa
	Programación con memoria dinámica
*/
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include <string.h>
#define ISDIGIT (character>='0' &&  character<='9') 
#define ISMAYUS (character>='A' && character<='Z')
#define ISMINUS (character>='a' && character<= 'z')
#define ISNOTPARENTHESIS (character!='(' && character!= ')')

//FUNCTIONS
BOOL isOperand(char character);
BOOL isOpenParenthesis(char character);
void showPostfix();
void addRemainingOperators();
int getPrecedence(char operator);
void hasHigherPrecedence(char operator);

//GLOBAL VARIABLES
QUEUE postfix;
STACK operators;
TYPE aux;

int main()
{
	//CREAR DATA STRUCTURES
	postfix = queue_create();
	operators = stack_create();

	//PROBANDO PARA LAS 4 EXPRESIONES DE EJEMPLO
	char *expresion[4]= {"a+b*c/d-e", "(a+b)*(c-d)/e", "a*(b+c)/(d-e)", "a*b/c+d-e"};
	for (int i=0; i<4;i++)
	{
		printf("Expresion %d: %s\n", i, expresion[i]);
		for (int j=0; j<strlen(expresion[i]); j++)
		{
			if (isOperand(expresion[i][j]))
			{
				queue_offer(postfix,char_create(expresion[i][j]));
			}
			else
			{
				if (isOpenParenthesis(expresion[i][j]))
					stack_push(operators,char_create(expresion[i][j]));
				else if (stack_isempty(operators))
					stack_push(operators,char_create(expresion[i][j]));
				else
				{
					hasHigherPrecedence(expresion[i][j]);
				}
			}
		}
		addRemainingOperators();
		printf("Expresion posfija: ");
		showPostfix();
		printf("\n\n");
	}

}
/*
	División(/) y producto(*) 
		Tienen igual precedencia
		Ganan al resto de operadores
	Suma(+) y resta(-)
		Tienen igual precedencia
		Ganan al operador igualdad (=)
*/
void showPostfix()
{
	while(!queue_isempty(postfix))
	{
		aux=queue_poll(postfix);
		if (char_val(aux)!='(' && char_val(aux)!=')')
			printf("%c",char_val(aux));
	}
}
void addRemainingOperators()
{
	while(!stack_isempty(operators))
	{
		aux=stack_pop(operators);
		queue_offer(postfix,aux);		
	}
}
int getPrecedence(char operator)
{
	if (operator=='*' || operator== '/')
		return 2;
	else if (operator=='+' || operator=='-')
		return 1;
	return 0;
}
void hasHigherPrecedence(char operator)
{
	while(!stack_isempty(operators))
	{
		TYPE stackOperator = stack_top(operators);
		if (getPrecedence(operator)>getPrecedence(char_val(stackOperator)))
		{
			stack_push(operators,char_create(operator));
			return;
		}
		else
		{
			aux=stack_pop(operators);
			queue_offer(postfix,aux);
		}
	}
	stack_push(operators,char_create(operator));
}

BOOL isOperand(char character)
{
	if ((ISDIGIT || ISMAYUS || ISMINUS ) && ISNOTPARENTHESIS)
		return 1;
	else
		return 0;
}

BOOL isOpenParenthesis(char character)
{
	if (character=='(')
		return 1;
	else
		return 0;
}