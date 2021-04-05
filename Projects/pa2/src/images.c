#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "images.h"

#define MAX_INTENSITY 255

/* new_ppm: create new black ppm
 *
 * height: height of image
 * width: width of image
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *new_ppm(int height, int width)
{
    ppm_t* rv = (ppm_t*)malloc(sizeof(ppm_t));
    
    rv->height = height;
    rv->width = width;
    rv->image = (struct color**)malloc(sizeof(struct color*) * height);
    for (int i = 0; i < height; i++) {
        rv->image[i] = (struct color*)malloc(sizeof(struct color) * width);
    } 

    return rv;
}

/* free_ppm: free a ppm struct
 *
 * input: ppm to free
 */
void free_ppm(ppm_t *input)
{
    for (int i = 0; i < input->height; i++) {
        free(input->image[i]);
    }

    free(input->image);
    free(input);
}

/* create_negative: create new negative ppm 
 *
 * input: ppm to negate
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *create_negative(ppm_t *input)
{
    ppm_t* rv = new_ppm(input->height, input->width);

    for (int x = 0; x < input->height; x++) {
        for (int y = 0; y < input->width; y++) {
            rv->image[x][y].red = MAX_INTENSITY - input->image[x][y].red;
            rv->image[x][y].blue = MAX_INTENSITY - input->image[x][y].blue;
            rv->image[x][y].green = MAX_INTENSITY - input->image[x][y].green;
        }
    }

    return rv;
}

/* greyscale_average: calculate the greyscale average 
 *   based on the specific method given
 *
 * RGB: a struct that contains the RGB values for a specific pixel
 *
 * Returns: calculated average (an integer)
 */
int greyscale_average(struct color RGB)
{
    return ((77 * RGB.red) + (150 * RGB.green) + (29 * RGB.blue)) / 256;
}

/* create_greyscale: create new greyscale ppm 
 *
 * input: ppm to make grey
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *create_greyscale(ppm_t *input)
{
    ppm_t* rv = new_ppm(input->height, input->width);

    for (int x = 0; x < input->height; x++) {
        for (int y = 0; y < input->width; y++) {
            int average = greyscale_average(input->image[x][y]);
            rv->image[x][y].red = average;
            rv->image[x][y].blue = average;
            rv->image[x][y].green = average;
        }
    }

    return rv; 
}

/* set_lower_bound: determines the index of the top or the
 *   left side of the rectangle around a pixel to blur
 *
 * index: the index of the traget blurring pixel
 * dist_from_mid: distnce from the edge to the midpoint 
 *   of the rectangle around the blurring target
 *
 * Returns: the index of the top or the left bound (an integer)
 */
int set_lower_bound(int index, int dist_from_mid)
{
    if ((index - dist_from_mid) > 0) {
        return index - dist_from_mid;
    } else {
        return 0;
    }
}

/* set_upper_bound: determines the index of the bottom or the
 *   right side of the rectangle around a pixel to blur
 *
 * index: the index of the traget blurring pixel
 * dist_from_mid: distnce from the edge to the midpoint 
 *   of the rectangle around the blurring target
 * max_len: the length of the image array
 *
 * Returns: the index of the bottom or the right bound (an integer)
 */
int set_upper_bound(int index, int dist_from_mid, int max_len)
{
   if ((index + dist_from_mid) < max_len) {
       return index + dist_from_mid;
   } else {
       return max_len - 1;
   }
}

/* calculate_blur_average: calculates and assigns the new averaged
 *   value to each pixel of the new blurred ppm 
 *
 * input: ppm to blur
 * output: a new ppm for the blurred result
 * upper_bound: the upper bound of the rectangle around a pixel
 *   to blur
 * lower_bound: the lower bound of the rectangle around a pixel
 *   to blur
 * left_bound: the left bound of the rectangle around a pixel
 *   to blur
 * right_bound: the right bound of the rectangle around a pixel
 *   to blur
 * index_x: the first (row) index of the target blurring pixel 
 *   in the 2-dimensional array
 * index_y: the second (column) index of the target blurring pixel 
 *   in the 2-dimensional array
 *
 * Returns: none, modifies the output ppm.
 */
void calculate_blur_average(ppm_t *input, ppm_t *output, int upper_bound,
                            int lower_bound, int left_bound, int right_bound, int index_x, int index_y) 
{

    int num_val = (lower_bound - upper_bound + 1) * (right_bound - left_bound + 1);
    int sum_red = 0;
    int sum_blue = 0;
    int sum_green =0;

    for (int i = upper_bound; i <= lower_bound; i++) {
        for (int j = left_bound; j <= right_bound; j++) {
            sum_red += input->image[i][j].red;
            sum_blue += input->image[i][j].blue;
            sum_green += input->image[i][j].green;
        }
    } 

    output->image[index_x][index_y].red = sum_red / num_val;
    output->image[index_x][index_y].blue = sum_blue / num_val;
    output->image[index_x][index_y].green = sum_green / num_val;
}

/* blur: create new blurred ppm 
 *
 * input: ppm to blur
 * size: size of area around a pixel to blur (an odd integer)
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *blur(ppm_t *input, int size)
{
    ppm_t* rv = new_ppm(input->height, input->width);

    int dist_from_mid = (size - 1) / 2;
    int upper_bound = 0;
    int lower_bound = 0;
    int left_bound = 0;
    int right_bound = 0;

    for (int x = 0; x < input->height; x++) {
        upper_bound = set_lower_bound(x, dist_from_mid);
        lower_bound = set_upper_bound(x, dist_from_mid, input->height);

        for (int y = 0; y < input->width; y++) {
            left_bound = set_lower_bound(y, dist_from_mid);
            right_bound = set_upper_bound(y, dist_from_mid, input->width);

            calculate_blur_average(input, rv, upper_bound, 
                                   lower_bound, left_bound, right_bound, x, y);
        }
    }

    return rv;
}
