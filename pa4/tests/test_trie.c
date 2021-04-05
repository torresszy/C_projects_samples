#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

#include "trie.h"

#define EPSILON (0.000001)
#define ERR_MSG_LEN (1000)

/********** Create tries for tests **********/

tnode_t *trie1()
{
    tnode_t *t = create_trie_node();
    add_word(t, "the");
    return t;
}

tnode_t *trie2()
{
    tnode_t *t = create_trie_node();
    add_word(t, "the");
    add_word(t, "an");
    return t;
}

tnode_t *trie3()
{
    tnode_t *t = create_trie_node();
    add_word(t, "the");
    add_word(t, "there");
    return t;
}

tnode_t *trie4()
{
    tnode_t *t = create_trie_node();
    add_word(t, "the");
    add_word(t, "there");
    add_word(t, "their");
    return t;
}

// string representations
char *trie1_string()
{
    return "      tnode_t *t = create_trie_node();\n      add_word(t, 'the');";
}

char *trie2_string()
{
    return "      tnode_t *t = create_trie_node();\n      add_word(t, 'the');\n      add_word(t, 'an');";
}

char *trie3_string()
{
    return "      tnode_t *t = create_trie_node();\n      add_word(t, 'the');\n      add_word(t, 'there');";
}

char *trie4_string()
{
    return "      tnode_t *t = create_trie_node();\n      add_word(t, 'the');\n      add_word(t, 'there');\n      add_word(t, 'their');";
}

/********** Create a trie node **********/

/* helper_create_trie_node: helper for create_trie_node
 *
 * test_name: test name in error messages
 */
void helper_create_trie_node(char *test_name)
{
    tnode_t *actual = create_trie_node();
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Function called in failed test:\n      create_trie_node()\n"
              "\n  The filter to run this specific test is: --filter %s"), test_name);

    // check next tnode_t pointers
    for(int i = 0; i < NUM_CHARACTERS; i++) {
        cr_assert_eq(actual->next[i], NULL, "%s\n      Actual next[%d] != NULL\n      Expected next[%d] = NULL ", err_msg, i, i);
    }

    // check tnode_t fields
    cr_assert_eq(actual->final, false, " %s\n      Actual final: %d\n      Expected final: false ", err_msg, actual->final);
    cr_assert_eq(actual->count, 0,     " %s\n      Actual count: %d\n      Expected count: 0 ", err_msg, actual->count);

    free_trie(actual);
}

TestSuite(create_trie_node, .timeout=60);

Test(create_trie_node, testA) 
{
    helper_create_trie_node("create_trie_node/testA");
}

/********** Add a word to a trie **********/

TestSuite(add_word, .timeout=60);

Test(add_word, testA) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();

    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: add_word(t, 'the')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "add_word/testA");

    // check root node
    cr_assert_eq(actual->count, 1, "%s\n      Root node:\n      Actual count: %d\n      Expected count: 1", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Root node:\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 3, "%s\n      Root node:\n      Actual longest: %d\n      Expected longest: 3", err_msg, actual->longest);

    // check 't'
    actual = actual->next[19];
    cr_assert_eq(actual->count, 1, "%s\n      Node 't':\n      Actual count: %d\n      Expected count: 1", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Node 't':\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 2, "%s\n      Node 't':\n      Actual longest: %d\n      Expected longest: 2", err_msg, actual->longest);

    // check 'h'
    actual = actual->next[7];
    cr_assert_eq(actual->count, 1, "%s\n      Node 'h':\n      Actual count: %d\n      Expected count: 1", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Node 'h':\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 1, "%s\n      Node 'h':\n      Actual longest: %d\n      Expected longest: 1", err_msg, actual->longest);

    // check 'e'
    actual = actual->next[4];
    cr_assert_eq(actual->count, 1, "%s\n      Node 'e':\n      Actual count: %d\n      Expected count: 1", err_msg, actual->count);
    cr_assert_eq(actual->final, true, "%s\n      Node 'e':\n      Actual final: %d\n      Expected final: true", err_msg, actual->final);
    cr_assert_eq(actual->longest, 0, "%s\n      Node 'e':\n      Actual longest: %d\n      Expected longest: 0", err_msg, actual->longest);

    free_trie(actual);
}

Test(add_word, testB) 
{
    tnode_t *actual = trie2();
    char *test_string = trie2_string();

    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: add_word(t, 'an')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "add_word/testB");

    // check root node
    cr_assert_eq(actual->count, 2, "%s\n      Root node:\n      Actual count: %d\n      Expected count: 2", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Root node:\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 3, "%s\n      Root node:\n      Actual longest: %d\n      Expected longest: 3", err_msg, actual->longest);

    // check 'a'
    actual = actual->next[0];
    cr_assert_eq(actual->count, 1, "%s\n      Node 'a':\n      Actual count: %d\n      Expected count: 1", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Node 'a':\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 1, "%s\n      Node 'a':\n      Actual longest: %d\n      Expected longest: 1", err_msg, actual->longest);

    // check 'n'
    actual = actual->next[13];
    cr_assert_eq(actual->count, 1, "%s\n      Node 'n':\n      Actual count: %d\n      Expected count: 1", err_msg, actual->count);
    cr_assert_eq(actual->final, true, "%s\n      Node 'n':\n      Actual final: %d\n      Expected final: true", err_msg, actual->final);
    cr_assert_eq(actual->longest, 0, "%s\n      Node 'n':\n      Actual longest: %d\n      Expected longest: 0", err_msg, actual->longest);

    free_trie(actual);
}

Test(add_word, testC) 
{
    tnode_t *actual = trie3();
    char *test_string = trie3_string();

    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: add_word(t, 'there')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "add_word/testC");

    // check root node
    cr_assert_eq(actual->count, 2, "%s\n      Root node:\n      Actual count: %d\n      Expected count: 2", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Root node:\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 5, "%s\n      Root node:\n      Actual longest: %d\n      Expected longest: 5", err_msg, actual->longest);

    // check 't'
    actual = actual->next[19];
    cr_assert_eq(actual->count, 2, "%s\n      Node 't':\n      Actual count: %d\n      Expected count: 2", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Node 't':\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 4, "%s\n      Node 't':\n      Actual longest: %d\n      Expected longest: 4", err_msg, actual->longest);

    // check 'h'
    actual = actual->next[7];
    cr_assert_eq(actual->count, 2, "%s\n      Node 'h':\n      Actual count: %d\n      Expected count: 2", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Node 'h':\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 3, "%s\n      Node 'h':\n      Actual longest: %d\n      Expected longest: 3", err_msg, actual->longest);

    // check 'e'
    actual = actual->next[4];
    cr_assert_eq(actual->count, 2, "%s\n      Node 'e':\n      Actual count: %d\n      Expected count: 2", err_msg, actual->count);
    cr_assert_eq(actual->final, true, "%s\n      Node 'e':\n      Actual final: %d\n      Expected final: true", err_msg, actual->final);
    cr_assert_eq(actual->longest, 2, "%s\n      Node 'e':\n      Actual longest: %d\n      Expected longest: 2", err_msg, actual->longest);

    // check 'r'
    actual = actual->next[17];
    cr_assert_eq(actual->count, 1, "%s\n      Node 'r':\n      Actual count: %d\n      Expected count: 1", err_msg, actual->count);
    cr_assert_eq(actual->final, false, "%s\n      Node 'r':\n      Actual final: %d\n      Expected final: false", err_msg, actual->final);
    cr_assert_eq(actual->longest, 1, "%s\n      Node 'r':\n      Actual longest: %d\n      Expected longest: 1", err_msg, actual->longest);

    // check 'e'
    actual = actual->next[4];
    cr_assert_eq(actual->count, 1, "%s\n      Node 'e':\n      Actual count: %d\n      Expected count: 1", err_msg, actual->count);
    cr_assert_eq(actual->final, true, "%s\n      Node 'e':\n      Actual final: %d\n      Expected final: true", err_msg, actual->final);
    cr_assert_eq(actual->longest, 0, "%s\n      Node 'e':\n      Actual longest: %d\n      Expected longest: 0", err_msg, actual->longest);
}

/********** Is a word in a trie **********/

/* helper_is_a_word: helper for is_a_word
 *
 * actual_trie: student trie
 * word: word to look for in the trie
 * expected: expected output (is the word there?)
 * test_string: string representation of the trie
 */
void helper_is_a_word(tnode_t *actual_trie, char *word, bool expected, char *test_string, char *test_name)
{

    bool actual = is_a_word(actual_trie, word);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: is_a_word(t, '%s')\n"
              "\n      Actual: %d"
              "\n      Expected: %d"
              "\n  The filter to run this specific test is: --filter %s"), test_string, word, actual, expected, test_name);

    cr_assert_eq(actual, expected, " %s", err_msg);
    free_trie(actual_trie);
}

TestSuite(is_a_word, .timeout=60);

Test(is_a_word, testA) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_is_a_word(actual, "t", false, test_string, "is_a_word/testA");
}

Test(is_a_word, testB) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_is_a_word(actual, "th", false, test_string, "is_a_word/testB");
}

Test(is_a_word, testC) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_is_a_word(actual, "the", true, test_string, "is_a_word/testC");
}

Test(is_a_word, testD) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_is_a_word(actual, "thee", false, test_string, "is_a_word/testD");
}

Test(is_a_word, testE) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_is_a_word(actual, "th", false, test_string, "is_a_word/testE");
}

Test(is_a_word, testF) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_is_a_word(actual, "the", true, test_string, "is_a_word/testF");
}

Test(is_a_word, testG) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_is_a_word(actual, "ther", false, test_string, "is_a_word/testG");
}

Test(is_a_word, testH) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_is_a_word(actual, "there", true, test_string, "is_a_word/testH");
}

Test(is_a_word, testI) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_is_a_word(actual, "thei", false, test_string, "is_a_word/testI");
}

Test(is_a_word, testJ) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_is_a_word(actual, "their", true, test_string, "is_a_word/testJ");
}

Test(is_a_word, testK) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_is_a_word(actual, "theirs", false, test_string, "is_a_word/testK");
}

/********** Get the number of completions **********/

/* helper_num_completions: helper for num_completions
 *
 * actual_trie: student trie
 * prefix: prefix to look for in the trie
 * expected: expected output (number of completions)
 * test_string: string representation of the trie
 */
void helper_num_completions(tnode_t *actual_trie, char *prefix, int expected, char *test_string, char *test_name)
{

    int actual = num_completions(actual_trie, prefix);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: num_completions(t, '%s')\n"
              "\n      Actual: %d"
              "\n      Expected: %d"
              "\n  The filter to run this specific test is: --filter %s"), test_string, prefix, actual, expected, test_name);

    cr_assert_eq(actual, expected, " %s", err_msg);
    free_trie(actual_trie);
}

TestSuite(num_completions, .timeout=60);

Test(num_completions, testA) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_num_completions(actual, "t", 1, test_string, "num_completions/testA");
}

Test(num_completions, testB) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_num_completions(actual, "th", 1, test_string, "num_completions/testB");
}

Test(num_completions, testC) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_num_completions(actual, "the", 1, test_string, "num_completions/testC");
}

Test(num_completions, testD) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_num_completions(actual, "a", 0, test_string, "num_completions/testD");
}

Test(num_completions, testE) 
{
    tnode_t *actual = trie1();
    char *test_string = trie1_string();
    helper_num_completions(actual, "tha", 0, test_string, "num_completions/testE");
}

Test(num_completions, testF) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_num_completions(actual, "t", 3, test_string, "num_completions/testF");
}

Test(num_completions, testG) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_num_completions(actual, "th", 3, test_string, "num_completions/testG");
}

Test(num_completions, testH) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_num_completions(actual, "the", 3, test_string, "num_completions/testH");
}

Test(num_completions, testI) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_num_completions(actual, "thei", 1, test_string, "num_completions/testI");
}

Test(num_completions, testJ) 
{
    tnode_t *actual = trie4();
    char *test_string = trie4_string();
    helper_num_completions(actual, "ther", 1, test_string, "num_completions/testJ");
}

/********** Get the completions **********/

TestSuite(get_completions, .timeout=60);

Test(get_completions, testA) 
{
    tnode_t *actual_trie = trie1();
    char *test_string = trie1_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, '')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testA");

    char **actual = get_completions(actual_trie, "");
    cr_assert_eq(strcmp(actual[0], "the"), 0, "%s\n      Not found: 'the'", err_msg);

    free(actual[0]);
    free(actual);
    free_trie(actual_trie);
}

Test(get_completions, testB) 
{
    tnode_t *actual_trie = trie1();
    char *test_string = trie1_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, 't')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testB");

    char **actual = get_completions(actual_trie, "t");
    cr_assert_eq(strcmp(actual[0], "he"), 0, "%s\n      Not found: 'he'", err_msg);

    free(actual[0]);
    free(actual);
    free_trie(actual_trie);
}

Test(get_completions, testC) 
{
    tnode_t *actual_trie = trie1();
    char *test_string = trie1_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, 'th')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testC");

    char **actual = get_completions(actual_trie, "th");
    cr_assert_eq(strcmp(actual[0], "e"), 0, "%s\n      Not found: 'e'", err_msg);

    free(actual[0]);
    free(actual);
    free_trie(actual_trie);
}

Test(get_completions, testD) 
{
    tnode_t *actual_trie = trie1();
    char *test_string = trie1_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, 'the')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testD");

    char **actual = get_completions(actual_trie, "the");
    cr_assert_eq(strcmp(actual[0], ""), 0, "%s\n      Not found: ''", err_msg);

    free(actual[0]);
    free(actual);
    free_trie(actual_trie);
}

Test(get_completions, testE) 
{
    tnode_t *actual_trie = trie2();
    char *test_string = trie2_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, '')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testE");

    char **actual = get_completions(actual_trie, "");
    int num = 2; // number of completions
   
    // check for "an"
    bool found = false;
    for(int i = 0; i < num; i++){
        if (strcmp(actual[i], "an") == 0){
            found = true;
        }
    }
    cr_assert_eq(found, true, "%s\n      Not found: 'an'", err_msg);

    // check for "the"
    found = false;
    for(int i = 0; i < num; i++){
        if (strcmp(actual[i], "the") == 0){
            found = true;
        }
    }
    cr_assert_eq(found, true, "%s\n      Not found: 'the'", err_msg);

    for(int i = 0; i < num; i++){
        free(actual[i]);
    }
    free(actual);
    free_trie(actual_trie);
}

Test(get_completions, testF) 
{
    tnode_t *actual_trie = trie4();
    char *test_string = trie4_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, 't')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testF");

    char **actual = get_completions(actual_trie, "t");
    int num = 3; // number of completions
   
    // check for "he"
    bool found = false;
    for(int i = 0; i < num; i++){
        if (strcmp(actual[i], "he") == 0){
            found = true;
        }
    }
    cr_assert_eq(found, true, "%s\n      Not found: 'he'", err_msg);

    // check "hier"
    found = false;
    for(int i = 0; i < num; i++){
        if (strcmp(actual[i], "heir") == 0){
            found = true;
        }
    }
    cr_assert_eq(found, true, "%s\n      Not found: 'heir'", err_msg);

    // check "here"
    found = false;
    for(int i = 0; i < num; i++){
        if (strcmp(actual[i], "here") == 0){
            found = true;
        }
    }
    cr_assert_eq(found, true, "%s\n      Not found: 'here'", err_msg);

    for(int i = 0; i < num; i++){
        free(actual[i]);
    }
    free(actual);
    free_trie(actual_trie);
}

Test(get_completions, testG) 
{
    tnode_t *actual_trie = trie4();
    char *test_string = trie4_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, 'the')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testG");

    char **actual = get_completions(actual_trie, "the");
    int num = 3; // number of completions
   
    // check for "he"
    bool found = false;
    for(int i = 0; i < num; i++){
        if (strcmp(actual[i], "") == 0){
            found = true;
        }
    }
    cr_assert_eq(found, true, "%s\n      Not found: ''", err_msg);

    // check "hier"
    found = false;
    for(int i = 0; i < num; i++){
        if (strcmp(actual[i], "ir") == 0){
            found = true;
        }
    }
    cr_assert_eq(found, true, "%s\n      Not found: 'ir'", err_msg);

    // check "here"
    found = false;
    for(int i = 0; i < num; i++){
        if (strcmp(actual[i], "re") == 0){
            found = true;
        }
    }
    cr_assert_eq(found, true, "%s\n      Not found: 're'", err_msg);

    for(int i = 0; i < num; i++){
        free(actual[i]);
    }
    free(actual);
    free_trie(actual_trie);
}

Test(get_completions, testH) 
{
    tnode_t *actual_trie = trie4();
    char *test_string = trie4_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, 'ther')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testH");

    char **actual = get_completions(actual_trie, "ther");
    cr_assert_eq(strcmp(actual[0], "e"), 0, "%s\n      Not found: 'e'", err_msg);

    free(actual[0]);
    free(actual);
    free_trie(actual_trie);
}

Test(get_completions, testI) 
{
    tnode_t *actual_trie = trie4();
    char *test_string = trie4_string();
    
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Functions called in failed test: \n%s"
              "\n  Test failed: get_completions(t, 'thei')\n"
              "\n  The filter to run this specific test is: --filter %s"), test_string, "get_completions/testI");

    char **actual = get_completions(actual_trie, "thei");
    cr_assert_eq(strcmp(actual[0], "r"), 0, "%s\n      Not found: 'r'", err_msg);

    free(actual[0]);
    free(actual);
    free_trie(actual_trie);
}