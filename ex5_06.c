/*
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with 
 * pointers instead of array indexing. Good possibilities include getline (Chapters 1 and 4), 
 * atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), 
 * and strindex and getop (Chapter 4).
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE         100

/* getline: reads one line and returns its length. */
int getline(char *s, int lim)
{
	int c;
	char *ss = s; /* s will hold its initial position as ss marches. */
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*ss++ = c;
	if (c == '\n')
		*ss++ = c;
	*ss = '\0';
	return ss - s;
}

/* atoi: returns the first integer found in s. */
int atoi(char *s)
{
	int n = 0, sign;
	while (isspace(*s))
		s++;
	sign = *s == '-' ? -1 : 1;
	if (*s == '+' || *s == '-')
		*s++;
	while (isdigit(*s))
		n = 10 * n + *s++ - '0';
	return n*sign;
}

/* itoa: converts an int number to its character representation. */
void itoa(int n, char *s)
{
	static int i = 0;
	if (n / 10)
		itoa(n / 10, s);
	else if (n < 0)
		*(s + i++) = '-';
	*(s + i++) = abs(n % 10) + '0';
	*(s + i) = '\0';
}

/* reverse: */
void reverse(char *s)
{
	int temp;
	char *ss = s;
	while (*++s);
	if (*--s == '\n')
		*s-- = '\0';
	while (s > ss)
	{
		temp = *ss;
		*ss++ = *s;
		*s-- = temp;
	}
}

/* strindex: returns index of t in s, -1 if none */
int strindex(char *s, char *t)
{
	char *start = s;
	while (*s)
	{
		char *ss = s;
		char *tt = t;
		while (*tt && *ss++ == *tt++);
		if (*tt == '\0')
			return (ss - start) - (tt - t);
		s++;
	}
	return -1;
}

int getch();
void ungetch(int);
#define NUMBER '0'
/* getop: get next character or numeric operand */
int getop(char *s)
{
	int c;
	while ((*s = c = getch()) == ' ' || c == '\t');
	*++s = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	//i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(*s++ = c = getch()))
			;
	if (c == '.') /* collect fraction part */
		while (isdigit(*s++ = c = getch()))
			;
	*s = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
/* getop: */

void test_getline()
{
	char s[MAXLINE];
	int len = getline(s, MAXLINE);
	printf("%s ,%d chars\n", s, len);
}

void test_atoi()
{
	char s[MAXLINE];
	getline(s, MAXLINE);
	printf("%d\n", atoi(s));
}

void test_itoa()
{
	int n = -1234;
	char s[MAXLINE];
	itoa(n, s);
	printf("%s\n", s);
}

void test_reverse()
{
	char s[MAXLINE] = "Sami Abdelgadir\n";
	printf("%s\n", s);
	reverse(s);
	printf("%s\n", s);
	reverse(s);
	printf("%s\n", s);
}

void test_strindex()
{
	char t[10] = "sami";
	char s[MAXLINE] = "hey Samica, samir, Samica"; /* s in samir index is 12. */
	printf("index of '%s' in '%s' is %d", t, s, strindex(s, t));
}

void test_getop()
{
	int type;
	char s[100];
	while ((type = getop(s)) != EOF) 
	{
		switch (type) 
		{
		case NUMBER:
			printf("%0.3f \n",atof(s));
			break;
		default:
			printf("not a number...\n");
			break;
		}
	}
}

void main()
{
	//test_getline();
	//test_atoi();
	//test_itoa();
	//test_reverse();
	//test_strindex();
	test_getop();
	getchar();
}