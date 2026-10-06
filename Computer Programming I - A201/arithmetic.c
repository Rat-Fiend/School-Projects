/*
 * arithmetic.c
 *
 *  Created on: Mar 5, 2021
 *      Author: Quinton Odenthal
 *      UA ID: 31182634
 */

/* Boilerplate code ########################################### */

#include <stdio.h>


int main(int argc, char **argv) {
  const int BUF_LEN = 4095;
  char num_str1[BUF_LEN];
  char num_str2[BUF_LEN];
  char num_str3[BUF_LEN + 1];
  char c;
  int i;
  int alldigits;
  int num_str1_len;
  int num_str2_len;
  int num_str3_len;
  int idx1, idx2, idx3;
  int l, r;
  int d1, d2, d3;
  int carry, sum;
  char t;

  /* Get the user to enter two strings */
  printf("Please enter a string made of decimal digits 0 through 9, finishing the entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    num_str1[i] = c;
  }
  num_str1[i] = '\0';

  printf("Please enter a string made of decimal digits 0 through 9, finishing the entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    num_str2[i] = c;
  }
  num_str2[i] = '\0';


  /* Determine if num_str1 and num_str2 are made of digits 0 through 9
     only.

     Set alldigits to 1 if num_str1 and num_str2 contain no other
     characters then the digits 0 through 9.

     Set alldigits to 0 if num_str1 or num_str2 contains characters
     which are no digits 0 through 9.

  */

  alldigits = 1;
  for (i=0; num_str1[i] != '\0'; ++i) {
	  if (! ((num_str1[i] >= '0') && (num_str1[i] <= '9'))) {
		  alldigits = 0;
		  break;
	  }
  }

  if (alldigits) {
	  for (i=0; num_str2[i] != '\0'; ++i) {
	  	  if (! ((num_str2[i] >= '0') && (num_str2[i] <= '9'))) {
	  		  alldigits = 0;
	  		  break;
	  	  }
	  }
  }

  /* Continue with real work only if the strings contain nothing but
     digits 0 through 9
  */
  if (alldigits && (num_str1[0] != '\0') && (num_str2[0] != '\0')) {
    /* Here, we know that num_str1 and num_str2 contain only digits 0 through 9.

       We are going to compute the sum of the numbers in num_str1 and num_str2
       and put that sum into num_str3.

       CAUTION: We cannot convert num_str1 and num_str2 into integers,
       add them and convert back from the sum integer to a decimal
       string. C unsigned ints hold numbers from 0 to 2^32 - 1, but
       our num_str1 and num_str2 can be way larger than that!

       We need to do the addition digit per digit, as we learned it in
       school:

          1   5   9   4   8
       +      1   6   6   4

       -------1---1---1----
          1   7   6   1   2

       This means:

       (i)    We start by computing the length of the strings, which are
              guaranteed not to be empty.

       (ii)   We start at the right-most digit for both strings. We need
              to be careful, as the index of the right-most digit is
              different from one string to the other. We use idx1 and
              idx2 for these two different indices. We can initialize
              idx3 to 0; this index will give us the position in
              num_str3, where we will put the digit we compute for
              this place. We also initialize the carry variable to 0.

       (iii)       In each step, we add the two digits (which are still
                   ASCII, so we need to convert them first) and the
                   carry (which is an int). The sum of the two digits
                   0-9 will make at most 9 + 9 = 18, the carry will be
                   either 0 or 1. This means we will get a number from
                   0 to 19, which can be stored the int variable
                   sum. We cut this number into a ones digit and a
                   tens digit. The ones digit is our digit d3 for the
                   sum of num_str1 and num_str2 in that place. The
                   digit d3 goes into num_str3 (Caution: we need to
                   convert from that int to a char along that route).
                   The tens digit is our new carry for the next step.

       (iv)   We keep on going until both strings have hit their left
              end.  Once we get to the point where one of the strings
              has hit its left end but not the other, we no longer read
              beyond the left end of the string that is over, but we
              substitute '0' as a digit in that position in this
              string.

       (v)    After that loop, we may have a carry that comes out. If it
              is 1, we fill that into num_str3 as a last digit. In any case,
	      we set the '\0' terminator of num_str3.

       (vi)   The sum in num_str3 came out mirrored. We mirror that string.

       (vii)  We display the sum.


       PLAY WITH EXAMPLES BEFORE YOU START CODING!

       The strings may have different length!

       MAKE SURE YOU NEVER ACCESS ANY CHARACTER OUTSIDE THE ALLOWABLE RANGE
       FOR EACH OF THE 3 STRINGS. DOUBLE-CHECK ON THAT! TRIPLE-CHECK NOW!

       Again:

       '0' + 0 = '0'
       '0' + 1 = '1'
       ...
       '0' + 9 = '9'

       Similary

       '0' - '0' = 0
       '1' - '0' = 1
       ...
       '9' - '0' = 9

    */

/* End of boilerplate code ########################################### */


/* Written by Quinton Odenthal */

    for (i=0; num_str1[i] != '\0'; ++i);
    num_str1_len = i;

    for (i=0; num_str2[i] != '\0'; ++i);
    num_str2_len = i;

    idx1 = num_str1_len - 1;

	idx2 = num_str2_len - 1;

	idx3 = 0;

	carry = 0;


	for (i=0; ((i <= idx1) || (i <= idx2)); ++i) {
		if (i > idx1) {
			d1 = 0;
		} else {
			d1 = (num_str1[idx1 - i] - '0');
		}
		if (i > idx2) {
			d2 = 0;
		} else {
			d2 = (num_str2[idx2 - i] - '0');
		}

		sum = carry + d1 + d2;

		carry = sum / 10;

		d3 = sum % 10;

		num_str3[idx3 + i] = (d3 + '0');
	}

	if (carry == 1) {
		num_str3[idx3 + i] = (carry + '0');
		num_str3[idx3 + i + 1] = '\0';
	} else {
		num_str3[idx3 + i] = '\0';
	}

	for (i=0; num_str3[i] != '\0'; ++i);
	num_str3_len = i;
	idx3 = num_str3_len - 1;

	l = 0;
	r = idx3;

	while (l < r) {
		t = num_str3[r];
		num_str3[r] = num_str3[l];
		num_str3[l] = t;
		++l;
		--r;
	}

    printf("%s + %s = %s\n", num_str1, num_str2, num_str3);
  } else {
    printf("One of the strings you entered, \"%s\" or \"%s\", contains a character that is not a digit 0 through 9 or one of the strings is empty.\n",
	   num_str1, num_str2);
  }

  return 0;
}
