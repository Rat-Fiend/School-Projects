/*
 * comparing_strings.c
 *
 *  Created on: Feb 26, 2021
 *      Author: Quinton Odenthal
 *      UA ID: 31182634
 */

/* Boilerplate code ########################################### */

#include <stdio.h>

int main(int argc, char **argv) {
  const int BUF_LEN = 128;
  char str1[BUF_LEN];
  char str2[BUF_LEN];
  int str1Length;
  int str2Length;
  int i;
  char c;
  int comp;

  /* Get the user to enter two strings */
  printf("Please enter two strings, finishing each entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    str1[i] = c;
  }
  str1[i] = '\0';

  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    str2[i] = c;
  }
  str2[i] = '\0';

  /* Compare the two strings:

     If str1 figures in a dictionary before str2, set comp to -1.
     If str1 is equal to str2, set comp to 0.
     If str1 figures in a dictionary after str2, set comp to 1.

     You must not use any function out of string.h. So no strcmp, no strlen!

     Caution: the strings may have different length! If two strings
     differ in length but are the same for the length of the shorter one,
     the shorter one sorts in a dictionary before the longer one. Check
     your code e.g. with "Hello" and "Hell" for this case.

     Try with:

     * "a" and "b"
     * "a" and "a"
     * "b" and "a"
     * "Hello" and "Hallo"
     * "Hello" and "Hello"
     * "Hell" and "Hello"
     * "" and ""
     * "" and "Hello"

     etc.

     Start by figuring out a loop (while loop) that
     goes over each character in both strings and stops
     whenever the shorter of the string is finished.

     String ends are marked in C with the ASCII null character '\0'.

     Finally, figure out the problem of two strings of the different length
     which are identical in the length of the shorter of them, such as
     "Hell" and "Hello". This will give you a if-else-if sequence *after* your
     loop.

     You are allowed to use break statements.

  */

/* End of boilerplate code ########################################### */

/* Written by Quinton Odenthal */

  i = 0;
  comp = 0;
  while (!(str1[i] == '\0') && !(str2[i] == '\0')) {
	  if (str1[i] < str2[i]) {
		  comp = -1;
		  break;
	  }
	  else if (str2[i] < str1[i]) {
		  comp = 1;
		  break;
	  }
	  ++i;
  }


  if (comp == 0) {
	  i = 0;
	  str1Length = 0;
	  while (!(str1[i] == '\0')) {
		  str1Length = str1Length + 1;
		  ++i;
	  }
	  i = 0;
	  str2Length = 0;
	  while (!(str2[i] == '\0')) {
		  str2Length = str2Length + 1;
		  ++i;
	  }

	  if (str1Length < str2Length) {
		  comp = -1;
	  }
	  else if (str2Length < str1Length) {
		  comp = 1;
	  }
	  else {
		  comp = 0;
	  }
  }


  /* Display the answer */
  if (comp < 0) {
    printf("The string \"%s\" figures in a dictionary before the string \"%s\".\n", str1, str2);
  } else {
    if (comp > 0) {
      printf("The string \"%s\" figures in a dictionary after the string \"%s\".\n", str1, str2);
    } else {
      printf("The two strings \"%s\" and \"%s\" are equal.\n", str1, str2);
    }
  }

  return 0;
}

