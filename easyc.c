#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h> // clock

#include "easyc.h"



int main(int argc, char* argv[])
{
	startEC;

	atexit(garbageCollector);
	printf("argc : %d argv[] : %s\n",argc, argv[1]);



	return 0;
}






