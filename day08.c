/*
 * AoC 2022 - Day 08
 * 
 * Input: A map of tree heights in a forest.
 * Part 1: Find the amount of trees that are visible (not outtermost or
 *         blocked by a higher tree).
 * Part 2: Find the tree the most trees are visible from.
 *
 * Solutions (c) Turysaz
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIDELEN 99

enum direction {
    RIGHT = 0,
    UP,
    LEFT,
    DOWN
};

/* Gets the absolute coords of a point defined by a line and a
 * depth when looking at the grid from a certain direction. */
void get_coords(
        const int line,
        const int depth,
        const int efflen,
        const enum direction t,
        int * const x,
        int * const y) {
    switch(t) {
    case RIGHT:
        *x = depth;
        *y = line;
        break;
    case DOWN:
        *x = line;
        *y = depth;
        break;
    case LEFT:
        *x = efflen - depth - 1;
        *y = line;
        break;
    case UP:
        *x = line;
        *y = efflen - depth - 1;
        break;
    }
}

/* Gets the absolute coords of a point offset defined 
 * by direction and distance. */
void get_rel_pos(
        const int x,
        const int y,
        const enum direction t,
        const int dist,
        int * const x1,
        int * const y1) {
    switch(t) {
    case LEFT:
        *x1 = x - dist;
        *y1 = y;
        break;
    case DOWN:
        *x1 = x;
        *y1 = y + dist;
        break;
    case RIGHT:
        *x1 = x + dist;
        *y1 = y;
        break;
    case UP:
        *x1 = x;
        *y1 = y - dist;
        break;
    }
}


/* returns effective side length */
int parse_map(char map[SIDELEN][SIDELEN]) {
    int x = 0, y = 0;
    char c;

    while((c = getc(stdin)) != EOF) {
        if (c != '\n') {
            map[x++][y] = c - 0x30; /* '0' == 0x30 */
            continue;
        }
        x = 0;
        y++;
    }
    return y;
}

void calculate_vmap(
        char grid[SIDELEN][SIDELEN],
        char vmap[SIDELEN][SIDELEN],
        const int efflen) {
    char cur, max;
    int line, /* the currently inspected row/column*/
        depth, /* the depth "into" the currently inspected line */
        x, y, d;

    for (d = 0; d < 4; d++) {
        for (line = 0; line < efflen; line++) {
            max = -1; /* the first tree (on the edge) is always
                       * visible and might be 0 */
            for (depth = 0; depth < efflen; depth++) {
                get_coords(line, depth, efflen, (enum direction)d, &x, &y);
                cur = grid[x][y];

                if (cur > max) {
                    vmap[x][y] = 1;
                    max = cur;
                }
            }
        }
    }
}

void calculate_smap(
        char grid[SIDELEN][SIDELEN],
        unsigned int smap[SIDELEN][SIDELEN],
        const int efflen) {
    int x, y,   /* current tree position */
        x1, y1, /* neigbour tree position */
        d, i,   /* direction and steps into it*/
        treecnt,/* count of trees in the current direction */
        score;  /* current tree score */

    /* iterate all trees */
    for (x = 0; x < efflen; x++) {
        for (y = 0; y < efflen; y++) {
            score = 1;
            /* look in all four directions */
            for (d = 0; d < 4; d++) {
                treecnt = 0;
                for (i = 1; i < efflen; i++) {
                    get_rel_pos(x, y, (enum direction)d, i, &x1, &y1);
                    if (x1 < 0 || y1 < 0 || x1 >= efflen || y1 >= efflen) {
                        break;
                    }
                    treecnt++;
                    if (grid[x1][y1] >= grid[x][y]) break;
                }
                score *= treecnt;
                if (score == 0) break;
            }
            smap[x][y] = score;
        }
    }
}
 
int main (int argc, char **argv) {
    char grid[SIDELEN][SIDELEN];
    char vmap[SIDELEN][SIDELEN]; /* visibility map */
    unsigned int smap[SIDELEN][SIDELEN]; /* score map */
    int efflen;
    int x, y;
    int treecount = 0, max_score = 0;

    /* init */
    memset(vmap, 0, sizeof(vmap));
    memset(smap, 0, sizeof(smap));

    efflen = parse_map(grid);

    calculate_vmap(grid, vmap, efflen);
    calculate_smap(grid, smap, efflen);

    for (y = 0; y < efflen; y++) {
        for (x = 0; x < efflen; x++) {
            treecount += vmap[x][y];
            max_score = smap[x][y] > max_score ? smap[x][y] : max_score;
        }
    }

    printf("Part 1: %i\n", treecount);
    printf("Part 2: %i\n", max_score);
}

