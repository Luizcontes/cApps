#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
void print_ints(int args, ...) {

    va_list ap;
    va_start(ap, args);

    int i;
    for (i = 0; i <args; i++) {
        printf("argument: %i\n", va_arg(ap, int));
    }
    va_end(ap);
}
*/

enum drink {
    MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE
};

double total(int args, ...) {

    double total = 0;
    va_list ap;
    va_start(ap, args);
    int i;
    for (i = 0; i < args; i++) {
        enum drink d = va_arg(ap, enum drink);
        total = total + price(d);
    }
    va_end(ap);
}

void main() {
    printf("Price is %.2f\n", total(2, MONKEY_GLAND, MUDSLIDE));

}
