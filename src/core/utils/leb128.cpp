#include "leb128.h"

unsigned core::writeUleb(uint32_t value, void* buffer) {
	uint8_t* stream = (uint8_t*) buffer;
	do {
		*stream = value & ~(~0u << 7);
		value >>= 7;
		if(value){
			*stream |= 1u << 7;
		}
		stream++;
	} while(value);
	return stream - (uint8_t*)buffer;
}

//unsigned core::writeSleb(int32_t value, void* buffer) {
//	uint8_t* stream = (uint8_t*) buffer;
//	int32_t test = 0;
//	uint8_t is_last = 0;
//	do {
//		test = value;
//		arshr(test, 6);
//		is_last = (test == 0 || ~test == 0);
//		if(is_last){
//			*stream = value & ~(~0u << 6);
//			arshr(value, 6);
//			*stream |= (1u << 6) & value;
//		} else {
//			*stream = value & ~(~0u << 7);
//			*stream |= 1u << 7;
//			arshr(value, 7);
//		}
//		stream++;
//	} while (!is_last);
//	return stream - (uint8_t*)buffer;
//}

unsigned core::readUleb(uint32_t& value, const void* buffer) {
	const uint8_t* stream = (uint8_t*) buffer;
	uint32_t byte = 0;
	uint8_t offset = 0;
	value = 0;
	do{
		byte = *stream & ~(~0u << 7);
		value |= byte << offset;
		offset += 7;
	} while(*stream++ & 1u << 7);
	return stream - (uint8_t*)buffer;
}

//unsigned core::readSleb(int32_t& value, const void* buffer) {
//	const uint8_t* stream = (uint8_t*) buffer;
//	uint32_t byte = 0;
//	uint8_t offset = 0;
//	uint8_t sign = 0;
//	value = 0;
//	do{
//		byte = *stream & ~(~0u << 7);
//		sign = byte & (1u << 6);
//		value |= byte << offset;
//		offset += 7;
//	} while(*stream++ & 1u << 7);
//
//	if(sign){
//		value |= (~0u << offset);
//	}
//	return stream - (uint8_t*)buffer;
//}

unsigned core::testUleb(uint32_t value) {
	unsigned stream = 0;
	do {
		value >>= 7;
		stream++;
	} while(value);
	return stream;
}

//unsigned core::testSleb(int32_t value) {
//	unsigned stream = 0;
//	int32_t test = 0;
//	uint8_t is_last = 0;
//	do {
//		test = value;
//		arshr(test, 6);
//		is_last = (test == 0 || ~test == 0);
//		if(is_last){
//			arshr(value, 6);
//		} else {
//			arshr(value, 7);
//		}
//		stream++;
//	} while (!is_last);
//	return stream;
//}

void core::arshr(int32_t& v, uint8_t shift) {
	if(v < 0){
		v = ~((~v) >> shift);
	} else {
		v >>= shift;
	}
}

