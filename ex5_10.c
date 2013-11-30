/*
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression 
 * from the command line, where each operator or operand is a separate argument. 
 * For example,
 * expr 2 3 4 + *
 * evaluates 2 * (3+4).
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define OK     1
#define NOT_OK 0

void push(double);
double pop(void);
int canpop();

int getfloat(char *str, double *res)
{
	int power = 1;
	if (!isdigit(*str) && *str != '.')
		return NOT_OK;
	for (*res = 0; isdigit(*str); *res = 10 * *res + (*str++ - '0'));
	if (*str == '.')
		for (power = 1; isdigit(*++str); *res = 10 * *res + (*str - '0'))
			power *= 10;
	else if (*str)
		return NOT_OK;
	*res = *res / power;
	return OK;
}

int isoperator(char *str)
{
	if (strlen(str) > 1)
		return NOT_OK;

	switch (*str)
	{
	case '+':case '-':case '*': case '/':
		return OK;
	default:
		return NOT_OK;
	}
}

double evaloperator(char* str, double v1, double v2)
{
	switch (*str)
	{
	case '+':
		return v1 + v2;
	case '-':
		return v1 - v2;
	case '*':
		return v1 * v2;
	case '/':
		return v1 / v2;
	default:
		return 0.0;
	}
}

main(int argc, char *argv []) /* expr 2 3 4 + *  */
{
	double num = 0;
	int err = 0;
	while (*++argv)
	{
		if (getfloat(*argv, &num))
			push(num);
		else if (isoperator(*argv))
		{
			double v1, v2;
			if (canpop())
				v1 = pop();
			else
			{
				printf("error: too many operators.\n");
				err = 1;
				break;
			}
			if (canpop())
				v2 = pop();
			else
			{
				printf("error: too many operators.\n");
				err = 1;
				break;
			}
			push(evaloperator(*argv, v1, v2));
		}
		else
		{
			printf("error: Unknown command.\n");
			err = 1;
			break;
		}
	}
	if (!err && canpop())
	{
		num = pop();
		if (canpop())
			printf("error: too many values.\n");
		else
			printf("%.3g", num);
	}

	getchar();
}


/*--------------------------------------STACK----------------------------------*/

#define MAXVAL 100

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error : stack empty\n");
		return 0.0;
	}
}

int canpop()
{
	return sp;
}

/*-----------------------------------------------------------------------------*/
