#include "types.h"

#include <cstdlib>
#include <cerrno>

long core::string2long(const char* string, long defaultValue, int base) {
	char *end;
	errno = 0;
	long result = std::strtol(string, &end, base);
	if (errno != 0 || end == string) {
		errno = 0;
		result = defaultValue;
	}
	return result;
}

