/*
 * AoC 2022 - Day 01
 * 
 * Input: A list of number sets.
 * Part 1: Find the number set which's sum is the greatest.
 * Part 2: Find the three number sets which's sum over all three is the
 *         greatest.
 *
 * Solutions (c) Turysaz
 */

#include <stdlib.h>
#include <stdio.h>

/**
 * Sorts an array.
 *
 * /param arr pointer to three-element array that is to be sorted.
 */
static void sort3(int *arr) {
    int buf;
    if (arr[0] < arr[1]) {
        buf = arr[0];
        arr[0] = arr[1];
        arr[1] = buf;
    }
    if (arr[1] < arr[2]) {
        buf = arr[1];
        arr[1] = arr[2];
        arr[2] = buf;
    }
    if (arr[0] < arr[1]) {
        buf = arr[0];
        arr[0] = arr[1];
        arr[1] = buf;
    }
}

int main(int argc, char **argv) {
    int current = 0;
    int max[] = {0, 0, 0};
    char buffer[10];

    while (fgets(buffer, sizeof(buffer)-1, stdin) != NULL) {
        if (buffer[0] == '\n') {
            max[2] = current > max[2] ? current : max[2];
            sort3(max);
            current = 0;
            continue;
        }
        current += atoi(buffer);
    }

    printf("Part 1: %i\n", max[0]);
    printf("Part 2: %i\n", max[0] + max[1] + max[2]);
}

