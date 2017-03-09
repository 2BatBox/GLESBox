#ifndef CORE_UTILS_FILES_H_
#define CORE_UTILS_FILES_H_

#include "../memory.h"
#include "../fio/exception.h"

namespace core {

Array<char> loadFile(const char* fileName) throw (FIOException, EOFException);
void saveFile(const char* fileName, const Array<char>& array) throw (FIOException);

};

#endif /* CORE_UTILS_FILES_H_ */
