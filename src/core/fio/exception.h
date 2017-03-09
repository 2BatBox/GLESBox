#ifndef CORE_FIO_EXCEPTION_H_
#define CORE_FIO_EXCEPTION_H_

#include "../exception.h"

namespace core {

class FIOException: public std::logic_error {
public:
	FIOException(const std::string& message) :
			std::logic_error(message) {
	}
};

class EOFException: public std::exception {
};

};

#endif /* CORE_FIO_EXCEPTION_H_ */
