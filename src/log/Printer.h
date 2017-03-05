#ifndef PRINTER_H_
#define PRINTER_H_

#include <stdio.h>

namespace Printer {

void printHexLine(const void* input, size_t offset, size_t size, size_t address, int left);
void hexDump(const void* input, size_t size, size_t address = 0, int left = 0);
void asciiDump(const void* input, size_t size, int left = 0);

template<typename T>
void printBits(T value) {
	size_t bits = sizeof(value) * 8;
	T mask = 1 << (bits - 1);
	while (bits--) {
		printf("%d", (value & mask) ? 1 : 0);
		value = value << 1;
		if(bits % 8 == 0){
			printf(" ");
		}
	}
	printf("\n");
}

}

#endif /* PRINTER_H_ */
