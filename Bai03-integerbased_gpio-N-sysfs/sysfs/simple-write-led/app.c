#include "gpio.h"

int main()
{
	GPIOExport(31);
	GPIODirection(31, OUT);
	GPIOWrite(31, HIGH);
	return 0;
}
