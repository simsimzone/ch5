/*
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 *           entab -m +n
 * to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 */
#include <stdio.h>
#include <ctype.h>
#define TAB		8
#define OK		1
#define NOT_OK	0

int getint(char *str, int *res)
{
	if (!str)
		return NOT_OK;
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
	int c, spaces = 0, index = 0, tab = TAB;
	int m, n, col = 0;
	if (argc > 1 && (*++argv)[0] == '-')
		if (!getint(++argv[0], &m))
			m = 0;
	if (argc > 2 && (*++argv)[0] == '-')
		if (!getint(++argv[0], &n))
			n = TAB;
	while ((c = getchar()) != EOF)
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
		col++;
		if (col > m)
			tab = n;
		if (++index % tab == 0 || c == '\n')
		{
			if (spaces > 1)
				putchar('\t');
			else if (spaces == 1)
				putchar(' ');
			spaces = 0;
			index = 0;
			if (c == '\n')
				col = 0;
		}
	}
}