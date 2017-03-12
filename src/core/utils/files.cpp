#include "files.h"

#include "../fio/FileWriter.h"
#include "../fio/FileReader.h"
#include "../fio/RawOutputFile.h"
#include "../memory.h"

#include <memory>

core::Array<char> core::loadFile(InputFile* inputFile) throw (FIOException, EOFException) {
	FileReader reader(inputFile);
	size_t fileSize = inputFile->getSize();
	AutoArray<char> array(new char[fileSize], fileSize);
	reader.readFully(*array, array.size);
	return array.takeAway();
}

core::Array<char> core::loadFileCString(InputFile* inputFile) throw (FIOException, EOFException) {
	FileReader reader(inputFile);
	size_t fileSize = inputFile->getSize() + 1;
	AutoArray<char> array(new char[fileSize], fileSize);
	reader.readFully(*array, array.size - 1);
	array[array.size - 1] = 0;
	return array.takeAway();
}

void core::saveFile(OutputFile* outputFile, const Array<char>& array) throw (FIOException) {
	FileWriter writer(outputFile);
	writer.writeFully(*array, array.size);
}

