#ifndef CORE_EXCEPTION_H_
#define CORE_EXCEPTION_H_

#include <stdexcept>
#include <stdlib.h>

namespace core {

class NullPointerException : public std::exception {
};

};

#endif /* CORE_EXCEPTION_H_ */
