#include <stdbool.h>
#include <stdio.h>
#include <criterion/criterion.h>

#include "util.h"
#include "betting.h"

#define EPSILON (0.000001)
#define ERR_MSG_LEN (1000)


/* helper_simulate_game: Do the work of one of testing one strategy
 *    for one game.
 *
 * strategy: which strategy to run
 * init_amount: initial amount of cash on hand (init_amount > 0)
 * num_bets: the maximum number of bets 
 * test_name - the test name to be used in error messages.
 */
void helper_simulate_game(enum betting_strategies strategy, double init_amount,
                          int num_bets, unsigned int seed,
                          double expected, char *test_name)
{
    double actual = simulate_game(strategy, init_amount, num_bets, seed);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Parameters used in failed test: "
              "simulate_game(%s, %f, %d, %u)\n"
              "\n     Actual: %.2f"
              "\n     Expected: %.2f"
              "\n  The filter to run this specific test is: --filter %s"),
             betting_strategy_to_str(strategy), init_amount, num_bets, seed,
             actual, expected, test_name);

    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_float_eq(actual, expected, EPSILON, " %s", err_msg);
}

/********** Bet one dollar tests **********/

TestSuite(one_dollar, .timeout=60);

Test(one_dollar, testA) {
    // corner case: no bets
    unsigned int seed = 1611076235;
    helper_simulate_game(ONE_DOLLAR, 10.0, 0, seed, 10.0, "one_dollar/testA");
}

Test(one_dollar, testB) {
    // test: one loss
    unsigned int seed = 1611076235;
    helper_simulate_game(ONE_DOLLAR, 10.0, 1, seed, 11.0, "one_dollar/testB");
}

Test(one_dollar, testC) {
    // test: ten flips, still has money
    unsigned int seed = 1611076235;
    helper_simulate_game(ONE_DOLLAR, 10.0, 10, seed, 10.0, "one_dollar/testC");
}

Test(one_dollar, testD) {
    // test: stop at N bets
    unsigned int seed = 1611076235;
    helper_simulate_game(ONE_DOLLAR, 5.0, 20, seed, 1.0, "one_dollar/testD");
}

Test(one_dollar, testE) {
    // test: stop at N bets
    unsigned int seed = 1611076235;
    helper_simulate_game(ONE_DOLLAR, 5.0, 21, seed, 0.0, "one_dollar/testE");
}

Test(one_dollar, testF) {
    // test: stop at N bets
    unsigned int seed = 1611076235;
    helper_simulate_game(ONE_DOLLAR, 5.0, 22, seed, 0.0, "one_dollar/testF");
}

Test(one_dollar, testG) {
    // test: different seed
    unsigned int seed = 1611076235+1;
    helper_simulate_game(ONE_DOLLAR, 10.0, 10, seed, 18.0, "one_dollar/testG");
}


/********** Double on win tests **********/

TestSuite(double_on_win, .timeout=60);

Test(double_on_win, testA) {
    // corner case: no bets
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_WIN, 10.0, 0, seed, 10.0, "double_on_win/testA");
}

Test(double_on_win, testB) {
    // check initial bet amount
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_WIN, 10.0, 1, seed, 11.0, "double_on_win/testB");
}

Test(double_on_win, testC) {
    // double on a win (bet will be $2 in round 2)
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_WIN, 10.0, 2, seed, 9.0, "double_on_win/testC");
}

Test(double_on_win, testD) {
    // test stay fixed on loss
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_WIN, 10.0, 3, seed, 7.0, "double_on_win/testD");
}

Test(double_on_win, testE) {
    // still has cash in round 9
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_WIN, 10.0, 9, seed, 6.0, "double_on_win/testE");
}

Test(double_on_win, testF) {
    // exactly zero at round 10
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_WIN, 10.0, 10, seed, 0.0, "double_on_win/testF");
}

Test(double_on_win, testG) {
    // test stop when out of cash
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_WIN, 10.0, 11, seed, 0.0, "double_on_win/testG");
}

Test(double_on_win, testH) {
    // different amount: broke in round 4
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_WIN, 5.0, 4, seed, 0.0, "double_on_win/testH");
}

Test(double_on_win, testI) {
    // different seed, different amount
    unsigned int seed = 1611076235+1;
    helper_simulate_game(DOUBLE_ON_WIN, 15.0, 10, seed, 518.0, "double_on_win/testI");
}

Test(double_on_win, testJ) {
    // another different seed
    unsigned int seed = 1611076235+2;
    helper_simulate_game(DOUBLE_ON_WIN, 10.0, 7, seed, 0.0, "double_on_win/testJ");
}



/********** Double on loss tests **********/

TestSuite(double_on_loss, .timeout=60);

Test(double_on_loss, testA) {
    // corner case: no bets
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 10.0, 0, seed, 10.0, "double_on_loss/testA");
}

Test(double_on_loss, testB) {
    // test initial bet
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 10.0, 1, seed, 11.0, "double_on_loss/testB");
}

Test(double_on_loss, testC) {
    // test stay the same on win
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 10.0, 2, seed, 10.0, "double_on_loss/testC");
}

Test(double_on_loss, testD) {
    // double on loss
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 10.0, 3, seed, 8.0, "double_on_loss/testD");
}

Test(double_on_loss, testE) {
    // after ten bets
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 10.0, 10, seed, 12.0, "double_on_loss/testE");
}

Test(double_on_loss, testF) {
    // tests cap on bet to cash on hand
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 10.0, 5, seed, 8.0, "double_on_loss/testF");
}

Test(double_on_loss, testG) {
    // end when out of cash: part 1
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 10.0, 11, seed, 0.0, "double_on_loss/testG");
}

Test(double_on_loss, testH) {
    // end when out of cash: part 2
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 10.0, 12, seed, 0.0, "double_on_loss/testH");
}

Test(double_on_loss, testI) {
    // use different seed: still goin at 11 flips
    unsigned int seed = 1611076235+1;
    helper_simulate_game(DOUBLE_ON_LOSS, 10, 11, seed, 22.0, "double_on_loss/testI");
}

Test(double_on_loss, testJ) {
    // different starting amount
    unsigned int seed = 1611076235;
    helper_simulate_game(DOUBLE_ON_LOSS, 5.0, 10, seed, 0.0, "double_on_loss/testJ");
}


/********** fibonacci betting tests **********/

TestSuite(fib_strategy, .timeout=60);

Test(fib_strategy, testA) {
    // corner case: no bets
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 10.0, 0, seed, 10.0, "fib_strategy/testA");
}

Test(fib_strategy, testB) {
    // one bet
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 10.0, 1, seed, 11.0, "fib_strategy/testB");
}

Test(fib_strategy, testC) {
    // move along sequence on loss 1 -> 1 -> 2
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 10.0, 4, seed, 7.0, "fib_strategy/testC");
}

Test(fib_strategy, testD) {
    // move along sequence on loss 1 -> 1 -> 2 -> 3
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 10.0, 5, seed, 10.0, "fib_strategy/testD");
}

Test(fib_strategy, testE) {
    // reset to 1 on win
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 10.0, 6, seed, 11.0, "fib_strategy/testE");
}

Test(fib_strategy, testF) {
    // cap bet to cash on hand
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 5.0, 5, seed, 4.0, "fib_strategy/testF");
}

Test(fib_strategy, testG) {
    // still going after 10!
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 10.0, 10, seed, 11.0, "fib_strategy/testG");
}

Test(fib_strategy, testH) {
    // out of cash - part 1
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 5.0, 16, seed, 3.0, "fib_strategy/testH");
}

Test(fib_strategy, testI) {
    // out of cash - part 2
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 5.0, 17, seed, 0.0, "fib_strategy/testI");
}

Test(fib_strategy, testJ) {
    // out of cash - part 3
    unsigned int seed = 1611076235;
    helper_simulate_game(FIB_STRATEGY, 5.0, 18, seed, 0.0, "fib_strategy/testJ");
}

Test(fib_strategy, testK) {
    // change seed -- broke in 9th round
    unsigned int seed = 1611076235 + 2;
    helper_simulate_game(FIB_STRATEGY, 5.0, 9, seed, 0.0, "fib_strategy/testK");
}



/********** series betting tests **********/

TestSuite(series_strategy, .timeout=60);

Test(series_strategy, testA) {
    // corner case: no bets
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 10.0, 0, seed, 10.0, "series_strategy/testA");
}

Test(series_strategy, testB) {
    // initial bet
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 10.0, 1, seed, 11.0, "series_strategy/testB");
}

Test(series_strategy, testC) {
    // initial bet
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 10.0, 2, seed, 10.0, "series_strategy/testC");
}

Test(series_strategy, testD) {
    // fix betting while losing
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 10.0, 4, seed, 8.0, "series_strategy/testD");
}

Test(series_strategy, testE) {
    // reduce bet to keep series total + bet <= 1
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 10.0, 7, seed, 12.0, "series_strategy/testE");
}

Test(series_strategy, testF) {
    // start new series
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 10.0, 8, seed, 11.0, "series_strategy/testF");
}

Test(series_strategy, testG) {
    // after 10
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 10.0, 10, seed, 11.0, "series_strategy/testG");
}

Test(series_strategy, testH) {
    // out of cash part 1
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 5.0, 20, seed, 1.0, "series_strategy/testH");
}

Test(series_strategy, testI) {
    // out of cash part 2
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 5.0, 21, seed, 0.0, "series_strategy/testI");
}

Test(series_strategy, testJ) {
    // out of cash part 2
    unsigned int seed = 1611076235;
    helper_simulate_game(SERIES_STRATEGY, 5.0, 22, seed, 0.0, "series_strategy/testJ");
}

Test(series_strategy, testK) {
    // different seed.
    unsigned int seed = 1611076235+10;
    helper_simulate_game(SERIES_STRATEGY, 3.0, 6, seed, 0.0, "series_strategy/testK");
}

/* helper_simulate_game: Do the work of one of testing one strategy
 * for one game.
 *
 * strategy: which strategy to run
 * init_amount: initial amount of cash on hand (init_amount > 0)
 * num_bets: the maximum number of bets 
 * test_name - the test name to be used in error messages.
 */
void helper_simulate_multiple_games(enum betting_strategies strategy,
                                    double init_amount,
                                    int num_bets,
                                    unsigned int init_seed,
                                    int num_games,
                                    double expected,
                                    char *test_name)
{
    double actual = simulate_multiple_games(strategy, init_amount, num_bets,
                                            init_seed, num_games);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
             ("\n  Parameters used in failed test: "
              "simulate_multiple_games(%s, %f, %d, %u, %d)\n"
              "\n     Actual: %.2f"
              "\n     Expected: %.2f"
              "\n  The filter to run this specific test is: --filter %s"),
             betting_strategy_to_str(strategy), init_amount, num_bets,
             init_seed, num_games, actual, expected, test_name);

    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_float_eq(actual, expected, EPSILON, " %s", err_msg);
}

/************ Test simulate multiple games ************/

TestSuite(multiple_one_dollar, .timeout=60);

Test(multiple_one_dollar, testA) {
    // one game
    unsigned int init_seed = 1611076235;
    helper_simulate_multiple_games(ONE_DOLLAR, 10.0, 10, init_seed, 1,
                                   10.0, "multiple_one_dollar/testA");
}

Test(multiple_one_dollar, testB) {
    // small number of games
    unsigned int init_seed = 1611076235;
    int games = 3;
    helper_simulate_multiple_games(ONE_DOLLAR, 10.0, 10, init_seed, games,
                                   12.0, "multiple_one_dollar/testB");
}

Test(multiple_one_dollar, testC) {
    // larger number games
    unsigned int init_seed = 1611076235;
    int games = 100;
    helper_simulate_multiple_games(ONE_DOLLAR, 10.0, 10, init_seed, games,
                                   10.30, "multiple_one_dollar/testC");
}

Test(multiple_one_dollar, testD) {
    // different starting seed
    unsigned int init_seed = 1611076235+5;
    int games = 100;
    helper_simulate_multiple_games(ONE_DOLLAR, 10.0, 10, init_seed, games,
                                 10.28, "multiple_one_dollar/testD");
}

TestSuite(multiple_double_on_win, .timeout=60);
Test(multiple_double_on_win, testA) {
    unsigned int init_seed = 1611076235;
    helper_simulate_multiple_games(DOUBLE_ON_WIN, 10.0, 10, init_seed, 1,
                                   0.0, "multiple_double_on_win/testA");
}

Test(multiple_double_on_win, testB) {
    // small number of games
    unsigned int init_seed = 1611076235;
    int games = 3;
    helper_simulate_multiple_games(DOUBLE_ON_WIN, 10.0, 10, init_seed, games,
                                   171.0, "multiple_double_on_win/testB");
}

Test(multiple_double_on_win, testC) {
    // more games
    unsigned int init_seed = 1611076235;
    int games = 100;
    helper_simulate_multiple_games(DOUBLE_ON_WIN, 10.0, 10, init_seed, games,
                                   12.82, "multiple_double_on_win/testC");
}

Test(multiple_double_on_win, testD) {
    // different starting seed
    unsigned int init_seed = 1611076235+5;
    int games = 100;
    helper_simulate_multiple_games(DOUBLE_ON_WIN, 10.0, 10, init_seed, games,
                                   7.64, "multiple_double_on_win/testD");
}


TestSuite(multiple_double_on_loss, .timeout=60);

Test(multiple_double_on_loss, testA) {
    unsigned int init_seed = 1611076235;
    helper_simulate_multiple_games(DOUBLE_ON_LOSS, 10.0, 10, init_seed, 1,
                                   12.0, "multiple_double_on_loss/testA");
}

Test(multiple_double_on_loss, testB) {
    // small number of games
    unsigned int init_seed = 1611076235;
    int games = 3;
    helper_simulate_multiple_games(DOUBLE_ON_LOSS, 10.0, 10, init_seed, games,
                                   12.0, "multiple_double_on_loss/testB");
}

Test(multiple_double_on_loss, testC) {
    // more games
    unsigned int init_seed = 1611076235;
    int games = 100;
    helper_simulate_multiple_games(DOUBLE_ON_LOSS, 10.0, 10, init_seed, games,
                                   10.88, "multiple_double_on_loss/testC");
}

Test(multiple_double_on_loss, testD) {
    // different starting seed
    unsigned int init_seed = 1611076235+5;
    int games = 100;
    helper_simulate_multiple_games(DOUBLE_ON_LOSS, 10.0, 10, init_seed, games,
                                   10.78, "multiple_double_on_loss/testD");
}

TestSuite(multiple_fib_strategy, .timeout=60);

Test(multiple_fib_strategy, testA) {
    unsigned int init_seed = 1611076235;
    helper_simulate_multiple_games(FIB_STRATEGY, 10.0, 10, init_seed, 1,
                                   11.0, "multiple_fib_strategy/testA");
}

Test(multiple_fib_strategy, testB) {
    // small number of games
    unsigned int init_seed = 1611076235;
    int games = 3;
    helper_simulate_multiple_games(FIB_STRATEGY, 10.0, 10, init_seed, games,
                                   13.0, "multiple_fib_strategy/testB");
}

Test(multiple_fib_strategy, testC) {
    // more games
    unsigned int init_seed = 1611076235;
    int games = 100;
    helper_simulate_multiple_games(FIB_STRATEGY, 10.0, 10, init_seed, games,
                                   10.29, "multiple_fib_strategy/testC");
}

Test(multiple_fib_strategy, testD) {
    // different seed
    unsigned int init_seed = 1611076235+5;
    int games = 100;
    helper_simulate_multiple_games(FIB_STRATEGY, 10.0, 10, init_seed, games,
                                   10.25, "multiple_fib_strategy/testD");
}

TestSuite(multiple_series, .timeout=60);

Test(multiple_series_strategy, testA) {
    // one game
    unsigned int init_seed = 1611076235;
    helper_simulate_multiple_games(SERIES_STRATEGY, 10.0, 10, init_seed, 1,
                                   11.0, "multiple_series_strategy/testA");
}

Test(multiple_series_strategy, testB) {
    // small number of games
    unsigned int init_seed = 1611076235;
    int games = 3;
    helper_simulate_multiple_games(SERIES_STRATEGY, 10.0, 10, init_seed, games,
                                   12.666667, "multiple_series_strategy/testB");
}

Test(multiple_series_strategy, testC) {
    // more games
    unsigned int init_seed = 1611076235;
    int games = 100;
    helper_simulate_multiple_games(SERIES_STRATEGY, 10.0, 10, init_seed, games,
                                   10.64, "multiple_series_strategy/testC");
}

Test(multiple_series_strategy, testD) {
    // different starting seed
    unsigned int init_seed = 1611076235+5;
    int games = 100;
    helper_simulate_multiple_games(SERIES_STRATEGY, 10.0, 10, init_seed, games,
                                   10.59, "multiple_series_strategy/testD");
}

