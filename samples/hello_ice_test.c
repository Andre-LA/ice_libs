/* Define the implementation of the library and include it */
#define ICE_TEST_IMPL 1
#include "ice_test.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

/* Create a Test */
ICE_TEST_CREATE_EX(test1) {
    ICE_TEST_ASSERT_TRUE(sizeof(void*) == 8);
}

int main(int argc, char **argv) {
    trace("main", "Testing if program is 64-bit...");
    test1(argc, argv); /* test! */
    trace("main", "TEST SUCCESS!");

    return 0;
}