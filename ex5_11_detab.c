/*
 * Exercise 5 - 11. Modify the program entab and detab(written as exercises in Chapter 1) 
 * to accept a list of tab stops as arguments.
 * Use the default tab settings if there are no arguments.
 */
#include <stdio.h>
#include <ctype.h>
#define TAB		5
#define OK		1
#define NOT_OK	0

int getint(char *str, int *res)
{
	if (!isdigit(*str))
		return NOT_OK;
	for (*res = 0; isdigit(*str); *res = 10 * *res + (*str++ - '0'))
		;
	if (*str)
		return NOT_OK;
	return OK;
}

main(int argc, char *argv [])
{
	int c, index = 0, i = 1, tab;
	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			putchar(c);
			index = 0;
		}
		else if (c == '\t')
		{
			if (i < argc)
				getint(argv[i++], &tab); /* use argument tabstop. */
			else
				tab = TAB; /* otherwise use our custom tabstop. */
			while (index++ < tab)
				putchar(' ');
			index = 0;
		}
		else
		{
			putchar(c);
			index++;
		}
	}
}