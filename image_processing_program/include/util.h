/*** DO NOT CHANGE THIS FILE ***/

/* read_ppm: read a PPM from a file
 * 
 * filename: name of file
 *
 * Returns: ppm struct
 */
struct ppm *read_ppm(char *filename);

/* write_ppm: write a ppm struct to a file
 * 
 * filename: name of file
 * ppm: ppm to write to file
 * 
 */
void write_ppm(char *filename, struct ppm *ppm);


