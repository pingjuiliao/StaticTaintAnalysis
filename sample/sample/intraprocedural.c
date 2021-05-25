#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned lock ; 

void
test_random(void) {
    int x, y, z ;
    x = rand() % 6 ;
    if ( x % 2 ) {
        y = x; 
    } else {
        z = 0; 
    }
}

void
test_lock(void) {
    unsigned a, b ;
    if ( lock ) {
        a = 0 ;
    } else {
        a = 1 ; 
    }
    b = 17 ;
}

int
main(int argc, char** argv) {
    
    test_random() ;
    test_lock() ;


    return 0;
}
