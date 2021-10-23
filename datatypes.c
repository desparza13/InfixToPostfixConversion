/*
Daniela Esparza Espinosa
Implementación de las funciones para el manejo de tipos de datos
*/
#include "datatypes.h"

// Crear un int en memoria dinámica
TYPE int_create(int n)
{
	int *ptr=malloc(sizeof(int));
	*ptr = n;
	return(ptr);
}

//Crear un float en memoria dinámica
TYPE float_create(float n)
{
	float *ptr=malloc(sizeof(float));
	*ptr = n;
	return(ptr);
}

//Crear un double en memoria dinámica
TYPE double_create(double n)
{
	double *ptr=malloc(sizeof(double));
	*ptr = n;
	return(ptr);
}

//Crear un char en memoria dinámica
TYPE char_create(char c)
{
	int *ptr=malloc(sizeof(char));
	*ptr = c;
	return(ptr);
}

//Crear un string en memoria dinámica
TYPE string_create(char *s)
{
	int strsize=strlen(s);
	char *ptr=malloc(strsize);
	strcpy(ptr,s);
	return(ptr);
}

