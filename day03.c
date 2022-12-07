/*
 * AoC 2022 - Day 03
 * 
 * Input: Lists of characters
 * Part 1: Find the single character, that occurs both in the first
 *         and the second half of each list.
 *         Get the total sum of all character indices of these chars.
 * Part 2: Get the single character, that occurs within each group of
 *         three succeeding lists.
 *         Get the total sum again.
 *
 * Solutions (c) Turysaz
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int get_priority(const char c) {
    if (c > 0x60) return c - 0x60; /* lower case */
    return c - 0x40 + 26; /* upper case */
}

int get_bit_index(const uint64_t map) {
    int i = 0;
    while (map >> i++ != 1);
    return i - 1;
}

int main(int argc, char **argv) {
    uint64_t map_l, map_r, mask, map_group = 0xFFFFFFFFFFFFFFFF;
    int total_1 = 0,
        total_2 = 0;
    char buffer[53]; /* 52 + \0 */
    size_t len;
    char c;
    int i, group_counter = 0;

    while (fgets(buffer, 52, stdin) != NULL) {
        map_l = map_r = mask = 0; /* init */
        len = strnlen(buffer, 52);

        for (i = 0; i < 52; i++) { /* iterate over string */
            if ((c = buffer[i]) == 0 || c == '\n') break;

            mask = (uint64_t)1 << get_priority(c);

            if (i < len/2) {
                map_l |= mask;
            } else {
                map_r |= mask;
            }
        }

        /* BEGIN part 2 */
        map_group &= map_l | map_r; /* get total map for elf */
        if (++group_counter == 3) {
            total_2 += get_bit_index(map_group);
            /* reset */
            map_group = 0xFFFFFFFFFFFFFFFF;
            group_counter = 0;
        }
        /* END part 2 */

        map_l &= map_r;
        total_1 += get_bit_index(map_l);
    }

    printf("Part 1: %i\n", total_1);
    printf("Part 2: %i\n", total_2);
}

