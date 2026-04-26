#include <stdio.h>
#include <stdlib.h>
#include "include/class_with_main.hpp"

int add_two_numbers(int a, int b) {
    return a+b;
}

#ifndef __TEST__
int main() {
    printf("%d", add_two_numbers(1,1));
    return 0;
}
#endif