/* CMSC 15200, Winter 2021
 *  PA #4 Trie: Source for PA #4 student tests.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "trie.h"

/* Add your functions here (if any) */

int main()
{
    tnode_t *t = create_trie_node();

    add_word(t, "and");
    add_word(t, "are");

    printf("Is \"and\" in t?: %d\n", is_a_word(t, "and"));
    printf("Is \"ant\" in t?: %d\n", is_a_word(t, "ant"));

    free_trie(t);
    /* Add your functions calls here */
}
