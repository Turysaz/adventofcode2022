/*
 * AoC 2022 - Day 04
 * 
 * Input: A list of range pairs.
 * Part 1: Find the amount of pairs where one range is entirely included
 *         in the other.
 * Part 2: Find the number of pairs that overlap.
 *
 * Solutions (c) Turysaz
 */

#include <stdlib.h>
#include <stdio.h>

int is_included(const int a1, const int a2, const int b1, const int b2) {
    return (a1 >= b1 && a2 <= b2) || (b1 >= a1 && b2 <= a2);
}

int overlaps(const int a1, const int a2, const int b1, const int b2) {
    return (a1 <= b1 && a2 >= b1) || (b1 <= a1 && b2 >= a1);
}

int main(int argc, char **argv) {
    int a1, a2, b1, b2;
    int total1 = 0, total2 = 0;

    while (scanf("%i-%i,%i-%i\n", &a1, &a2, &b1, &b2) != EOF) {
        total1 += is_included(a1, a2, b1, b2);
        total2 += is_included(a1, a2, b1, b2) | overlaps(a1, a2, b1, b2);
    }

    printf("Part 1: %i\n", total1);
    printf("Part 2: %i\n", total2);
}

