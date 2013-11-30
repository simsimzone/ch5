
/*
 * Exercise 5-2. Write getfloat, the floating-point analog of getint. 
 * What type does getfloat return as its function value?
 */

/*
 * return type is int, as it is a flag (-1, 0, >0)
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

/* getfloat: get next float from input into *pn */
int getfloat(float *pn)
{
	int c, sign, c2, power=1;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
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
	if (c == '.')
		for (power = 1; isdigit(c = getch()); *pn = 10 * *pn + (c - '0'))
			power *= 10;
	*pn = *pn * sign / power;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define SIZE 10
void main()
{
	int n, res;
	float array[SIZE];
	for (n = 0; n < SIZE && (res = getfloat(&array[n])) != EOF; n++)
	{
		if (res == 0)
		{
			getch();
			n--;
		}
		else
			printf("%0.3f\n", array[n]);
	}
}