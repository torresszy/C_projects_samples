/* CMSC 15200, Winter 2021
 *  PA #4 Trie: header for PA #4.
 */


#define NUM_CHARACTERS 26

typedef struct trie_node tnode_t;

struct trie_node {
    bool final;
    int count;
    int longest;
    tnode_t *next[NUM_CHARACTERS]; 
};

/* Create a new tnode_t
 *
 * Returns: a pointer to a tnode_t
 */ 
tnode_t *create_trie_node();

/* Free a trie
 *
 * trie: a pointer to the trie
 */ 
void free_trie(tnode_t *trie);

/* Add a word to a trie
 *
 * trie: a pointer to the trie
 * word: the word to add
 */ 
void add_word(tnode_t *trie, char *word);

/* Determine whether a word is in a trie
 *
 * trie: a pointer to the trie
 * word: the word to search for
 * 
 * Returns: whether the word is in the trie
 */ 
bool is_a_word(tnode_t *trie, char *word);

/* Get the number of completions
 *
 * trie: a pointer to the trie
 * prefix: the prefix to complete
 * 
 * Returns: the number of completions
 */ 
int num_completions(tnode_t *trie, char *prefix);

/* Construct the completions of a prefix
 *
 * trie: a pointer to the trie
 * prefix: the prefix to complete
 * 
 * Returns: an array of completion strings
 */ 
char **get_completions(tnode_t *trie, char *prefix);
