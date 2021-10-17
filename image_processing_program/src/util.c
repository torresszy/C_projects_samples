/*** DO NOT CHANGE THIS FILE ***/

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "images.h"

/* read_ppm: read a ppm from a file
 * 
 * filename: name of file
 *
 * Returns: a pointer to a ppm struct
 */
ppm_t *read_ppm(char *filename)
{
    FILE *fp;
    int c, rgb_comp_color;
    char buff[16];

    //open PPM file for reading
    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "read_ppm: Unable to open file '%s'\n", filename);
        exit(1);
    }

    //read image format
    if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '3') {
         fprintf(stderr, "read_ppm: Image format must be 'P3'\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n'){
            // skip whitespace
        }
         c = getc(fp);
    }

    ungetc(c, fp);

    int width, height;
    //read image size information
    if (fscanf(fp, "%d %d", &width, &height) != 2) {
         fprintf(stderr, "read_ppm: Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "read_ppm: Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n'){
        // skip whitespace
    }

    //memory allocation for pixel data
    struct color **image = (struct color**)malloc(sizeof(struct color*) * height);
    for(int i = 0; i < height; i++){
        image[i] = (struct color*)malloc(sizeof(struct color) * width);
    }

    if (!image) {
         fprintf(stderr, "read_ppm: Unable to allocate memory\n");
         exit(1);
    }

    // read pixels
    for(int i = 0; i < height; i++) {
	    for(int j = 0; j < width; j++) {
	        fscanf(fp, "%d", &(image[i][j].red));
	        fscanf(fp, "%d", &(image[i][j].green));
	        fscanf(fp, "%d", &(image[i][j].blue));

	    }
	}

    ppm_t *ppm = (ppm_t*)malloc(sizeof(ppm_t));
    ppm->height = height;
    ppm->width = width;
    ppm->image = image;

    fclose(fp);
    return ppm;
}

/* write_ppm: write a ppm to a file
 * 
 * filename: name of file
 * ppm: pointer to a ppm struct to write to file
 * 
 */
void write_ppm(char *filename, ppm_t *ppm)
{
    FILE *fp;

    if (ppm == NULL) {
      fprintf(stderr, "write_ppm: called with NULL pointer.\n");
      return;
    }

    //open file for output
    fp = fopen(filename, "w");
    if (!fp) {
         fprintf(stderr, "write_ppm: Unable to open file '%s'\n", filename);
         exit(1);
    }

    //image format
    fprintf(fp, "P3\n");

    //image size
    fprintf(fp, "%d %d\n", ppm->width, ppm->height);

    // rgb component depth
    fprintf(fp, "%d\n", 255);

    // write rgb pixels
    for(int i = 0; i < ppm->height; i++) {
	    for(int j = 0; j < ppm->width; j++) {

	        fprintf(fp, "%d ", (ppm->image[i][j].red));
	        fprintf(fp, "%d ", (ppm->image[i][j].green));
	        fprintf(fp, "%d ", (ppm->image[i][j].blue));
	    }
        fprintf(fp, "\n");
	}
    fclose(fp);
}
