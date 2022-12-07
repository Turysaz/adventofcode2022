/*
 * AoC 2022 - Day 06
 * 
 * Input: A stream of characters.
 * Part 1: Find the index of the first character after a set of 4 unique
 *         characters occurred.
 * Part 2: The same, but for 14 unique characters.
 *
 * Remarks:
 * The solution uses a 64bit integer as a bit field to track each character
 * in a 4 (respective, 14) byte sized array.
 * The uniqueness is then checked by counting the set bits in the field.
 * This is the so-called Hamming Weight, or "popcount". x86 has a popcount
 * instruction, that is calling using GCCs builtin function for it.
 *
 * Solutions (c) Turysaz
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int marker_detected(char buf[], int size) {
    uint64_t map = 0;
    int i;

    for (i = 0; i < size; i++) {
        if (buf[i] == 0) continue;
        map |= (uint64_t)1 << (buf[i] - 0x60); /*0x60: shift into relevant ascii range */
    }
    
    /* For int, there is also __builtin_popcount(i) .*/
    if (__builtin_popcountll(map) == size) return 1;

    return 0;
}

int main(int argc, char **argv) {
    char c;
    char buffer_1[4]; /* ring buffers for part 1 and 2. */
    char buffer_2[14];
    int i;
    bool p1_solved = false, p2_solved = false;

    memset(buffer_1, 0, sizeof(buffer_1));
    memset(buffer_2, 0, sizeof(buffer_2));

    while((c = getc(stdin)) != EOF) {
        buffer_1[(i) % 4] = c;
        buffer_2[(i++) % 14] = c;
        if (!p1_solved && marker_detected(buffer_1, 4)) {
            printf("Part 1: %i\n", i);
            p1_solved = true;
        }
        if (!p2_solved && marker_detected(buffer_2, 14)) {
            printf("Part 2: %i\n", i);
            p2_solved = true;
        }
        if (p1_solved && p2_solved) break;
     }

    return 0;
}

