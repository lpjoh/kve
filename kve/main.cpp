#include "TestEngine.h"

int main() {
	kve::TestEngine engine{};
	
	if (!engine.Start()) {
		return -1;
	}

	return 0;
}