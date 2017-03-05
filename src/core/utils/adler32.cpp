#include "adler32.h"

void core::adler32Append(void* buf, size_t buflength, Adler32& state) {
	uint8_t* in_buf = (uint8_t*)buf;
	for (size_t n = 0; n < buflength; n++){
		state.s0 = (state.s0 + in_buf[n]) % 65521;
		state.s1 = (state.s1 + state.s0) % 65521;
	}
}
