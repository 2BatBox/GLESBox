#ifndef CORE_UTILS_ADLER32_H_
#define CORE_UTILS_ADLER32_H_

#include <stdlib.h>
#include <stdint.h>

namespace core {

struct Adler32 {
	uint32_t s0;
	uint32_t s1;
	Adler32() : s0(1), s1(0) {}
	uint32_t result(){
		return (s1 << 16) + s0;
	}
};

void adler32Append(void* buf, size_t buflength, Adler32& state);

};

#endif /* CORE_UTILS_ADLER32_H_ */
