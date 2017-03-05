#ifndef CORE_UTILS_ENDIAN_H
#define CORE_UTILS_ENDIAN_H

#include <stdlib.h>
#include <stdint.h>

namespace core {

	template<typename T>
	static size_t writeLittleEndian(T value, void* buffer) {
		uint8_t* array = (uint8_t*) buffer;
		size_t size = sizeof(T);
		while (size--) {
			*array = value & 0xFF;
			value >>= 8;
			array++;
		}
		return sizeof(T);
	}

	template<typename T>
	static size_t writeBigEndian(T value, void* buffer) {
		uint8_t* array = (uint8_t*) buffer;
		size_t size = sizeof(T);
		array += size;
		while (size--) {
			array--;
			*array = value & 0xFF;
			value >>= 8;
		}
		return sizeof(T);
	}


	template<typename T>
	static size_t readLittleEndian(T& value, const void* buffer) {
		size_t size = sizeof(T);
		value = 0;
		const uint8_t* array = (const uint8_t*) buffer;
		array += size;
		while (size--) {
			array--;
			value <<= 8;
			value |= *array & 0xFF;
		}
		return sizeof(T);
	}

	template<typename T>
	static size_t readBigEndian(T& value, const void* buffer) {
		size_t size = sizeof(T);
		value = 0;
		const uint8_t* array = (const uint8_t*) buffer;
		while (size--) {
			value <<= 8;
			value |= *array & 0xFF;
			array++;
		}
		return sizeof(T);
	}

};

#endif /* CORE_UTILS_ENDIAN_H */
