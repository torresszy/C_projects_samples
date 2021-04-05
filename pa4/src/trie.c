/* CMSC 15200, Winter 2021
 * PA #4 Trie: Source for PA #4.
 */




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "trie.h"

/* convert the input letter into the corresponding integer
 * index
 * 
 * letter: the input letter
 * 
 * Returns: an integer index
 */
int convert(char letter)
{
    return letter - 'a'; 
}

/* convert the index into the corresponding letter
 * 
 * index: the input index
 * 
 * Returns: a char letter
 */
char convert_index_to_letter(int index)
{
    return index + 'a';
}

/* Create a new tnode_t
 *
 * Returns: a pointer to a tnode_t
 */ 
tnode_t *create_trie_node()
{
    tnode_t* node = (tnode_t*)malloc(sizeof(tnode_t));

    node->final = false;
    node->count = 0;
    node->longest = 0;

    for (int i = 0; i < NUM_CHARACTERS; i++) {
        node->next[i] = NULL; 
    }

    return node;
}

/* Free a trie
 *
 * trie: a pointer to the trie
 */ 
void free_trie(tnode_t *trie)
{   
    for (int i = 0; i < NUM_CHARACTERS; i++) {
        if (trie->next[i]) {
            free_trie(trie->next[i]);
        }
    }
    free(trie);
}   

/* add each letter node of a given word recursively 
 * to a trie
 * 
 * trie: a pointer to the trie
 * word: the word to add
 * index: a pointer to the current index of the word string
 * word_length: the length of the word to add
 */
void add_node(tnode_t* trie, char* word, int* index, int word_length)
{   
    if (*index > word_length) {
        return;
    }

    int array_index = convert(word[*index]);
    if (trie->next[array_index] == NULL) {
        trie->next[array_index] = create_trie_node();
    }

    trie->count += 1;
    if (trie->longest < (word_length - *index)) {
        trie->longest = word_length - *index;
    }
    if (*index == word_length) {
        trie->final = true;
    }

    (*index)++;
    add_node(trie->next[array_index], word, index, word_length);
}

/* Add a word to a trie
 *
 * trie: a pointer to the trie
 * word: the word to add
 */ 
void add_word(tnode_t *trie, char *word)
{
    int word_length = strlen(word);
    int index = 0;
    add_node(trie, word, &index, word_length);
}

/* Determine whether a word is in a trie
 *
 * trie: a pointer to the trie
 * word: the word to search for
 * 
 * Returns: whether the word is in the trie
 */ 
bool is_a_word(tnode_t *trie, char *word)
{
    int word_length = strlen(word);
    tnode_t* curr = trie;

    for (int i = 0; i < word_length; i++) {
        if (curr->next[convert(word[i])] == NULL) {
            return false;
        }
        curr = curr->next[convert(word[i])];
    }

    return curr->final;
}

/* Get the number of completions
 *
 * trie: a pointer to the trie
 * prefix: the prefix to complete
 * 
 * Returns: the number of completions
 */ 
int num_completions(tnode_t *trie, char *prefix)
{
    int prefix_length = strlen(prefix);
    tnode_t* curr = trie;

    for (int i = 0; i < prefix_length; i++) {
        if (curr->next[convert(prefix[i])] == NULL) {
            return 0;
        } else {
            curr = curr->next[convert(prefix[i])]; 
        }
    }

    return curr->count;
}

/* Add the suffixes into the completion array 
 * 
 * node: a pointer to the current node in the trie
 * suffixes: an array that will contain all the completions 
 *   at the end
 * index: a pointer to the current index of the suffixes array
 * curr_completion: a string holding the current completion as
 *   it traverses down the trie
 */
void add_suffixes(tnode_t* node, char** suffixes, int* index, char* curr_completion)
{   
    if (node->final) {
        strcpy(suffixes[*index], curr_completion);
        (*index)++;
    }

    for (int i = 0; i < NUM_CHARACTERS; i++) {
        if (node->next[i] != NULL) {
            char letter = convert_index_to_letter(i);
            char* new_completion = (char*)malloc(sizeof(char) * (strlen(curr_completion) + 1));
            strcpy(new_completion, curr_completion);
            new_completion[strlen(curr_completion)] = letter;
            add_suffixes(node->next[i], suffixes, index, new_completion);
        }
    }
}

/* Construct the completions of a prefix
 *
 * trie: a pointer to the trie
 * prefix: the prefix to complete
 * 
 * Returns: an array of completion strings
 */ 
char **get_completions(tnode_t *trie, char *prefix)
{
    int num_suffixes = num_completions(trie, prefix);
    if (num_suffixes == 0) {
        return NULL;
    }

    tnode_t* curr = trie;
    int prefix_length = strlen(prefix);
    for (int i = 0; i < prefix_length; i++) {
        curr = curr->next[convert(prefix[i])];
    }

    int index = 0;
    char** suffixes = (char**)malloc(sizeof(char*) * num_suffixes);
    for (int i = 0; i < num_suffixes; i++) {
        suffixes[i] = (char*)malloc(sizeof(char) * (curr->longest + 1));
    }
    
    add_suffixes(curr, suffixes, &index, "");
    return suffixes;
}
