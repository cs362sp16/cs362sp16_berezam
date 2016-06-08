#include "myassert.h"
#include <stdio.h>

int myassert(int b, char* msg, int failed) {
	if (b == 0) {
		printf("FAILED ASSERTION: %s.\n", msg);
		failed = 1;
	}
	
	return failed;
}

void checkasserts(int failed) {
	if (!failed) {
		printf ("TEST SUCCESSFULLY COMPLETED.\n");
	}
}