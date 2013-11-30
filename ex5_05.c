/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, 
 * which operate on at most the first n characters of their argument strings. 
 * For example, strncpy(s,t,n) copies at most n characters of t to s. 
 * Full descriptions are in Appendix B.
*/

#include <stdio.h>

/* strncpy: copies at most n characters of t to s. */
void strncpy(char *s, char *t, int n)
{
	while (n-- && (*s++ = *t++));
	if (*s)
		*s = '\0';
}

/* strncat: concatenates at most n characters of t to the end of s.*/
void strncat(char *s, char *t, int n)
{
	while (*++s);
	while (n-- && (*s++ = *t++));
	if (*s)
		*s = '\0';
}

/* strncmp: compares most n characters of t to s.*/
int strncmp(char *s, char *t, int n)
{
	while (n-- && (*s++ == *t++));
	return n > 0 ? *--s - *--t : 0;
}

#define MAX_CHARS 100
void main()
{
	char t[MAX_CHARS] = "sami abdelgadir";
	char s [MAX_CHARS];
	int n = 30;
	strncpy(s, t, n);
	printf("copy maximum of %2d characters: %s\n",n, s);
	strncpy(s, t, n = 5);
	printf("copy maximum of %2d characters: %s\n", n, s);

	strncat(s, t, n = 4);
	printf("concat s,t,n=%2d => %s\n", n, s);

	strncpy(s, t, n = 5);
	strncat(s, t, n = 80);
	printf("concat s,t,n=%2d => %s\n", n, s);

	strncpy(s, t, n = 5);
	n = 80;
	printf("comparing %s to %s taking %2d chars resulting: %d\n", s, t, n, strncmp(s, t, n));
	n = 5;
	printf("comparing %s to %s taking %2d chars resulting: %d\n", s, t, n, strncmp(s, t, n));
	getchar();
}