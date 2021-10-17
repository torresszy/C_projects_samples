#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "images.h"

/* Add your test functions (if any) here */

int main()
{
    // Brian Kernighan image
    ppm_t *blur1_1;
    blur1_1 = read_ppm("tests/test-images/test1.ppm");

    // test negative
    ppm_t *output = blur(blur1_1, 3);
    printf("RGB: %d, %d, %d \n", output->image[1][0].red, output->image[1][0].green,output->image[1][0].blue);

    // free ppms
    free_ppm(blur1_1);
    free_ppm(output);

    
}

