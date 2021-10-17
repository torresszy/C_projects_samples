/* Utilities used by the test code */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

#define ERR_MSG_LEN (1000)

void check_int(int actual, int expected, char *kind,
               char *test_desc, char *test_str);

void check_bool(bool actual, bool expected, char *kind,
                char *test_desc, char *test_str);

int add_int_array(int data[], int len);