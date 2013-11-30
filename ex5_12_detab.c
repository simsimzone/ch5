/*
 * Exercise 5-12. Extend entab and detab to accept the shorthand 
 *           entab -m +n
 * to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 */
#include <stdio.h>
#include <ctype.h>
#define TAB		4
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
	int c, index = 0, tab = TAB;
	int m, n, col = 0;
	if (argc > 1 && (*++argv)[0] == '-')
		if (!getint(++argv[0], &m))
			m = 0;
	if (argc > 2 && (*++argv)[0] == '-')
		if (!getint(++argv[0], &n))
			n = TAB;
	while ((c = getchar()) != EOF)
	{
		col++;
		if (col > m)
			tab = n;
		if (c == '\n')
		{
			putchar(c);
			index = 0;
		}
		else if (c == '\t')
		{
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