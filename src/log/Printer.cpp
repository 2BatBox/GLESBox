#include <ctype.h>

#include "Printer.h"
#include "Log.h"

static const size_t WIDTH = 16;
static const size_t ASCII_WIDTH = 128;
static const size_t BUFFER_SIZE = 1024 * 2;

void Printer::printHexLine(const void* input, size_t offset, size_t size, size_t address, int left){
	char buffer[BUFFER_SIZE];
	size_t buffOffset = 0;
	const char* data = (const char*)input;
	buffOffset += sprintf(buffer + buffOffset, "%*s", left * 4, "");
	buffOffset += sprintf(buffer + buffOffset, "%0*lx  ", 8, offset + address);

	size_t i;
	for(i = 0 ; i < WIDTH ; i++){

		if(i > 0 && i % 8 == 0){
			buffOffset += sprintf(buffer + buffOffset, " ");
		}

		if(i < size){
			buffOffset += sprintf(buffer + buffOffset, "%02x ", data[i] & 0xFF);
		} else {
			buffOffset += sprintf(buffer + buffOffset, "   ");
		}
	}

	buffOffset += sprintf(buffer + buffOffset, " |");

	for(i = 0 ; i < size ; i++){
		if(!iscntrl(data[i]))
			buffOffset += sprintf(buffer + buffOffset, "%c", data[i]);
		else
			buffOffset += sprintf(buffer + buffOffset, ".");
	}

	buffOffset += sprintf(buffer + buffOffset, "|");
	LOGI("%s", buffer);
}

void Printer::hexDump(const void* input, size_t size, size_t address,  int left){
	const char* data = (const char*)input;
	size_t i;
	size_t max;
	for(i = 0; i < size; i += WIDTH){
		max = size - i;
		if(max > WIDTH)
			max = WIDTH;
		printHexLine(data + i, i, max, address, left);
	}
}

void Printer::asciiDump(const void* input, size_t size, int left){
	const char* data = (const char*)input;
	size_t i;
	size_t max;
	for(i = 0; i < size; i += ASCII_WIDTH){
		max = size - i;
		if(max > ASCII_WIDTH)
			max = ASCII_WIDTH;
		LOGI("[%.*s]", (int)max, data + i);
	}
}


