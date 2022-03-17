#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {

    char letters[] = { 'C', 'A', 'B' };
    char* ptLetters[3];
    char** ptPtLetters[3];

    for (int i = 0; i < strlen(letters); i++)
        ptLetters[i] = &letters[i];

    while (1) {

        int i = 0;
        while (1) {
            
            if (ptLetters[i+1] == '\0')
                break;
            else {
                if (*ptLetters[i] > *ptLetters[i+1]) {
                    ptPtLetters[i] = &ptLetters[i+1];
                    ptPtLetters[i+1] = &ptLetters[i];
                }
            }
            i++;
        }
        break;
    }

    
    for(int i = 0; i < 3; i++) {
        printf("%c\n", **ptPtLetters[i]);
    }
    
}