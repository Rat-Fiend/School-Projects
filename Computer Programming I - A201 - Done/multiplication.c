/* Multiplication.c

   Written by  Quinton Odenthal

*/

#include <stdio.h>

int multiplication (int a, int b) {
	if (b == 0) return 0;
	if (b == 1) return a;
	if (b % 2 == 0) return multiplication(a + a, b / 2);
	return a + multiplication(a + a, (b - 1) / 2);
}

int main(int argc, char **argv) {
	int userNum1, userNum2;

	printf("Please enter two non-negative integers./n");

	printf("Integer #1: ");
	scanf("%d", &userNum1);

	printf("Integer #2: ");
	scanf("%d", &userNum2);

	printf("Your numbers traditionally multiplied is: %d.\n", userNum1 * userNum2);
	printf("Your numbers multiplied using the Russian Peasant Multiplication is: %d.\n", multiplication(userNum1, userNum2));

  return 0;
}
