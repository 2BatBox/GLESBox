#ifndef CORE_UTILS_FILES_H_
#define CORE_UTILS_FILES_H_

#include "../memory.h"
#include "../fio/exception.h"
#include "../fio/InputFile.h"
#include "../fio/OutputFile.h"

namespace core {

Array<char> loadFile(InputFile* inputFile) throw (FIOException, EOFException);
Array<char> loadFileCString(InputFile* inputFile) throw (FIOException, EOFException);
void saveFile(OutputFile* outputFile, const Array<char>& array) throw (FIOException);

};

#endif /* CORE_UTILS_FILES_H_ */
