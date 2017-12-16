#include <iostream>

#include "TraceR.h"

int main(int argc, char* argv[])
{
	TraceR tracer(1920, 1080, 256);
	tracer.render();

	return 0;
}
