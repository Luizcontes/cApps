#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int yes_no(char* question) {


    char answer[3];

    while (1) {
        printf("%s? (y/n): ", question);
        fgets(answer, 3, stdin);
        if (answer[0] != 'n')
            if (answer[0] == 'y') {
                printf("yes\n");
                break;
            }
        if (answer[0] != 'y')
            if (answer[0] == 'n') {
                printf("no\n");
                break;
            }
        question = "Insert the right answer";
    }

    return answer[0] == 'y';
}

int main() {

    /*
    if (yes_no("A ordem do y/n, faz diferenca?")) {

        printf("\nyes\n\n");

    }
    */


    while (yes_no("Run again")) {
        //printf("\nof couse...\n");
    }


    return 0;
}