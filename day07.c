/*
 * AoC 2022 - Day 07
 * 
 * Input: A terminal recording of a file system traversal using cd and ls,
 *        with file sizes.
 * Part 1: Find the total size of all directories which contain less that
 *         100_000 bytes of data, each. Nested directories count multiple times.
 * Part 2: Find the directory that, when deleted, frees just enough space to
 *         have 30_000_000 bytes left. Total is 70_000_000.
 *
 * Solutions (c) Turysaz
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LISTLEN 250

struct directory {
    char name[32];
    unsigned long size;
};

typedef struct directory_list {
    int length;
    struct directory entries[LISTLEN];
} dir_list;

long get_dir_sizes(dir_list *list, unsigned long * const total_used) {
    char linebuffer[64],
         namebuf[32];
    unsigned long filesize, dirsize = 0;;
    struct directory *dir;

    while(fgets(linebuffer, sizeof(linebuffer)-1, stdin) != NULL) {
        if (strncmp("$ cd ..\n", linebuffer, 8) == 0) break;
        if (sscanf(linebuffer, "$ cd %31s", namebuf) > 0) {
            filesize = get_dir_sizes(list, total_used);

            /* Add completed directory to list */
            dir = &(list->entries[list->length++]);
            dir->size = filesize;
            memcpy(dir->name, namebuf, 32);

            dirsize += filesize;
            continue;
        }

        if (sscanf(linebuffer, "%lu %31s", &filesize, namebuf) > 0) {
            dirsize += filesize;
            *total_used += filesize;
            continue;
        }

        if (strncmp("$ ls\n", linebuffer, 5) == 0) continue;
        if (strncmp("dir ", linebuffer, 4) == 0) continue;
        fprintf(stderr, "Invalid line: %s\n", linebuffer);
    }

    return dirsize;
}

int main(int argc, char **argv) {
    dir_list list = { .length = 0 };
    int i;
    unsigned long
        part1_total = 0,
        total_used = 0,
        /* Assume the need to delete the entire 30M to start with*/
        for_deletion=30000000,
        missing_space,
        l;

    get_dir_sizes(&list, &total_used);
    missing_space = total_used - 40000000; /* max allowed used space */

    for (i = 0; i<list.length; i++) {
        l = list.entries[i].size;
        if (l <= 100000) {
            part1_total += l;
        }

        /* Check if overshoot would be better for this directory */
        if (l - missing_space < for_deletion - missing_space) {
            for_deletion = l;
        }
    }

    printf("Part 1: %lu\n", part1_total);
    printf("Part 2: %lu\n", for_deletion);
}

