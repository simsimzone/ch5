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
	int c, spaces = 0, index = 0, i = 2, tab = TAB;
	if (argc > 1 && !getint(argv[1], &tab))
		tab = TAB;
	while ((c = getchar()) != EOF)//read line
	{
		if (c == ' ')
			spaces++;
		else
		{
			if (spaces > 0)
				while (spaces--)
					putchar(' ');
			putchar(c);
			spaces = 0;
		}
		if (++index % tab == 0 || c == '\n')
		{
			if (spaces > 1)
				putchar('\t');
			else if (spaces == 1)
				putchar(' ');
			spaces = 0;
			index = 0;
			if (c == '\n')
				i = 1;
			if (i < argc)
				getint(argv[i++], &tab); /* use argument tabstop. */
			else
				tab = TAB; /* otherwise use our custom tabstop. */
		}
	}
}