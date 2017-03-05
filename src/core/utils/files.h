#ifndef CORE_UTILS_FILES_H_
#define CORE_UTILS_FILES_H_

#include "../memory.h"
#include "../exception.h"

namespace core {

Array<char> loadFile(const char* fileName) throw (IOException, EOFException);
void saveFile(const char* fileName, const Array<char>& array) throw (IOException, EOFException);

};

#endif /* CORE_UTILS_FILES_H_ */
