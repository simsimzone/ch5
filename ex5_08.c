
/*
 * Exercise 5-8. There is no error checking in day_of_year or month_day. 
 * Remedy this defect.
 */

#include <stdio.h>

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

void main()
{
	int year = 1988, month = 3, day = 1, yearday;

	yearday = day_of_year(year, month, day);
	printf("yearday=%d\n", yearday);

	yearday = -1;
	month_day(year, yearday, &month, &day);
	if (day < 1)
		printf("error yearday overflow\n");
	else
		printf("for yearday: %d, month = %d, day = %d\n", yearday, month, day);

	getchar();
}

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	/**********************************/
	if (month < 1 || month > 12)
	{
		printf("error, month overflow.\n");
		return -1;
	}
	if (day < 1 || day > daytab[leap][month])
	{
		printf("error, day overflow.\n");
		return -1;
	}
	/**********************************/
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; i < 13 && yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	if (i == 13)
	{
		*pday = -1;
		return;
	}
	*pmonth = i;
	*pday = yearday;
}