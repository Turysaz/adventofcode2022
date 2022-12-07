/*
 * AoC 2022 - Day 05
 * 
 * Input: A map of stacks. Instructions to move items from one stack to another.
 * Part 1: What are the topmost items on all stacks? Instructions move one item
 *         at a time -> invert order.
 * Part 2: What are the topmost items on all stacks? Instructions move entire sub
 *         stacks -> keep order.
 *
 * Solutions (c) Turysaz
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 40

typedef struct stentry_t stentry_t;

typedef struct stentry_t {
    char value;
    stentry_t *next;
} stentry_t;

typedef struct stack_t {
    stentry_t *head;
} stack_t;

void stack_init(stack_t * const s) {
    s->head = NULL;
}

void stack_push(stack_t * const s, const char c) {
    stentry_t *e;

    if ((e = malloc(sizeof(stentry_t))) == NULL) {
        fprintf(stderr, "Malloc err\n");
        exit(-1);
    }

    e->next = s->head;
    e->value = c;
    s->head = e;
}

/* CAUTION: returns 0 on empty stack! */
char stack_peek(const stack_t * const s) {
    if (!s->head) return 0;
    return s->head->value;
}

/* CAUTION: returns 0 on empty stack! */
char stack_pop(stack_t * const s) {
    stentry_t *e;
    char c;

    e = s->head;
    if (!e) return 0;
    c = e->value;
    s->head = e->next;
    free(e);
    return c;
}

void stack_invert(stack_t * const s) {
    stack_t copy;
    char c;

    stack_init(&copy);
    while((c = stack_pop(s)) != 0) {
        stack_push(&copy, c);
    }
    s->head = copy.head;
}

void stack_clear(stack_t * const s) {
    while(stack_pop(s) != 0) { }
}

void stack_transfer(stack_t * const src, stack_t * const trg, int n) {
    stentry_t *cursor, *memo;
    int i;

    cursor = src->head;
    for (i = 1; i < n; i++) {
        cursor = cursor->next;
    }

    memo = cursor->next;
    cursor->next = trg->head;
    trg->head = src->head;
    src->head = memo;
}

int main(int argc, char **argv) {
    char buffer[BUFSIZE];
    int i;
    char c;
    stack_t stacks_1[9], stacks_2[9];
    int src, cnt, trg;

    /* init */
    memset(&buffer, 0, sizeof(buffer));
    for (i = 0; i < 9; i++) {
        stack_init(&stacks_1[i]);
        stack_init(&stacks_2[i]);
    }

    /* Read stack map */
    while(fgets(buffer, BUFSIZE-1, stdin) != NULL) {
        if (buffer[1] == '1') continue;
        if (buffer[0] == '\n') break;

        for (i = 0; i < 9; i++) {
            c = buffer[1+i*4]; /* calculate stack column in input */
            if (c == ' ' || c == 0) continue;
            stack_push(&stacks_1[i], c);
            stack_push(&stacks_2[i], c);
        }
    }

    /* flip stacks over after reading them top-to-bottom. */
    for (i = 0; i < 9; i++) {
        stack_invert(&stacks_1[i]);
        stack_invert(&stacks_2[i]);
    }
 
    /* Perfom instructions */
    while (scanf("move %i from %i to %i\n", &cnt, &src, &trg) != EOF) {
        /* Part 1 */
        for (i = 0; i < cnt; i++) {
            c = stack_pop(&stacks_1[src-1]);
            if (c == 0) break;
            stack_push(&stacks_1[trg-1], c);
        }

        /* Part 2 */
        stack_transfer(&stacks_2[src-1], &stacks_2[trg-1], cnt);
    }

    /* Print results */
    printf("Part 1: ");
    for (i = 0; i < 9; i++) {
        c = stack_peek(&stacks_1[i]);
        printf("%c", c == 0 ? '/' : c);
    }
    printf("\nPart 2: ");
    for (i = 0; i < 9; i++) {
        c = stack_peek(&stacks_2[i]);
        printf("%c", c == 0 ? '/' : c);
    }
    printf("\n");

    /* Cleanup */
    for (i = 0; i < 9; i++) {
        stack_clear(&stacks_1[i]);
        stack_clear(&stacks_2[i]);
    }
}

