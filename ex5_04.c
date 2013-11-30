/*
 * Exercise 5-4. Write the function strend(s,t), 
 * which returns 1 if the string t occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>

/* strend: returns 1 if the string t occurs at the end of the string s, and zero otherwise. */
int strend(char *s, char *t)
{
	char *c = t;
	while (*s)
		if (*s++ != *c++)
			c = t;
	return !*c;
}

#define MAX_CHARS 100
void main()
{
	char t[MAX_CHARS] = "sami";
	char s1[MAX_CHARS] = "sami is samica";
	char s2[MAX_CHARS] = "samica is sami";
	int res = strend(s1, t);
	printf("\"%s\" %s at the end of \"%s\"\n", t, res?"occured":"not occured", s1);
	res = strend(s2, t);
	printf("\"%s\" %s at the end of \"%s\"", t, res ? "occured" : "not occured", s2);


	getchar();
}