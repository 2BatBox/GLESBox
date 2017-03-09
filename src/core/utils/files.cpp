#include "files.h"

#include "../fio/FileWriter.h"
#include "../fio/RawInputFile.h"
#include "../fio/FileReader.h"
#include "../fio/RawOutputFile.h"
#include "../memory.h"

#include <memory>

core::Array<char> core::loadFile(const char* fileName) throw (FIOException, EOFException) {
	std::unique_ptr<InputFile> inputFile(RawInputFile::open(fileName));
	FileReader reader(inputFile.get());
	size_t fileSize = inputFile->getSize();
	AutoArray<char> array(new char[fileSize], fileSize);
	reader.readFully(*array, array.size);
	return array.takeAway();
}

void core::saveFile(const char* fileName, const Array<char>& array) throw (FIOException) {
	std::unique_ptr<OutputFile> outputFile(RawOutputFile::open(fileName));
	FileWriter writer(outputFile.get());
	writer.writeFully(*array, array.size);
}

