#include "gpio.h"

int main()
{
	//GPIOUnexport(31);
	//GPIOUnexport(14);
	if (GPIOExport(31) != -1) {
		printf("Starting set direction\n");
		GPIODirection(31, OUT);
	}
	if (GPIOExport(14) != -1) {
		printf("Starting set direction\n");
		GPIODirection(14, IN);
	}
	GPIOButton(31, 14);
	return 0;
}
