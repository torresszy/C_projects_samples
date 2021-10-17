#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"
#include "betting.h"

/* Add your test functions here */


/* run_and_print_single_game: helper function for calling simulate_game
 * and printing the result 
 *
 * strategy: the strategy to run
 * init_amount: initial amount of cash on hand (init_amount > 0)
 * num_bets: the maximum number of bets 
 * seed: used to initialize the random number generator
 *
 * Returns: norhing
 */
void run_and_print_single_game(enum betting_strategies strategy, double init_cash,
                               int num_bets, unsigned int seed) {
    char *bs_name = betting_strategy_to_str(strategy);
    printf("\nsimulate_game(%s, %f, %d, %u)): ",
           bs_name, init_cash, num_bets, seed);
    printf("%f\n", simulate_game(strategy, init_cash, num_bets, seed));
}

/* run_and_print_multiple_games: helper function for calling
 * simulate_multiple_games and printing the result
 *
 * strategy: the strategy to run
 * init_amount: initial amount of cash on hand (init_amount > 0)
 * num_bets: the maximum number of bets 
 * seed: initial value of the seed parameter
 * num_games: the number of games to run
 *
 * Returns: norhing
 */
void run_and_print_multiple_games(enum betting_strategies strategy, double init_cash,
                                  int num_bets, unsigned int seed, int num_games) {
    char *bs_name = betting_strategy_to_str(strategy);
    printf("\nsimulate_mutiple_games(%s, %f, %d, %u, %d)): ",
         bs_name, init_cash, num_bets, seed, num_games);
    printf("%f\n", simulate_multiple_games(strategy, init_cash, num_bets, seed, num_games));
}


int main()
{
     // update these values to do different tests

     double init_cash = 10.0;
     int num_bets = 0;
     unsigned int init_seed = 1611076235;
  
     // add calls to your test functions here.

     // sample use of helper function.  FLIP_ONLY just prints the coin
     // flips
     run_and_print_single_game(SERIES_STRATEGY, init_cash, num_bets, init_seed);

     // sample call to print_multiple_games.
     // int num_games = 100;
     // run_and_print_multiple_games(ONE_DOLLAR, init_cash, num_bets, init_seed, num_games);
}

