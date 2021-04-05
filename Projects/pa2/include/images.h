/*** DO NOT CHANGE THIS FILE ***/

struct color {
    int red;
    int green;
    int blue;
};

struct ppm {
    int height;
    int width;
    struct color **image;
};

typedef struct ppm ppm_t;

/* new_ppm: create new black ppm
 *
 * height: height of image
 * width: width of image
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *new_ppm(int height, int width);

/* free_ppm: free a ppm struct
 *
 * input: ppm to free
 */
void free_ppm(ppm_t *input);

/* create_negative: create new negative ppm 
 *
 * input: ppm to negate
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *create_negative(ppm_t *input);

/* create_greyscale: create new greyscale ppm 
 *
 * input: ppm to make grey
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *create_greyscale(ppm_t *input);

/* blur: create new blurred ppm 
 *
 * input: ppm to blur
 * size: size of area around a pixel to blur (an odd integer)
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *blur(ppm_t *input, int size);