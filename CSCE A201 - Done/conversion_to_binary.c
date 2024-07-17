/*
 * conversion_to_binary.c
 *
 *  Created on: Feb 26, 2021
 *      Author: Quinton Odenthal
 *      UA ID: 31182634
 */


#include <stdio.h>


int main(int argc, char **argv) {
  int n, k, i, p, j;
  int exp, temp;
  int strLen;
  char str[65];

  /* Make the user enter a non-negative integer */
  printf("Please enter a non-negative integer: ");
  scanf("%d", &n);
  while (n < 0) {
    printf("Sorry, your input is incorrect.\n");
    printf("Please enter a non-negative integer: ");
    scanf("%d", &n);
  }

  /* Convert the integer to reversed binary: e.g. 6 gets converted to 011 */
  if (n == 0) {
    /* Special case for n = 0 */
    str[0] = '0';
    str[1] = '\0';
  } else {
    /* Common case */
    k = n;
    i = 0;
    while (k > 0) {
    	exp = i + 1;
    	temp = 1;
    	while (exp > 0) {
     		temp = temp * 2;
     		--exp;
    	}

    	if (k % temp == (temp / 2)) {
      		k = k - (temp / 2);
       		str[i] = '1';
   		} else {
   			str[i] = '0';
    	}
    	++i;
    }
    str[i] = '\0';
  }

  /* The conversion made the string come out reversed, so reverse the string again.

     DO NOT USE A COPY OF THE STRING. DO NOT USE ANY LIBRARY FUNCTION
     (no strlen or other !)

  */

  strLen = 0;
  i = 0;
  while (!str[i] == '\0') {
	  strLen = strLen + 1;
	  ++i;
  }

  for (i=0; i < (strLen / 2); ++i) {
	  j = str[i];
	  p = str[(strLen - 1) - i];

	  str[i] = p;
	  str[(strLen - 1) - i] = j;
  }

  /* Display the number and the string */
  printf("The decimal number %d is %s in binary.\n", n, str);

  return 0;
}
