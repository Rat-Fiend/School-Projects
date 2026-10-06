/*
 * substring.c
 *
 *  Created on: Mar 5, 2021
 *      Author: Quinton Odenthal
 *      UA ID: 31182634
 */

/* Boilerplate code ########################################### */

#include <stdio.h>

int main(int argc, char **argv) {
  const int BUF_LEN = 128;
  char haystack[BUF_LEN];
  char needle[BUF_LEN];
  char c;
  int i, j, substring, found;
  int needle_len, haystack_len;

  /* Get the user to enter two strings */
  printf("Please enter a string, finishing the entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    needle[i] = c;
  }
  needle[i] = '\0';

  printf("Please enter another string, finishing the entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    haystack[i] = c;
  }
  haystack[i] = '\0';

  /* Print the string once */
  printf("The strings you entered are \"%s\" and \"%s\".\n", needle, haystack);

  /* Determine if needle is contained in the haystack

     Set the variable substring to 1 if the needle is in the haystack.

     Set the variable substring to 0 if the needle is not in the
     haystack.

     DO NOT DECLARE ANY OTHER VARIABLES; USE ONLY THE ONES ALREADY
     DECLARED.

     Examples:

     needle = "adam" is contained in haystack = "Madame Bovary"

     needle = "" is contained in haystack = "Hello World"

     needle = "or" is contained in haystack = "Hello World"

     needle = "orange" is not contained in haystack = "Goranje"

     needle = "banana" is contained in haystack = "banana"

     Needles longer than the haystack can never be contained in the
     haystack.

     CHECK, DOUBLE-CHECK, TIPLE-CHECK AND QUADRUPLE-CHECK THAT YOU
     NEVER ACCESS ANY CHARACTER OUT OF THE ALLOWABLE RANGE IN ANY OF
     THE TWO STRINGS!

     You will want to start by computing the lengths of the needle and
     of the haystack.

  */

/* End of boilerplate code ########################################### */

/* Written by Quinton Odenthal */

  for (i=0; needle[i] != '\0'; ++i);
  needle_len = i;

  for (i=0; haystack[i] != '\0'; ++i);
  haystack_len = i;

  found = 1;
  substring = 1;
  if (needle_len > haystack_len) {
	  substring = 0;
  }
  else if (needle_len == 0) {
	  substring = 1;
  }
  else {
	  found = 0;
	  for (i=0; i<haystack_len; ++i) {
		  if (haystack[i] == needle[0]) {
			  found = 1;
			  for (j=0; j<needle_len; ++j) {
				  if ((haystack[j + i] == '\0') || (needle[j] != haystack[j + i])){
					  found = 0;
					  break;
				  }
			  }
		  if (found) {
			  break;
		  }
		  }
	  }
  }

  if (!found) {
	  substring = 0;
  }



  /* Print the answer */
  if (substring) {
    printf("\"%s\" is contained as a substring in \"%s\".\n", needle, haystack);
  } else {
    printf("\"%s\" is not contained as a substring in \"%s\".\n", needle, haystack);
  }

  return 0;
}

