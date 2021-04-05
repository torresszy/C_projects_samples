#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

#include "util.h"
#include "images.h"

#define EPSILON (0.000001)
#define ERR_MSG_LEN (1000)

/********** Task 1: Image interface **********/

/* helper_new_ppm: Do the work of one of testing new_ppm
 *
 * height: height of new image
 * width: width of new image
 * test_name: test name in error messages
 */
void helper_new_ppm(int height, int width, char *test_name)
{
    ppm_t *actual = new_ppm(height, width);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Parameters used in failed test: new_ppm(%d, %d)\n"
              "\n  The filter to run this specific test is: --filter %s"),
             height, width, test_name);

    cr_assert_eq(actual->height, height, " %s\n      Actual height: %d\n      Expected height: %d ", err_msg, actual->height, height);
    cr_assert_eq(actual->width, width, " %s\n      Actual width: %d\n      Expected width: %d ", err_msg, actual->width, width);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cr_assert_eq(actual->image[i][j].red, 0, " %s\n  Wrong value at pixel (%d, %d):\n        Actual red: %d\n        Expected red: 0", err_msg, i, j, actual->image[i][j].red);
            cr_assert_eq(actual->image[i][j].green, 0, " %s\n  Wrong value at pixel (%d, %d):\n        Actual green: %d\n        Expected green: 0", err_msg, i, j, actual->image[i][j].green);
            cr_assert_eq(actual->image[i][j].blue, 0, " %s\n  Wrong value at pixel (%d, %d):\n        Actual blue: %d\n        Expected blue: 0", err_msg, i, j, actual->image[i][j].blue);
        }
    }
    free_ppm(actual);
}

TestSuite(new_ppm, .timeout=60);

Test(new_ppm, testA) 
{
    helper_new_ppm(1, 1, "new_ppm/testA");
}

Test(new_ppm, testB) 
{
    helper_new_ppm(1, 4, "new_ppm/testB");
}

Test(new_ppm, testC) 
{
    helper_new_ppm(4, 1, "new_ppm/testC");
}

Test(new_ppm, testD) 
{
    helper_new_ppm(4, 4, "new_ppm/testD");
}

TestSuite(free_ppm, .timeout=60);

Test(free_ppm, testA) 
{
    ppm_t *input = read_ppm("tests/test-images/test1.ppm");
    free_ppm(input);
}

Test(free_ppm, testB) 
{
    ppm_t *input = read_ppm("tests/test-images/test2.ppm");
    free_ppm(input);
}

/********** Task 2: Create negative **********/

void helper_create_negative(char* input_file, char* expected_file, char *test_name)
{
    ppm_t *input = read_ppm(input_file);
    ppm_t *expected = read_ppm(expected_file);

    ppm_t *actual = create_negative(input);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  create_negative failed with PPM: %s\n"
              "\n  The filter to run this specific test is: --filter %s"), input_file, test_name);

    cr_assert_eq(actual->height, expected->height, " %s\n      Actual height: %d\n      Expected height: %d ", err_msg, actual->height, expected->height);
    cr_assert_eq(actual->width, expected->width, " %s\n      Actual width: %d\n      Expected width: %d ", err_msg, actual->width, expected->width);
    for(int i = 0; i < expected->height; i++){
        for(int j = 0; j < expected->width; j++){
            cr_assert_eq(actual->image[i][j].red, expected->image[i][j].red, " %s\n  Wrong value at pixel (%d, %d):\n        Actual red: %d\n        Expected red: %d", err_msg, i, j, actual->image[i][j].red, expected->image[i][j].red);
            cr_assert_eq(actual->image[i][j].green, expected->image[i][j].green, " %s\n  Wrong value at pixel (%d, %d):\n        Actual green: %d\n        Expected green: %d", err_msg, i, j, actual->image[i][j].green, expected->image[i][j].green);
            cr_assert_eq(actual->image[i][j].blue, expected->image[i][j].blue, " %s\n  Wrong value at pixel (%d, %d):\n        Actual blue: %d\n        Expected blue: %d", err_msg, i, j, actual->image[i][j].blue, expected->image[i][j].blue);
        }
    }
    free_ppm(input);
    free_ppm(expected);
    free_ppm(actual);
}

TestSuite(create_negative, .timeout=60);

Test(create_negative, testA) 
{
    helper_create_negative("tests/test-images/test1.ppm", "tests/test-images/negative1.ppm", "create_negative/testA");
}

Test(create_negative, testB) 
{
    helper_create_negative("tests/test-images/test2.ppm", "tests/test-images/negative2.ppm", "create_negative/testB");
}

/********** Task 3: Create greyscale **********/

void helper_create_greyscale(char* input_file, char* expected_file, char *test_name)
{
    ppm_t *input = read_ppm(input_file);
    ppm_t *expected = read_ppm(expected_file);

    ppm_t *actual = create_greyscale(input);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  create_greyscale failed with PPM: %s\n"
              "\n  The filter to run this specific test is: --filter %s"), input_file, test_name);

    cr_assert_eq(actual->height, expected->height, " %s\n      Actual height: %d\n      Expected height: %d ", err_msg, actual->height, expected->height);
    cr_assert_eq(actual->width, expected->width, " %s\n      Actual width: %d\n      Expected width: %d ", err_msg, actual->width, expected->width);
    for(int i = 0; i < expected->height; i++){
        for(int j = 0; j < expected->width; j++){
            cr_assert_eq(actual->image[i][j].red, expected->image[i][j].red, " %s\n  Wrong value at pixel (%d, %d):\n        Actual red: %d\n        Expected red: %d", err_msg, i, j, actual->image[i][j].red, expected->image[i][j].red);
            cr_assert_eq(actual->image[i][j].green, expected->image[i][j].green, " %s\n  Wrong value at pixel (%d, %d):\n        Actual green: %d\n        Expected green: %d", err_msg, i, j, actual->image[i][j].green, expected->image[i][j].green);
            cr_assert_eq(actual->image[i][j].blue, expected->image[i][j].blue, " %s\n  Wrong value at pixel (%d, %d):\n        Actual blue: %d\n        Expected blue: %d", err_msg, i, j, actual->image[i][j].blue, expected->image[i][j].blue);
        }
    }
    free_ppm(input);
    free_ppm(expected);
    free_ppm(actual);
}

TestSuite(create_greyscale, .timeout=60);

Test(create_greyscale, testA) 
{
    helper_create_greyscale("tests/test-images/test1.ppm", "tests/test-images/greyscale1.ppm", "create_greyscale/testA");
}

Test(create_greyscale, testB) 
{
    helper_create_greyscale("tests/test-images/test2.ppm", "tests/test-images/greyscale2.ppm", "create_greyscale/testB");
}

/********** Task 3: Blur image **********/

void helper_blur(char* input_file, int size, char* expected_file, char *test_name)
{
    ppm_t *input = read_ppm(input_file);
    ppm_t *expected = read_ppm(expected_file);

    ppm_t *actual = blur(input, size);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  blur with box size %d failed with PPM: %s\n"
              "\n  The filter to run this specific test is: --filter %s"), size, input_file, test_name);

    cr_assert_eq(actual->height, expected->height, " %s\n      Actual height: %d\n      Expected height: %d ", err_msg, actual->height, expected->height);
    cr_assert_eq(actual->width, expected->width, " %s\n      Actual width: %d\n      Expected width: %d ", err_msg, actual->width, expected->width);
    for(int i = 0; i < expected->height; i++){
        for(int j = 0; j < expected->width; j++){
            cr_assert_eq(actual->image[i][j].red, expected->image[i][j].red, " %s\n  Wrong value at pixel (%d, %d):\n        Actual red: %d\n        Expected red: %d", err_msg, i, j, actual->image[i][j].red, expected->image[i][j].red);
            cr_assert_eq(actual->image[i][j].green, expected->image[i][j].green, " %s\n  Wrong value at pixel (%d, %d):\n        Actual green: %d\n        Expected green: %d", err_msg, i, j, actual->image[i][j].green, expected->image[i][j].green);
            cr_assert_eq(actual->image[i][j].blue, expected->image[i][j].blue, " %s\n  Wrong value at pixel (%d, %d):\n        Actual blue: %d\n        Expected blue: %d", err_msg, i, j, actual->image[i][j].blue, expected->image[i][j].blue);
        }
    }
    free_ppm(input);
    free_ppm(expected);
    free_ppm(actual);
}

TestSuite(blur, .timeout=60);

Test(blur, testA) 
{
    helper_blur("tests/test-images/test1.ppm", 1, "tests/test-images/blur1-1.ppm", "blur/testA");
}

Test(blur, testB) 
{
    helper_blur("tests/test-images/test1.ppm", 3, "tests/test-images/blur1-3.ppm", "blur/testB");
}

Test(blur, testC) 
{
    helper_blur("tests/test-images/test1.ppm", 5, "tests/test-images/blur1-5.ppm", "blur/testC");
}

Test(blur, testD) 
{
    helper_blur("tests/test-images/test2.ppm", 1, "tests/test-images/blur2-1.ppm", "blur/testD");
}

Test(blur, testE) 
{
    helper_blur("tests/test-images/test2.ppm", 3, "tests/test-images/blur2-3.ppm", "blur/testE");
}

Test(blur, testF) 
{
    helper_blur("tests/test-images/test2.ppm", 5, "tests/test-images/blur2-5.ppm", "blur/testF");
}