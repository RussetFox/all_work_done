#include <stdio.h>

void inicjuj (int *top)//Inicjacja wskaznika na stos (1 element)
{
	*top= 0;
}

void push (int *s, int *top, int element)//Wrzucenie elementu na stos, jesli stos nie jest pełny
{
	s[(*top)++]= element;
}

int pop (int *s, int *top)//Usuniecie elementu, o ile stos nie jest pusty
{
	return s[--(*top)];
}

int pelny (int *top, const int rozmiar)//Zwraca wartosc 1 jesli stos pelny, 0 jesli pusty
{
	return *top == rozmiar ? 1 : 0;
}

int empty (int *top)//Jesli stos pusty, zwraca wartosc 0
{
	return *top == 0 ? 1 : 0;
}


void print (int *s, int *top)//Wyswietla zawartosc stosu
{
	printf ("Stos: ");
	int i;
	for (i=0; i < *top; i++)
	{
		printf ("%i ", s[i]);
	}
	printf ("\n");
}
