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
void tryExampleExpressions(); //Prueba las 6 expresiones de ejemplo en la descripcion del examen
void convertToPostfix(char infix[100]); //Convierte e imprime la versión posfija de una expresión infija
BOOL isOperand(char character); //Revisa si un carácter es un operando (letras o digitos)
BOOL isOpenParenthesis(char character); //Revisa si un carácter es (
void showPostfix(); //Imprime la versión posfija
void addRemainingOperators(); //Añade todos los operadores que quedan en el stack de operadores vaciandolo
int getPrecedence(char operator); //Regresa el grado de precedencia del operador entre mayor sea, mayor preferencia tiene (2 para multiplicacion y division y 1 para suma y resta)
void hasHigherPrecedence(char operator); //Logica del programa, compara la precedencia de un operador con el que se encuentre arriba de la pila y actúa según corresponda

//GLOBAL VARIABLES
QUEUE postfix; //cola donde se va escribiendo el resultado (expresión posfija)
STACK operators; //pila donde se guardan los operadores para su procesamiento
TYPE aux; //variable tipo para traducción de tipos de datos con la pila y la cola
char infix[100]; //string donde se guarda la expresión infija a convertir

int main()
{
	//CREAR DATA STRUCTURES
	postfix = queue_create();
	operators = stack_create();

	//MENU
	int opcionMenu;
	printf("Seleccione una opcion\n1.Ingresar mi propia expresion\n2.Probar expresiones de ejemplo\n3.SALIR\n");
	scanf("%d",&opcionMenu);
	while(opcionMenu!=3) //Si no se escoge salir
	{
		switch (opcionMenu)
		{
			case 1: //Expresión infija propia
				printf("-----------------------------------------------------------------------------\n");
				printf("Expresión infija: ");
				scanf("%s",infix);
				convertToPostfix(infix);
				break;
			case 2: //Mostrar ejemplos
				printf("-----------------------------------------------------------------------------\n");
				printf("Mostrando ejemplos:\n");
				tryExampleExpressions();
				break;
			default:
				printf("Opción no disponible\n");
				break;
		}
		printf("-----------------------------------------------------------------------------\n");
		printf("Selección menú: ");
		scanf("%d",&opcionMenu);
	}
	printf("SALIENDO...\n");
}


void convertToPostfix(char infix[100])
{
	for(int i=0; i<strlen(infix); i++) //Por cada carácter de la expresión infija
	{
		if (isOperand(infix[i])) //Si es un operando
			queue_offer(postfix,char_create(infix[i])); //Se añade a la expresión posfija directamente
		else if (isOpenParenthesis(infix[i]) || stack_isempty(operators)) //Si abre parentesis o no tenia ningun operador guardado
			stack_push(operators,char_create(infix[i])); //Se añade al stack para comparar con siguientes operadores
		else 
			hasHigherPrecedence(infix[i]); //Reviso contra los operadores guardados y opero según el caso
	}
	addRemainingOperators(); //Vacio lo que quedo en el stack a mi expresión posfija
	printf("Expresion posfija: ");
	showPostfix(); //Imprimir
	printf("\n\n");	
}

void tryExampleExpressions()
{
	char *expresion[6]= {"2+3*4","(2+3)*4","a+b*c/d-e", "(a+b)*(c-d)/e", "a*(b+c)/(d-e)", "a*b/c+d-e"}; //Banco de expresiones
	for (int i=0; i<6;i++) //Evaluar cada expresión del banco
	{
		printf("Expresion infija: %s\n", expresion[i]);
		convertToPostfix(expresion[i]);
	}
}

void showPostfix() 
{
	while(!queue_isempty(postfix)) //Imprimir todo lo que esté en la cola de la expresión posfija
	{
		aux=queue_poll(postfix);
		if (char_val(aux)!='(' && char_val(aux)!=')')
			printf("%c ",char_val(aux));
	}
}
void addRemainingOperators() 
{
	while(!stack_isempty(operators)) //Vaciar todo lo que esté en el stack de operadores hacia la cola de la expresión posfija
	{
		aux=stack_pop(operators);
		queue_offer(postfix,aux);		
	}
}

int getPrecedence(char operator)
{
	if (operator=='*' || operator== '/') //Si es multiplicacion o division tiene mayor precedencia
		return 2;
	else if (operator=='+' || operator=='-')//Sobre la suma y la resta
		return 1;
	return 0;
}
void hasHigherPrecedence(char operator) //Comparar precedencia de un operador con el top del stack de operadores
{
	while(!stack_isempty(operators)) //Hasta que no queden operadores con los que comparar
	{
		TYPE stackOperator = stack_top(operators);
		if (getPrecedence(operator)>getPrecedence(char_val(stackOperator))) //Si el nuevo operador tiene mayor precedencia que el de hasta arriba del stack
		{
			stack_push(operators,char_create(operator)); //Lo añado al stack
			return;
		}
		else //Si debería ir antes
		{
			aux=stack_pop(operators); //Lo quito del stack
			queue_offer(postfix,aux); //Y lo añado a la cola de la expresion posfija
		}
	}
	stack_push(operators,char_create(operator)); //Añado el nuevo operador al stack para compararlo con los nuevos operadores de la derecha de la expresion
}

BOOL isOperand(char character) //Reviso si es un operando
{
	if ((ISDIGIT || ISMAYUS || ISMINUS ) && ISNOTPARENTHESIS)
		return 1;
	else
		return 0;
}

BOOL isOpenParenthesis(char character) //Reviso si es apertura de parentesis
{
	if (character=='(')
		return 1;
	else
		return 0;
}