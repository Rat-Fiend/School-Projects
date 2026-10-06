/*
 * conversion_from_binary.c
 *
 *  Created on: Feb 26, 2021
 *      Author: Quinton Odenthal
 *      UA ID: 31182634
 */


#include <stdio.h>


int main(int argc, char **argv) {
  const int BUF_LEN = 128;
  char str[BUF_LEN];
  int i;
  int strLen, exp;
  char c;
  int is_binary;
  int n, temp;

  /* Get the user to enter a string */
  printf("Please enter a string made of 0s and 1s, finishing the entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    str[i] = c;
  }
  str[i] = '\0';


  /* Check if the user string contains nothing but 0s and 1s */
  is_binary = 1;

  i = 0;
  while (!(str[i] == '\0')) {
	  if (!(str[i] == '0') && !(str[i] == '1')) {
		  is_binary = 0;
		  break;
	  }
	  ++i;
  }


  /* Proceed only of the string contains only 0s and 1s */
  if (is_binary == 1) {
    /* Convert the string of 0s and 1s to an integer number n */
	strLen = 0;
	i = 0;
	while (! str[i] == '\0') {
		strLen = strLen + 1;
		++i;
	}

    n = 0;
    for (i=0; i < strLen; ++i) {
    	exp = (strLen - 1) - i;
    	if (str[i] == '1') {
    		temp = 1;
    		while (exp > 0) {
    			temp = temp * 2;
   	    		--exp;
   	    	}
    	} else {
    		temp = 0;
    	}
    	n = n + temp;
    }

    printf("The binary number %s is %d in decimal.\n", str, n);
  } else {
    printf("The string you entered, \"%s\", contains characters other than 0 and 1.\n", str);
  }

  return 0;
}
