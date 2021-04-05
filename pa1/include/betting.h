/*** DO NOT CHANGE THIS FILE ***/

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
                     int num_bets, unsigned int seed);

/* simulate_game: simulate multiple games
 *
 * strategy: the betting strategy to use
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * init_seed: initial value used for the seed
 * num_games: the number of games to simulate
 *
 * Returns: average amount of cash on hand at the end of the simulated
 *    games as a double
 */
double simulate_multiple_games(enum betting_strategies strategy, double init_amount,
                               int num_bets, unsigned int init_seed, int num_games);

