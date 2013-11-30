/*
 *Exercise 5-16. Add the -d (``directory order'') option,
 * which makes comparisons only on letters, numbers and blanks.
 * Make sure it works in conjunction with -f.
 */

#include <stdio.h>

#define MAXLINES 5000 /* max #lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr [], int nlines);
void writelines(char *lineptr [], int nlines);
void q_sort(void *lineptr [], int left, int right, int (*comp)(void*, void*));

void strcpy(char *, char *);

int numcmp(char*, char*);
int numcmprev(char *, char *);
int strcmp(char *, char *);
int strcmprev(char *, char *);
int strcmpfold(char *, char *);
int strcmpfoldrev(char*, char*);
int strcmpdirfold(char *, char *);
int strcmpdirrev(char *, char *);
int strcmpdirfoldrev(char *, char *);
int strcmpdir(char *, char *);

/* sort input lines */
main(int argc, char *argv [])
{
	int nlines;			/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */
	int reverse = 0;	/* 1 if in reverse order */
	int fold = 0;       /* 1 if no case sensitive */
	int dir = 0;        /* 1 to ignore chunk characters */

	while (--argc > 0 && *++argv)
	{
		if (!strcmp(*argv, "-n"))
			numeric = 1;
		else if (!strcmp(*argv, "-r"))
			reverse = 1;
		else if (!strcmp(*argv, "-f"))
			fold = 1;
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		int (*compfunc)(char*, char*) =
			numeric ?
				reverse ?
					numcmprev : numcmp
				: fold ?
					dir?
						reverse ?
							strcmpdirfoldrev: strcmpdirfold
						:reverse?
							   strcmpfoldrev : strcmpfold
					: dir ?
						reverse ?
							strcmpdirrev : strcmpdir
						: reverse ?
							strcmprev : strcmp;
		q_sort((void**) lineptr, 0, nlines - 1,
			(int (*)(void*, void*))(compfunc));
		writelines(lineptr, nlines);
		getchar();
		return 0;
	}
	else
	{
		printf("error: input too big to sort\n");
		getchar();
		return 1;
	}
}

#define MAXLEN 1000 /* max length of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
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
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
		return nlines;
}
/* writelines: write output lines */
void writelines(char *lineptr [], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}


/*-----------------------------------------------------------------------------*/
#include <ctype.h>
/* qsort: sort v[left]...v[right] into increasing order */
void q_sort(void *v [], int left, int right, int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v [], int, int);

	if (left >= right)					/* do nothing if array contains */
		return;							/* fewer than two elements */
	swap(v, left, (left + right) / 2);	/* move partition elem to v[0] */
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);				/* restore partition elem */
	q_sort(v, left, last - 1, comp);
	q_sort(v, last + 1, right, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v [], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/******************************************************************************/
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
/*******************************************************************************/

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

/*----------------------------------------------------------------*/

#include <stdlib.h>

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int numcmprev(char *s1, char *s2)
{
	return -1 * numcmp(s1, s2);
}

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *s, char *t)
{
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

/* strcpy: copy t to s; pointer version 3 */
void strcpy(char *s, char *t)
{
	while (*s++ = *t++)
		;
}

/* strlwrfold: same as strcmp, except it doesn't deal with case sensitivity */
int strcmpfold(char *s, char *t)
{
	for (; tolower(*s) == tolower(*t); s++, t++)
		if (*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}

int strcmprev(char *s, char *t)
{
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *t - *s;
}

int strcmpfoldrev(char*s, char* t)
{
	return -1 * strcmpfold(s, t);
}

/* compares only letters, numbers and blanks, and ignores bad characterts. */
int strcmpdir(char *s, char *t)
{
	while (!isdigit(*s) && !isalpha(*s) && !isspace(*s) && *s)	/* ignore chunk characters */
		++s;
	while (!isdigit(*t) && !isalpha(*t) && !isspace(*t) && *t)	/* ignore chunk characters */
		++s;
	for (; *s == *t;)
	{
		if (*s == '\0')
			return 0;
		s++; t++;
		while (!isdigit(*s) && !isalpha(*s) && !isspace(*s) && *s)	/* ignore chunk characters */
			++s;
		while (!isdigit(*t) && !isalpha(*t) && !isspace(*t) && *t)	/* ignore chunk characters */
			++t;
	}
	return *s - *t;
}

int strcmpdirfold(char *s, char *t)
{
	while (!isdigit(*s) && !isalpha(*s) && !isspace(*s) && *s)	/* ignore chunk characters */
		++s;
	while (!isdigit(*t) && !isalpha(*t) && !isspace(*t) && *t)	/* ignore chunk characters */
		++s;
	for (; tolower(*s) == tolower(*t);)
	{
		if (*s == '\0')
			return 0;
		s++; t++;
		while (!isdigit(*s) && !isalpha(*s) && !isspace(*s) && *s)	/* ignore chunk characters */
			++s;
		while (!isdigit(*t) && !isalpha(*t) && !isspace(*t) && *t)	/* ignore chunk characters */
			++t;
	}
	return tolower(*s) - tolower(*t);
}

int strcmpdirrev(char *s, char *t)
{
	return -1 * strcmpdir(s, t);
}

int strcmpdirfoldrev(char *s, char *t)
{
	return -1 * strcmpdirfold(s, t);
}

