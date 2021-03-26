#include "utility.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	std::string s;
	
	s = df::toString(0);
	assert(s == "0");

	s = df::toString(1);
	assert(s == "1");

	s = df::toString(-1);
	assert(s == "-1");

	s = df::toString(12345678);
	assert(s == "12345678");

	s = df::toString(-12345678);
	assert(s == "-12345678");

	printf("Test done.\n");

	return 0;
}