/* day_of_week.c

   Name: Quinton Odenthal
   Date: 4/9/21
*/

#include <stdio.h>

int is_leap_year(int year) {
	if (year % 400 == 0) return 1;
	if ((year % 4 == 0) && (year % 100 != 0)) return 1;
	return 0;
}

int get_century_value (int year) {
	int c, r;
	c = year / 100;
	r = c % 4;
	return (3 - r) * 2;
}

int get_year_value (int year) {
	int y;
	y = year % 100;
	y = y + (y / 4);
	return y;
}

int get_month_value (int month, int year) {
	if (is_leap_year(year) == 1) {
		switch (month) {
		case 1:
			return 6;
		case 2:
			return 2;
		}
	}
	switch (month) {
	case 1:
		return 0;
	case 2:
		return 3;
	case 3:
		return 3;
	case 4:
		return 6;
	case 5:
		return 1;
	case 6:
		return 4;
	case 7:
		return 6;
	case 8:
		return 2;
	case 9:
		return 5;
	case 10:
		return 0;
	case 11:
		return 3;
	case 12:
		return 5;
	}
}

int day_of_week_number (int day, int month, int year) {
	int u, v, w;
	u = get_century_value(year);
	v = get_year_value(year);
	w = get_month_value(month, year);
	return (u + v + w + day) % 7;
}

char *day_of_week (int day, int month, int year) {
	switch (day_of_week_number(day, month, year)) {
	case 0:
		return "Sunday";
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednesday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	case 6:
		return "Saturday";
	}
}

int main(int argc, char **argv) {
	int userDay, userMonth, userYear;
	printf("Please enter the day (as an integer): ");
	scanf("%d", &userDay);

	printf("Please enter the month (as an integer): ");
	scanf("%d", &userMonth);

	printf("Please enter the year (as a 4 digit integer): ");
	scanf("%d", &userYear);

	printf("%d-%d-%d is a %s.\n", userDay, userMonth, userYear, day_of_week(userDay, userMonth, userYear));

  return 0;
}
