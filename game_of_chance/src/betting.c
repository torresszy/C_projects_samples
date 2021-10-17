#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "util.h"
#include "betting.h"


/* one_dollar: simulate a game following the one
 *  dollar strategy
 *
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * 
 * Returns: the amount of cash on hand at the end of the game as a double.
 */
double one_dollar(double init_amount, int num_bets)
{
    double remaining_amount = init_amount;
    for (int b = 1; (b <= num_bets) && (remaining_amount > 0); b++) {
      if (flip_coin()) {
        remaining_amount += 1.0;
      } else {
        remaining_amount -= 1.0;
      }
    }

    return remaining_amount;
}


/* double_strategy: simulate a game following the double
 *   on wins/losses strategy
 *
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * win: true if the rule is double on wins, false if
 *   the rule is double on losses
 * 
 * Returns: the amount of cash on hand at the end of the game as a double.
 */
double double_strategy(double init_amount, int num_bets, bool win)
{
    double remaining_amount = init_amount;
    double bet_amount = 1.0;
    for (int b = 1; (b <= num_bets) && (remaining_amount > 0); b++) {
      if (bet_amount >= remaining_amount) {
        bet_amount = remaining_amount;
      } 
      if (flip_coin()) {
        remaining_amount += bet_amount;
        if (win) {
          bet_amount *= 2;
        }
      } else {
        remaining_amount -= bet_amount;
        if (!win) {
          bet_amount *= 2;
        }
      }
    }

    return remaining_amount;
}


/* fib_strategy: simulate a game following the 
 *   fibonacci strategy
 *
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * 
 * Returns: the amount of cash on hand at the end of the game as a double.
 */
double fib_strategy(double init_amount, int num_bets)
{
    double remaining_amount = init_amount;
    double current_bet_amount = 1.0;
    double previous_bet_amount = 0.0;
    double new_bet_amount = current_bet_amount;

    for (int b = 1; (b <= num_bets) && (remaining_amount > 0); b++) {
      if (current_bet_amount >= remaining_amount) {
        current_bet_amount = remaining_amount;
      }
      if (flip_coin()) {
        remaining_amount += current_bet_amount;
        new_bet_amount = 1.0;
        previous_bet_amount = 0.0;
      } else {
        remaining_amount -= current_bet_amount;
        new_bet_amount = previous_bet_amount + current_bet_amount;
        previous_bet_amount = current_bet_amount;
      }
      current_bet_amount = new_bet_amount;
    }

    return remaining_amount;
}


/* series_strategy: simulate a game following the series strategy
 *
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * 
 * Returns: the amount of cash on hand at the end of the game as a double.
 */
double series_strategy(double init_amount, int num_bets)
{
    double remaining_amount = init_amount;
    double bet_amount = 1.0;
    double series_total = 0.0;

    for (int b = 1; (b <= num_bets) && (remaining_amount > 0); b++) {
      if (series_total == 1.0) {
        series_total = 0.0;
        bet_amount = 1.0;
      }
      if (bet_amount >= (1.0 - series_total)) {
        bet_amount = (1.0 - series_total);
      }
      if (bet_amount >= remaining_amount) {
        bet_amount = remaining_amount;
      }
      if (flip_coin()) {
        remaining_amount += bet_amount;
        series_total += bet_amount;
        bet_amount += 1.0;
      } else {
        remaining_amount -= bet_amount;
        series_total -= bet_amount;
      }
    }

    return remaining_amount;
}


/* simulate_game: simulate a single game
 *
 * strategy: the betting strategy to use
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * unsigned int seed: used to initialize the random number generator
 *
 * Returns: the amount of cash on hand at the end of the game as a double.
 */
double simulate_game(enum betting_strategies strategy, double init_amount,
                     int num_bets, unsigned int seed)
{
    // Do not remove or move this call to srand.  It initializes the
    // random number generator, which should be done exactly once per
    // game.
    srand(seed);

    switch (strategy) {
      case ONE_DOLLAR:
        return one_dollar(init_amount, num_bets);
      case DOUBLE_ON_WIN:
        return double_strategy(init_amount, num_bets, true);
      case DOUBLE_ON_LOSS:
        return double_strategy(init_amount, num_bets, false);
      case FIB_STRATEGY:
        return fib_strategy(init_amount, num_bets);
      case SERIES_STRATEGY:
        return series_strategy(init_amount, num_bets);
      case FLIP_ONLY :
        return 0.0;
    }
}


/* simulate_multiple_games: simulate multiple games
 *
 * strategy: the betting strategy to use
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * init_seed: the initial value used for the random number generator
 *   seed
 * num_games: the number of games to simulate
 *
 * Returns: average amount of cash on hand at the end of the simulated
 *    games as a double
 */
double simulate_multiple_games(enum betting_strategies strategy, double init_amount,
                               int num_bets, unsigned int init_seed, int num_games)
{
    double sum = 0.0;

    for (int b = 1; (b <= num_games); b++) {
      sum += simulate_game(strategy, init_amount, num_bets, init_seed);
      init_seed ++;
    }

    return (sum / (num_games * 1.0));
}
