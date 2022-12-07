/*
 * AoC 2022 - Day 02
 * 
 * Input: A list of [ABC] [XYZ] character pairs.
 * Part 1: Calculate a score over all pairs.
 *         Each pair represents a rock-paper-scissors-match.
 *         {A,X} - Rock
 *         {B,Y} - Paper
 *         {C,Z} - Scissors
 *         Score = {X:1,Y:2,Z:2} + {0:abc-side-win,3:draw,6:xyz-side-win}
 * Part 2: The second colum indicates the required outcome.
 *         X - Loose
 *         Y - Draw
 *         Z - Win
 *         Calculate the required action to get the outcome and then
 *         calculate the score as before.
 *
 * Solutions (c) Turysaz
 */

#include <stdlib.h>
#include <stdio.h>

static int outcome_score(const char own, const char other) {
    /* Explanation:
     * (own-'X') and (other-'A') calculate the numeric value
     * of the action: Rock:0, Paper:1, Scissors:2.
     * Adding 4 and getting mod3 of it all gives a value
     * indicating the outcome:
     * loose:0, draw:1, win:2.
     * 
     * Multiply with 3 for the desired scoring.
     * Determined the formular by working it out on paper. :)
     */
    return ((((own - 'X') - (other - 'A')) + 4) % 3) * 3;
}

int main(int argc, char **argv) {
    int ret;
    char left, right, required;
    int score1 = 0,
        score2 = 0;

    while ((ret = scanf("%c %c\n", &left, &right) != EOF)) {
        /* part 1 */
        score1 += (right - 'X') + 1 + outcome_score(right, left);

        /* part 2*/

        /* Explanation:
         * Take the left side and shift it "clockwise" or "ccw":
         * Loose:-1, Draw:0, Win:+1.
         * Then do (..+3)%3 to get rid of negative values.
         */
        required = (left - 'A') + (right - 'X' - 1) + 3;
        required %= 3;
        score2 += required + 1 + (right - 'X') * 3;
    }

    printf("Part 1: %i\n", score1);
    printf("Part 2: %i\n", score2);
}

