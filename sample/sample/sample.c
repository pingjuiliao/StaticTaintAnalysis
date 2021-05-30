#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int WORLD = 10;
int LOCK = 0;

int
this_contains_if_statements(void) {
    int random_number = rand();

    if (random_number % 2 == 0) {
        return 0;
    } else {
        return 1;
    }
}

int
this_contains_switch_case(void) {
    int random_number = rand();

    switch (random_number % 5) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        default:
            return -1;
    }
}

void
this_access_global_data(void) {
    WORLD = 100;
}

int
lock() {
    if (LOCK==0) {
        LOCK = 1;
        return 0;
    } else {
        return -1;
    }
}

int
unlock() {
    if (LOCK==1) {
        LOCK = 0;
        return 0;
    }
    else {
        return -1;
    }
}

void
this_uses_lock(void) {
    while (1) {
        if (lock()) {
            WORLD = 200;
            unlock();
            break;
        }
    }
}

int GLOBAL_A = 0 ;
int GLOBAL_B = 0 ;
void 
this_propagate_a_global(void) {
    int r = WORLD  ;
    switch(r) {
        case 1:
            GLOBAL_A = 1 ;
            break ;
        case 2:
            r += 1;
            break;
        case 3:
            r -= 1;
            break;
        default:
            break;
    }
}

void
this_propagate_another_global(void) {
    int r = GLOBAL_A ;
    switch(r) {
        case 1 :
            r -= 1 ;
            break;
        case 2 :
            GLOBAL_B = 1 ;
            break ;
        default:
            break ;
    }
}

void
this_uses_a_propagated_global(void) {
    int i ;
    if (GLOBAL_A) {
        i = 0 ;
    } else {
        i = 1 ;
    }
}

int
main() {
    int a, b, c;
    srand((unsigned int)time(NULL));
    a = this_contains_if_statements();
    b = this_contains_switch_case();
    this_access_global_data();
    this_uses_lock();
    printf("%d, %d, %d\n", a, b, WORLD);
}
