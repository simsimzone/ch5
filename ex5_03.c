/*
 * Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2: 
 * strcat(s,t) copies the string t to the end of s.
 */

#include <stdio.h>

/* strcat: copies the string t to the end of s. */
void strcat(char *s, char *t)
{
	while (*s)
		s++;
	while (*s++ = *t++);
}

#define MAX_CHARS 100
void main()
{
	char t[MAX_CHARS] = "Abdelgadir";
	char s [MAX_CHARS] = "";
	strcat(s, t);
	printf("%s", s);

	getchar();
}
