#include "LogManager.h"
#include <assert.h>

int main(void) {
	int res = LM.startUp();
	assert(res == 0);

	LM.shutDown();
	return 0;
}