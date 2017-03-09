#include "FileWriter.h"

using namespace core;

FileWriter::FileWriter(OutputFile* file) :
		file(file) {
}

unsigned FileWriter::write(char* buffer, unsigned size) throw (FIOException) {
	return file->write(buffer, size);
}

unsigned FileWriter::writeFully(const char* buffer, unsigned size) throw (FIOException) {
	size_t writed = 0;
	while (writed < size) {
		size_t result = file->write(buffer + writed, size - writed);
		writed += result;
		if (result == 0) {
			throw FIOException("Can't write buffer");
		}
	}
	return writed;
}
