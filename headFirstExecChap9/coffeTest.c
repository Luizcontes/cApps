#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    char* my_env[] = { "FOOD=coffe", NULL };
    if (execle("./home/luizcontes/Programming/cApps/build/coffe", "./home/luizcontes/Programming/cApps/build/coffe", "donuts", NULL, my_env) == -1) {
        fprintf(stderr, "Can`t run process 0: %s\n", strerror(errno));

        return 1;
    }
    return 0;
}
https://www.nasdaq.com/feed/rssoutbound?category=Blockchain