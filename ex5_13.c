/*
 * Exercise 5-13. Write the program tail, 
 * which prints the last n lines of its input. 
 * By default, n is set to 10, let us say, 
 * but it can be changed by an optional argument so that
 *            tail -n
 * prints the last n lines. 
 * The program should behave rationally no matter how unreasonable 
 * the input or the value of n. 
 * Write the program so it makes the best use of available storage; 
 * lines should be stored as in the sorting program of Section 5.6, 
 * not in a two-dimensional array of fixed size.
*/

#include <stdio.h>
#include <string.h>
#define MAXLINES	5000
#define OK			1
#define NOT_OK		0
#define N			10
int getint(char*, int*);

char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char * [], int);
void printlnlines(char * [], int, int);

main(int argc, char* argv[])
{
	int n = N;
	int nlines; /* number of input lines read */
	if (argc > 1 && (*++argv)[0] == '-')
		if (!getint(++argv[0], &n))
			n = N;
	n = n > 0 ? n : N;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		printlnlines(lineptr, nlines, n);
		getchar();
		return 0;
	}
	else {
		printf("error: input too big\n");
		getchar();
		return 1;
	}
}

/*-------------------------------------------------------------------------------*/

void printlnlines(char *lineptr [], int nlines, int n)
{
	int i;
	int start;
	if (nlines < n)
		start = 0;
	else
		start = nlines - n;
	for (i = start; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/*-------------------------------------------------------------------------------*/

#define MAXLEN 1000 /* max length of any input line */
int getline(char *, int);
char *alloc(int);

int readlines(char *lineptr [], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy_s(p, MAXLEN, line);
			lineptr[nlines++] = p;
		}
		return nlines;
}
/*-------------------------------------------------------------------------------*/

int getline(char s [], int lim)
{
	int c, i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/*-------------------------------------------------------------------------------*/

#define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */
char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		/* it fits */
		allocp += n;
		return allocp - n; /* old p */
	}
	else /* not enough room */
		return 0;
}
void afree(char *p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

/*-------------------------------------------------------------------------------*/
#include <ctype.h>
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