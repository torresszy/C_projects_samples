#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>

#include "util.h"
#include "betting.h"

/* flip_coin: flip a fair coin
 *
 * Returns: true for heads/win, false for tails/loss.
 */
bool flip_coin()
{
     return (rand() % 2 == 1);
}


/* flip_only: sample use of the coin flipping function - prints the
 *   coin flips.
 *
 * inital_amount: initial cash on hand
 * num_flips: number of flips to do.
 *
 * Returns: initial amount to simplify testing framework.
 */
double flip_only(double initial_amount, int num_bets)
{
     printf("\n");
     for (int b = 1; b <= num_bets; b++) {
         bool toss = flip_coin();
         printf("%d, %s\n", b, (toss ? "WIN" : "LOSS"));
     }
     return initial_amount;
}

/* betting_strategy_to_str - convert enumerated type value 
 * to a string
 *
 * strategy -- the betting strategy to convert to a string
 *
 * Returns: string
 */
  
char *betting_strategy_to_str(enum betting_strategies strategy)
{
    // This task could also be done with a switch statement.

    if (strategy == ONE_DOLLAR) {
        return "ONE_DOLLAR";
    } else if (strategy == DOUBLE_ON_WIN) {
        return "DOUBLE_ON_WIN";
    } else if (strategy == DOUBLE_ON_LOSS) {
        return "DOUBLE_ON_LOSS";
    } else if (strategy == FIB_STRATEGY) {
        return "FIB_STRATEGY";
    } else if (strategy == SERIES_STRATEGY) {
        return "SERIES_STRATEGY";
    } else if (strategy == FLIP_ONLY) {
        return "FLIP_ONLY";
    } else {
        fprintf(stderr, "Unexpectedly hit else in betting strategy to str\n");
        exit(0);
    }
}
