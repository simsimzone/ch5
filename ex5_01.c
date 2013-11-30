
/*
 * Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid representation of zero. 
 * Fix it to push such a character back on the input.
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch()
{
	return bufp > 0 ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign, c2;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{
		c2 = getch();
		if (!isdigit(c2))
		{
			ungetch(c2);
			ungetch(c);
			return 0;
		}
		c = c2;
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}


#define SIZE 20
void main()
{
	//int pn = 0, flag;
	int n, array[SIZE], res;
	for (n = 0; n < SIZE && (res = getint(&array[n])) != EOF; n++)
	{
		if (res == 0)
		{
			getch();
			n--;
		}
		else
			printf("%d\n", array[n]);
	}
	getchar();
}