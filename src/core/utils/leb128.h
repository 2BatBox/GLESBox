#ifndef CORE_UTILS_LEB128_H_
#define CORE_UTILS_LEB128_H_

#include <stdint.h>

namespace core {

	/*
	*	Write 32-bit unsigned int as uleb128.
	*	Return : bytes in stream.
	*/
	unsigned writeUleb(uint32_t value, void* buffer);

	/*
	*	Write 32-bit signed int as sleb128.
	*	Return : bytes in stream.
	*/
//	unsigned writeSleb(int32_t value, void* buffer); //todo: there is a bug with read/write signed value

	/*
	*	Read 32-bit unsigned int from uleb128 stream.
	*	Return : bytes in stream.
	*/
	unsigned readUleb(uint32_t& value, const void* buffer);

	/*
	*	Read 32-bit signed int from sleb128 stream.
	*	Return : bytes in stream.
	*/
//	unsigned readSleb(int32_t& value, const void* buffer); //todo: there is a bug with read/write signed value

	/*
	*	Calculate size of 32-bit unsigned int as uleb128.
	*	Return : bytes in stream.
	*/
	unsigned testUleb(uint32_t value);

	/*
	*	Calculate size of 32-bit signed int as sleb128.
	*	Return : bytes in stream.
	*/
//	unsigned testSleb(int32_t value); //todo: there is a bug with read/write signed value

	/*
	*	Arithmetic right shift.
	*/
	void arshr(int32_t& v, uint8_t shift);

};

#endif /* CORE_UTILS_LEB128_H_ */
