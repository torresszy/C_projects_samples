#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

#include "util.h"

void check_int(int actual, int expected, char *kind,
               char *test_desc, char *test_str)
{
    char err_msg[ERR_MSG_LEN];
    snprintf(err_msg, ERR_MSG_LEN-1,
            ("Failed %s\n"
                  "  Actual %s: %d\n"
                  "  Expected %s: %d\n"
                  "Command to rerun this test: "
                  "bin/test_task_manager --filter %s\n"),
                 test_desc, kind, actual, kind, expected, test_str);
    cr_assert_eq(actual, expected, " \n%s", err_msg);
}

void check_bool(bool actual, bool expected, char *kind,
                char *test_desc, char *test_str)
{
    char err_msg[ERR_MSG_LEN];
    char *actual_str = actual ? "true" : "false";
    char *expected_str = expected ? "true" : "false";
    snprintf(err_msg, ERR_MSG_LEN-1,
            ("Failed %s\n"
                  "  Actual %s: %s\n"
                  "  Expected %s: %s\n"
                  "Command to rerun this test: "
                  "bin/test_task_manager --filter %s\n"),
                 test_desc, kind, actual_str, kind, expected_str, test_str);
    cr_assert_eq(actual, expected, " \n%s", err_msg);
}

int add_int_array(int data[], int len)
{
    int rv = 0;
    for (int i=0; i < len; i++) {
        rv += data[i];
    }
    return rv;
}