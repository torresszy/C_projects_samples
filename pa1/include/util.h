/*** DO NOT CHANGE THIS FILE ***/

/* Type used to represent betting strategies */
enum betting_strategies {ONE_DOLLAR,
                         DOUBLE_ON_WIN,
                         DOUBLE_ON_LOSS,
                         FIB_STRATEGY,
                         SERIES_STRATEGY,
                         FLIP_ONLY};

/* betting_strategy_to_str - convert enumerated type value 
 * to a string
 *
 * strategy -- the strategy to convert
 *
 * Returns: string
 */
  
char *betting_strategy_to_str(enum betting_strategies strategy);


/* flip_coin: flip a fair coin
 *
 * Returns: true for heads/win, false for tails/loss.
 */
bool flip_coin();

/* flip_only: sample use of the coin flipping function - prints the
 *   coin flips.
 *
 * inital_amount: initial cash on hand
 * num_flips: number of flips to do.
 *
 * Returns: initial amount to simplify testing framework.
 */

double flip_only(double initial_amount, int num_bets);


