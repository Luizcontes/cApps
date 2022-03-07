#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum response_type { DUMP, SECOND_CHANCE, MARRIAGE };
typedef struct {
    char* name;
    enum response_type type;
} response;

void dump(response r) {

    printf("Dear %s,\n", r.name);
    puts("Unfortunately your last date contacted us to");
    puts("say that they will not be seeing you gain.\n");
}

void second_chance(response r) {

    printf("Dear %s,\n", r.name);
    puts("Good news: your last date has asked us to");
    puts("arrange another meeting. Please call ASAP.\n");
}

void marriage(response r) {

    printf("Dear %s,\n", r.name);
    puts("Congratulations! Your last date has contacted");
    puts("us with a proposal of marriage.\n");
}

void (*replies[])(response) = {dump, second_chance, marriage};

void main() {

    response r[] = {
        {"Mike", DUMP}, {"Luis", SECOND_CHANCE},
        {"Matt", SECOND_CHANCE}, {"William", MARRIAGE}
    };
    for (int i = 0; i < 4; i++) {
        (replies[r[i].type])(r[i]);
        /*
        switch (r[i].type) {
        case DUMP:
            dump(r[i]);
            break;
        case SECOND_CHANCE:
            second_chance(r[i]);
            break;
        default:
            marriage(r[i]);
        }
        */
    }
}

