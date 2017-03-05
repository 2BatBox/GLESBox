#ifndef CORE_EXCEPTION_H_
#define CORE_EXCEPTION_H_

#include <stdexcept>
#include <stdlib.h>

class IOException : public std::logic_error {
public:
	IOException(const std::string& message) : std::logic_error(message) {
	}
};

class NullPointerException : public std::exception {
};

class EOFException : public std::exception {
};

class LEBFormatException : public std::exception {
};

class BadFormatException : public std::logic_error {
public:
	BadFormatException(const std::string& message) : std::logic_error(message) {
	}
};


#endif /* CORE_EXCEPTION_H_ */
